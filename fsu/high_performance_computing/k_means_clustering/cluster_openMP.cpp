// #ifdef DOUBLE
typedef double precision;
// #else
// typedef float precision;
// #endif

#include <limits>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Jpegfile.h"
using namespace std;
#include <time.h>
#include <cmath>
#include <math.h>
#include <vector>
#include "omp.h"



int main()
{
	precision time = omp_get_wtime();

	UINT height;
	UINT width;
	BYTE *dataBuf;
	//read the file to dataBuf with RGB format
	dataBuf = JpegFile::JpegFileToRGB("plots/monarchColor.jpg", &width, &height);


	UINT row,col;

	int k = 20;
	int N = width*height;
	int iterations = 25;

	// This places the first generators into a 2d array of k rows. (red, grn, blu)
	int mult = int(N/k);
	BYTE *pRed, *pGrn, *pBlu;
	vector<vector<int>> generators;
	for(int i=0; i<k; i++){
		pRed = dataBuf + i*mult*3;
		pGrn = dataBuf + i*mult*3 + 1;
		pBlu = dataBuf + i*mult*3 + 2;
		generators.push_back({(int)(*pRed), (int)(*pGrn), (int)(*pBlu)});
	}

	// If last iteration then we will need to collect all of the indices of the pixels in the local clusters 
	vector<vector<int>> mainClusters;
	for(int i=0; i<k; i++){
		mainClusters.push_back({});
	}

	// Start of Parallel Stuff
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// This is the for loop for the amount of iterations we want to complete of k means clustering
	for(int it=0; it<iterations; it++){

		// This is the amount of pixels inside each cluster. We will add up the sizes of the local clusters inside parallel region.
		// Also we will have the clustersSum for each cluster. We will put the local sum in it using critical 
		vector<int> clustersSize;
		vector<vector<precision>> clustersSum;
		for(int i=0; i<k; i++){
			clustersSize.push_back(0);
			clustersSum.push_back({0.0,0.0,0.0});
		}

		// This is where the Parallel Region will start at the start of each iteration.
		omp_set_num_threads(4);
		#pragma omp parallel shared(it, generators, k, clustersSize, clustersSum, mainClusters) private(pRed, pBlu, pGrn)
		{	
			// Every thread has its own local clusters vector which they will fill up with index data of each pixel
			vector<vector<int>> clusters;
			for(int i=0; i<k; i++){			
				clusters.push_back({});
			}

			// This for loop then places the pixels into clusters we will flatten out the index of the pixels so it will be one long array of pixel indices
				// then we will place the index of the pixel into the row of the cluster. the index being row*width + col
			UINT row,col;
			#pragma omp for private(col)
			for(row=0; row<height; row++){
				for(col=0; col<width; col++){
					pRed = dataBuf + row*width*3 + col*3;
					pGrn = dataBuf + row*width*3 + col*3 + 1;
					pBlu = dataBuf + row*width*3 + col*3 + 2;
					vector<int> pixel({(int)(*pRed), (int)(*pGrn), (int)(*pBlu)});

					// This for loop goes through clusters to find the closest color (in respect to L2 Norm) to the current Pixel we are on
					precision min = 10000000.0;			
					precision minCluster = 0;
					for(int i=0; i<k; i++){
						precision diffNorm = 0;
						// This is L2 Norm squared computation
						for(int j=0; j<3; j++){
							diffNorm = diffNorm + (generators[i][j] - pixel[j])*(generators[i][j] - pixel[j]);
						}
						// This sets the new min and which cluster it belongs to 
						if(diffNorm < min){
							min = diffNorm;
							minCluster = i;
						}
					}
					// This puts in the index of the pixel into the cluster group. It flattens the 2d array and puts in that index
					clusters[minCluster].push_back(row*width + col);
				}
			}

			// Sum of the local thread cluster eventually to be added to main clustersSum
			vector<vector<precision>> sum;		
			for(int i=0; i<k; i++){
				sum.push_back({0.0,0.0,0.0});
				for(int j=0; j<clusters[i].size(); j++){
					pRed = dataBuf + clusters[i][j]*3;
					pGrn = dataBuf + clusters[i][j]*3 + 1;
					pBlu = dataBuf + clusters[i][j]*3 + 2;
					sum[i][0] = sum[i][0] + (precision)(*pRed);
					sum[i][1] = sum[i][1] + (precision)(*pGrn);
					sum[i][2] = sum[i][2] + (precision)(*pBlu);
				}
			}

			// This sums the sizes of the local clusters and loads it into the outside clustersSize
			// This also puts the local sums into the outside clustersSum 
			// Lastly if this is the last iteration then it puts all of the indices in the mainClusters
			// So no data gets lost we need to do these two in sequential order (One thread at a time)
			#pragma omp critical
			for(int i=0; i<k; i++){
				clustersSize[i] = clustersSize[i] + clusters[i].size();
				for(int j=0; j<3; j++){
					clustersSum[i][j] = clustersSum[i][j] + sum[i][j];
				}
				// This piece fills in mainClusters from the local clusters if its the last iteration
				if(it == iterations - 1){
					for(int j=0; j<clusters[i].size(); j++){
						mainClusters[i].push_back(clusters[i][j]);
					}
				}
			}

			// This Sets the new generators as the average of the old cluster for the next iteration of clustering
			#pragma omp for
			for(int i=0; i<k; i++){
				for(int j=0; j<3; j++){
					generators[i][j] = clustersSum[i][j]/clustersSize[i];
				}
			}
		}
	}

	// This fills in the pixels belonging to the cluster and puts there colors as the average(new generator) of the cluster
	for(int i=0; i<k; i++){
		for(int j=0; j<mainClusters[i].size(); j++){
			pRed = dataBuf + mainClusters[i][j]*3;
			pGrn = dataBuf + mainClusters[i][j]*3 + 1;
			pBlu = dataBuf + mainClusters[i][j]*3 + 2;
			*pRed = (BYTE)generators[i][0];
			*pGrn = (BYTE)generators[i][1];
			*pBlu = (BYTE)generators[i][2];
		}
	}

	// Write the new blurred image to another jpeg file
	JpegFile::RGBToJpegFile("plots/monarchPar4Group20It25.jpg", dataBuf, width, height, true, 75);

	delete dataBuf;

	time = omp_get_wtime() - time;
	cout << "Time = " << time << endl;

	return 1;
}
