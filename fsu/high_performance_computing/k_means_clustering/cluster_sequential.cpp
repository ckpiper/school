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
		generators.push_back({(int)(*pRed), (int)(*pGrn), (int)(*pBlu), 0});
	}

	// This is the for loop for the amount of iterations we want to complete of k means clustering
	for(int it=0; it<iterations; it++){
		vector<vector<int>> clusters;
		for(int i=0; i<k; i++){
			clusters.push_back({});
		}

		// This for loop then places the pixels into clusters we will flatten out the index of the pixels so it will be one long array of pixel indices
			// then we will place the index of the pixel into the row of the cluster. the index being row*width + col
		UINT row,col;
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

		// This next loop then finds the averages of the groups
		for(int i=0; i<k; i++){
			vector<precision> avg({0.0,0.0,0.0});		// average of cluster
			for(int j=0; j<clusters[i].size(); j++){
				pRed = dataBuf + clusters[i][j]*3;
				pGrn = dataBuf + clusters[i][j]*3 + 1;
				pBlu = dataBuf + clusters[i][j]*3 + 2;
				
				avg[0] = avg[0] + (precision)(*pRed);
				avg[1] = avg[1] + (precision)(*pGrn);
				avg[2] = avg[2] + (precision)(*pBlu);
			}
			generators[i][0] = avg[0]/clusters[i].size();
			generators[i][1] = avg[1]/clusters[i].size();
			generators[i][2] = avg[2]/clusters[i].size();
		}

		// If this is the last iteration then we go through the cluster and then set that pixel as the generator
		if(it == iterations - 1){
			for(int i=0; i<k; i++){
				for(int j=3; j<clusters[i].size(); j++){
					pRed = dataBuf + clusters[i][j]*3;
					pGrn = dataBuf + clusters[i][j]*3 + 1;
					pBlu = dataBuf + clusters[i][j]*3 + 2;
					*pRed = (BYTE)generators[i][0];
					*pGrn = (BYTE)generators[i][1];
					*pBlu = (BYTE)generators[i][2];
				}
			}
		}
	}


	// Write the new blurred image to another jpeg file
	JpegFile::RGBToJpegFile("plots/monarchGroup20It25.jpg", dataBuf, width, height, true, 75);

	delete dataBuf;

	time = omp_get_wtime() - time;
	cout << "Time = " << time << endl;

	return 1;
}
