// mpic++ -o clusterMPIParallel.exe ../Jpegfile.cpp clusterMPIParallel.cpp ../JpegLib/libjpeg.a

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
#include "../Jpegfile.h"
using namespace std;
#include <time.h>
#include <cmath>
#include <math.h>
#include "mpi.h"



int main(int argc, char *argv[])
{

	MPI_Init(&argc, &argv);
	int id, p;

	// These get the id of worker / process and the number of processes
	MPI_Comm_rank ( MPI_COMM_WORLD, &id ); 
    MPI_Comm_size ( MPI_COMM_WORLD, &p ); 

	double t1;
	t1 = MPI_Wtime();
	int k = 5;
	int iterations = 1;

	// These are all our variables which need to be initialized
	UINT height, width;
	int numPixels, totalPixels;
	BYTE *dataBuf = NULL;
	int *allClusterSize = new int[k];
    int *allClusterSum = new int[k*3];
    BYTE **rootClusters = NULL;
	BYTE *generators = new BYTE[k*3];

    // This fills up the dataBuf only in the root
	if( id==0 ){
		dataBuf = JpegFile::JpegFileToRGB("testColor.jpg", &width, &height);

		totalPixels = (int) height * (int) width;
		numPixels = (int)(totalPixels / p);

		// This places the first generators into a 2d array of k rows. (red, grn, blu)
		int mult = int(totalPixels/k);
		BYTE *pRed, *pGrn, *pBlu;
		for(int i=0; i<k; i++){
			pRed = dataBuf + i*mult*3;
			pGrn = dataBuf + i*mult*3 + 1;
			pBlu = dataBuf + i*mult*3 + 2;
			generators[i*3] = (*pRed);
			generators[i*3+1] = (*pGrn);
			generators[i*3+2] = (*pBlu);
		}
	}

	// This gives the number of pixels to every worker
	MPI_Bcast(&numPixels, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// This allocates memory for the pixels that will be sent to this worker (Each pixel has 3 words)
    BYTE *workerBuf = NULL;
	workerBuf = new BYTE[numPixels*3];

	// This scatters the data from dataBuf into the private workerBuf array
    MPI_Scatter(dataBuf, numPixels*3, MPI_BYTE, workerBuf, numPixels*3, MPI_BYTE, 0, MPI_COMM_WORLD);

    // This Broadcasts the generators to each of the workers
    MPI_Bcast(generators, k*3, MPI_INT, 0, MPI_COMM_WORLD);

    // This is the for loop for the amount of iterations we want to complete of k means clustering
	for(int it=0; it<iterations; it++){
		// The next 15 lines are different dynamic arrays which we will need
		int *workerClusterSize = NULL;
		workerClusterSize = new int[k];
		int *workerClusterSum = NULL;
		workerClusterSum = new int[k*3];
		for(int i=0; i<k; i++){  workerClusterSize[i] = 0;  }
		for(int i=0; i<k*3; i++){  workerClusterSum[i] = 0;  }	
		int **workerClusters2D = NULL;
		if(it == iterations - 1){
			// This will store where the index of the pixel in each cluster We do not know how long each will be so we assume the longest which would be one of the clusters would have every pixel
			workerClusters2D = new int*[k];
			for(int i=0; i<k; i++){  workerClusters2D[i] = new int[numPixels];  }
		}

		// Place the pixels into the correct clusters and finding the sum and sizes of clusters
		for(int i=0; i<numPixels; i++){
			// BYTE *pRed, *pGrn, *pBlu;
			BYTE pRed = workerBuf[i*3];
			BYTE pGrn = workerBuf[i*3+1];
			BYTE pBlu = workerBuf[i*3+2];

			precision min = 100000000;
			int minCluster;
			for(int j=0; j<k; j++){
				// This finds the L2 norm squared
				precision diffNorm = ((int)(pRed)-generators[j*3])*((int)(pRed)-generators[j*3]) + 
						((int)(pGrn)-generators[j*3+1])*((int)(pGrn)-generators[j*3+1]) + ((int)(pBlu)-generators[j*3+2])*((int)(pBlu)-generators[j*3+2]);
				if(diffNorm < min){
					min = diffNorm;
					minCluster = j;
				}
			}

			if(it==(iterations-1)){
				// The workerClusterSize holds the size of each cluster up to this point thus it is the index of the next spot in the array
				// Now id0 gets the first numPixels, id1 gets second numPixels, and so the index of the pixel will be numPixels*id to get to starting index then plus whateve pixels it is here
				workerClusters2D[minCluster][workerClusterSize[minCluster]] = numPixels*id + i;
			}

			workerClusterSum[minCluster*3] += (int)(pRed);
			workerClusterSum[minCluster*3+1] += (int)(pGrn);
			workerClusterSum[minCluster*3+2] += (int)(pBlu);
			workerClusterSize[minCluster]++;
		}

		// This places the last (totalPixels-numPixels*p) pixels into the correct clusters of the root directory 
		if(id==0){
			for(int i=numPixels*p; i<totalPixels - numPixels*p; i++){
				printf("i=%d\n", i);
				BYTE *pRed, *pGrn, *pBlu;
				pRed = dataBuf + i*3;
				pGrn = dataBuf + i*3 + 1;
				pBlu = dataBuf + i*3 + 2;

				precision min = 100000000;
				int minCluster;
				for(int j=0; j<k; j++){
					// This finds the L2 norm squared
					precision diffNorm = ((int)(*pRed)-generators[j*3])*((int)(*pRed)-generators[j*3]) + 
							((int)(*pGrn)-generators[j*3+1])*((int)(*pGrn)-generators[j*3+1]) + ((int)(*pBlu)-generators[j*3+2])*((int)(*pBlu)-generators[j*3+2]);
					if(diffNorm < min){
						min = diffNorm;
						minCluster = j;
					}
				}

				if(it == iterations - 1){
					// The workerClusterSize hold the size of each cluster up to this point so we use it as the next spot
					// Now id0 gets the first numPixels, id1 gets second numPixels, and so the index of the pixel will be numPixels*p to get to starting index then plus whateve pixels it is here
					workerClusters2D[minCluster][workerClusterSize[minCluster]] = numPixels*p + i;
				}

				workerClusterSum[minCluster*3] += (int)(*pRed);
				workerClusterSum[minCluster*3+1] += (int)(*pGrn);
				workerClusterSum[minCluster*3+2] += (int)(*pBlu);
				workerClusterSize[minCluster]++;
			}
		}

		// Set allCluster arrays to zero
		for(int i=0; i<k; i++){  allClusterSize[i] = 0;  }
		for(int i=0; i<k*3; i++){  allClusterSum[i] = 0;  }
		int **workerClusterSize2D = new int*[k];
		int **workerClusterDisp2D = new int*[k];
		if(it == iterations - 1){
			if(id==0){
				// We will need the individual workerClusterSize and workerClusterDisp for the MPI_Gatherv if its the last iteration
				// This will be a 2D rectangular array where index workerClusterSize2D[i][j] is the size of the ith cluster in the j process
				// workerClusterSize2D = new int*[k];
				// workerClusterDisp2D = new int*[k];
				for(int i=0; i<k; i++){
					workerClusterSize2D[i] = new int[p];
					workerClusterDisp2D[i] = new int[p];
					for(int j=0; j<p; j++){ workerClusterSize2D[i][j] = 0; }
					for(int j=0; j<p; j++){ workerClusterDisp2D[i][j] = 0; }
				}
			}


			printf("Right Before Barrier\n");
	    	MPI_Barrier(MPI_COMM_WORLD);
	    	printf("Right After Barrier\n");

			printf("id=%d, Before Gather\n", id);
			// This Fills up workerClusterSize2D
			for(int i=0; i<k; i++){  MPI_Gather(workerClusterSize+i, 1, MPI_INT, workerClusterSize2D[i], 1, MPI_INT, 0, MPI_COMM_WORLD);  }
			printf("id=%d, After Gather\n", id);

			// Now we need to fill up the allClusterSize totals for the avg later 
			// We also need to make the displacement vector for the gatherv
			if(id==0){
				for(int i=0; i<k; i++){
					for(int j=0; j<p; j++){  allClusterSize[i] += workerClusterSize2D[i][j];  }
					workerClusterDisp2D[i][0] = workerClusterSize2D[i][0];
					for(int j=1; j<p; j++){  workerClusterDisp2D[i][p] = workerClusterDisp2D[i][p-1] + workerClusterSize2D[i][p];  }
				}
			}

			printf("id=%d, Before MPI_Bcast\n", id);
			MPI_Bcast(allClusterSize, k, MPI_INT, 0, MPI_COMM_WORLD);
			printf("id=%d, After MPI_Bcast\n", id);
		} else {
			MPI_Allreduce(workerClusterSize, allClusterSize, k, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
		}

		printf("id=%d, After initializing allCLuster and workerClusterSizeDisp2D\n", id);

		MPI_Allreduce(workerClusterSum, allClusterSum, k*3, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

		// We can delete the workerClusterSize and workerClusterSum as we are done with them
		delete [] workerClusterSize;
		workerClusterSize = NULL;
		delete [] workerClusterSum;
		workerClusterSum = NULL;

		// This averages the the sums and then sets the new generators to those averages and then delete allClusterSize as it is no longer needed
		for(int i=0; i<k; i++){ for(int j=0; j<3; j++){  generators[i*3+j] = (BYTE)(allClusterSum[i*3+j]/allClusterSize[i]);  } }

		// This is for the last iteration when we will need to collect the indices to change the actual dataBuf
		if(it == iterations - 1){
			rootClusters = new BYTE*[k];
			for(int i=0; i<k; i++){
				rootClusters[i] = new BYTE[allClusterSize[i]];
				MPI_Gatherv(workerClusters2D[i], workerClusterSize[i], MPI_BYTE, rootClusters[i], workerClusterSize2D[i], workerClusterDisp2D[i], MPI_BYTE, 0, MPI_COMM_WORLD);
			}
			// We do not need the workerClusterSize/Disp anymore as they were only used for the MPI_Gatherv
			if(id==0){
				for(int i=0; i<k; i++){
					delete [] workerClusterSize2D[i];
					delete [] workerClusterDisp2D[i];
				}
				delete [] workerClusterSize2D;
				delete [] workerClusterDisp2D;
				workerClusterSize2D = NULL;
				workerClusterDisp2D = NULL;
			}
			for(int i=0; i<k; i++){  delete [] workerClusters2D[i];  }
			delete [] workerClusters2D;
			workerClusters2D = NULL;
		}
	}

	// Now we can delete these as we are completely done with them
	delete [] allClusterSum;
	allClusterSum = NULL;
	delete [] workerBuf;
	workerBuf = NULL;

	if(id==0){
		for(int i=0; i<k; i++){
			for(int j=0; j<allClusterSize[i]; j++){
				BYTE *pRed, *pGrn, *pBlu;
				pRed = dataBuf + rootClusters[i][j]*3;
				pGrn = dataBuf + rootClusters[i][j]*3 + 1;
				pBlu = dataBuf + rootClusters[i][j]*3 + 2;
				*pRed = (BYTE)generators[i*3];
				*pGrn = (BYTE)generators[i*3+1];
				*pBlu = (BYTE)generators[i*3+2];
			}
		}
	}

	delete [] generators;
	generators = NULL;
	delete [] allClusterSize;
	allClusterSize = NULL;
	for(int i=0; i<k; i++){  delete [] rootClusters[i];  }
	delete [] rootClusters;
	rootClusters = NULL;

	JpegFile::RGBToJpegFile("plots/testPar4Group5It1.jpg", dataBuf, width, height, true, 75);

	delete dataBuf;

	if( id ==0 ){
		printf("Elapsed time is %f\n", MPI_Wtime() - t1);
	}

	MPI_Finalize();
	
	return 0;
}








