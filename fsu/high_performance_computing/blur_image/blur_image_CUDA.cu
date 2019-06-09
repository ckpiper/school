// #ifdef DOUBLE
typedef double precision;
// #else
// typedef float precision;
// #endif

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Jpegfile.h"

            // averageCalc<<<blocks, threadsPerBlock>>>(dataBufD, dataAvD, distancesD, distancesRowStartIndexD, rowStartD, rowEndD, N, height, width, sum, rInt);

__global__ void averageCalc(BYTE *dataBufD, BYTE *dataAvD, precision *distancesD, int *distancesRowStartIndexD, int *rowStartD, int *rowEndD, UINT height, UINT width, int rInt){

	int index = threadIdx.x + blockIdx.x * blockDim.x;
	int stride = blockDim.x * gridDim.x;
    int const rInt21 = rInt*2+1;
    int ND = (int)(height*width);

	for(int pixel=index; pixel<ND; pixel+=stride){
		// These are for the borders and get the row and col of the pixel this thread is going to handle
		int borderTop = 0, borderBot = 0, row = (int)(pixel/(int)width);
		int col = pixel - row*(int)width;
		// int *rowStartBord = (int *)malloc(rInt21*sizeof(int)), *rowEndBord = (int *)malloc(rInt21*sizeof(int));
		int rowStartBord[11], rowEndBord[11];
		for(int i=0; i<rInt21; i++){
			rowStartBord[i] = rowStartD[i];
			rowEndBord[i] = rowEndD[i];
		}

		// ////// These then change the border variables accordingly if we need to //////
		// // This tell the next nested loop to start at a higher row 
		// if(row < rInt){ borderTop = rInt - row; }

		// // This will tell the next nested loop to stop at a lower row
		// if(row > (int)height - rInt - 1){ borderBot = row - ((int)height - rInt - 1); }

		// // This is for the left boundary and changes the indices of rowStartBord if they are outside boundary
		// if(col < rInt){		
		// 	for(int i=0; i< rInt21; i++){
		// 		if(rowStartD[i] < -1*col){
		// 			rowStartBord[i] = -1*col;
		// 		}
		// 	}
		// }
		// // This is for the right boundary and changes the indices of rowEndBord if the end outside boundary
		// if(col > (int)width - rInt - 1){		
		// 	for(int i=0; i<rInt21; i++){
		// 		if(rowEndD[i] > (int)width - col - 1){
		// 			rowEndBord[i] = (int)width - col - 1;
		// 		}
		// 	}
		// }

		// rowStartD[0] = borderTop;
		// rowEndD[0] = borderBot;
		// for(int i=1; i<rInt21; i++){
		// 	rowEndD[i] = rowEndBord[i];
		// 	rowStartD[i] = rowStartBord[i];
		// }

		// These will hold the averages of the three colors
		precision rAvg = 0.0, gAvg = 0.0, bAvg = 0.0;

		BYTE *pRed, *pGrn, *pBlu;
		precision sum = 0.0;
		for(int i=borderTop; i <= rInt*2 - borderBot; i++){
			for(int j=0; j <= rowEndBord[i] - rowStartBord[i]; j++){
				if( (row+i-rInt) * (int)width + (col+rowStartBord[i]+j) >= 0 && (row+i-rInt) * (int)width + (col+rowStartBord[i]+j) < ND){
					// We need to shift the row and columns accordingly to the pixel in the ball we want
					// row is at center of ball then (i-rInt) is the +-indicating if we are above the center(-) or below(+)
					// col is at center of ball and rowStartBord[i] is 0 at most so j runs throught the row of the ball
					pRed = dataBufD + (row+i-rInt) * (int)width * 3 + (col+rowStartBord[i]+j) * 3;
					pGrn = dataBufD + (row+i-rInt) * (int)width * 3 + (col+rowStartBord[i]+j) * 3 + 1;
					pBlu = dataBufD + (row+i-rInt) * (int)width * 3 + (col+rowStartBord[i]+j) * 3 + 2;

					// This adds new information to the average multiplied by the corresponding weight 
					// distanceRowStartIndex starts you at the first spot of the this row on the stencil, 
						// but if we are on the left border we need to start not on the left most but a however many to the right which is what rowStartBord - rowStart does,
						// then j just is the increment for moving through the row 
					precision distance = distancesD[distancesRowStartIndexD[i] + rowStartBord[i]-rowStartD[i] + j];
					sum += distance;
					rAvg += ((precision)(*pRed))*distance;
					gAvg += ((precision)(*pGrn))*distance;
					bAvg += ((precision)(*pBlu))*distance;
				}
			}	
		}
		// rowStartD[0] = (int)(rAvg/sum), rowStartD[1] = (int)(gAvg/sum), rowStartD[2] = (int)(bAvg/sum), rowStartD[3] = (int)(sum*100000);

		pRed = dataAvD + pixel*3, pGrn = dataAvD + pixel*3 + 1, pBlu = dataAvD + pixel*3 + 2;

		// Divide by the sum to get the weighted average and turn it into an int and add it to the vector
        *pRed = (BYTE)(rAvg/sum), *pGrn = (BYTE)(gAvg/sum), *pBlu = (BYTE)(bAvg/sum);

        free(rowStartBord);
        free(rowEndBord);
	}

}


int main(){

	int experiment = 8;

    for(int blockMult=1; blockMult<experiment; blockMult++){
        printf("%d & ", (int)(pow(2, blockMult)));
        for(int threadMult=1; threadMult<experiment; threadMult++){

            clock_t start, end;
            double cpu_time_used;
             
            start = clock();

            int blocks = (int)(pow(2, blockMult)), threadsPerBlock = (int)(pow(2, threadMult));

			precision pi = M_PI;

			precision radius = 5.0;
			precision std = 10.0;
			precision std2 = 2*std*std;
			precision bottom = pi*std2;		// what the exponential function gets divided by

			// This is pre-processing to get distances/weights of gaussian distribution into a vector of vectors
			// We will find the border of our ball and then calculate the distances of each pixel in our ball from our zero pixel
			// In this we will treat the center of the ball as the the origin so roww=0 and coll=0. 
			// RowStart and RowEnd are inclusive so rowStart[2] = -2 and rowEnd[2] = 2; the row has 5 elements with index (-2,-1,0,1,2)
			int rInt = (int)radius;
			int rInt21 = rInt*2+1;
			int *rowStart = (int *)malloc(rInt21*sizeof(int)), *rowStartD;
			int *rowEnd = (int *)malloc(rInt21*sizeof(int)), *rowEndD;
			int roww = -1*rInt;		// This is the row of the top most pixel of ball
			int coll = 0;			// This is the column of the top most pixel of ball
			precision *distances, *distancesD;

			// printf("Done Allocating for rowStart and rowEnd, rInt = %d\n", rInt);

			// This gets the 2nd qudrant of the border and we will use symmetry to get the rest of the border
			// This starts at top and finds the border by moving left measuring the distance from center and
			// 		if the distance is larger than the radius we move back right, put that index into the our rowStart indices vector, and move down to start this over
			//		if it is smaller then we start the while loop over again to find the start of this row
			while(roww != 0){	
				coll--;
				precision length = sqrt(coll*coll + roww*roww);
				if(length > radius){
					coll++;
					rowStart[rInt + roww] = coll;
					roww++;
				}
			}
			rowStart[rInt] = -1*rInt; // This is the middle row start

			//// These next two for loops fill in rowStart and rowEnd using symmetry ////
			// the +-i from center will have same starting point
			for(int i=1; i <= rInt; i++){	rowStart[rInt+i] = rowStart[rInt-i];   }
			// the ends are same distance from center but on other side so just times them by negative 1
			for(int i=0; i < rInt21; i++){	rowEnd[i] = -1*rowStart[i];	  }
			// for(int i=0; i < rInt21; i++){	printf("%d, ", rowEnd[i]);	  }
			// printf("\n");
			// This frees up memory in the GPU and copies over rowStart and rowEnd into that freed memory
			cudaMalloc((void **)&rowStartD, rInt21*sizeof(int));
			cudaMalloc((void **)&rowEndD, rInt21*sizeof(int));
			cudaMemcpy(rowStartD, rowStart, rInt21*sizeof(int), cudaMemcpyHostToDevice);
			cudaMemcpy(rowEndD, rowEnd, rInt21*sizeof(int), cudaMemcpyHostToDevice);

			// printf("Done Allocating and Copying to rowStartD and rowEndD\n");

			// This allocates memory for distances and *distancesRowStartIndex
			int distancesSize = 0;
			int *distancesRowStartIndex = (int *)malloc(rInt21*sizeof(int)), *distancesRowStartIndexD;
			for(int i=0; i<(rInt*2+1); i++){
				distancesRowStartIndex[i] = distancesSize;
				distancesSize += rowEnd[i]*2+1;
			}
			distances = (precision *)malloc((distancesSize)*sizeof(precision));

			// printf("Done Allocating memory for distances and distancesRowStartIndex\n");

			// This fills in the distances data structure by just going through the the rows of the ball and calculating the distance and storing it
				// Fix sum if I have time
			precision sum = 0.0;
			for(int i=0; i<=rInt*2; i++){
				for(int j=0; j<rowEnd[i]-rowStart[i]; j++){			  // This underneat is the actual distance from center
					distances[distancesRowStartIndex[i]+j] = exp(-1 * sqrt( (rInt-i)*(rInt-i) + (rowStart[i]+j)*(rowStart[i]+j) ) / std2) / bottom;
					sum = sum + distances[distancesRowStartIndex[i]+j];
				}
			}
			// printf("sum = %f\n", sum);

			// printf("Done calculating Distances (Weights)\n");

			// This frees up memory in the GPU and copies over distances and distancesRowStartIndex
			cudaMalloc((void **)&distancesRowStartIndexD, rInt21*sizeof(int));
			cudaMalloc((void **)&distancesD, distancesSize*sizeof(precision));
			cudaMemcpy(distancesRowStartIndexD, distancesRowStartIndex, rInt21*sizeof(int), cudaMemcpyHostToDevice);
			cudaMemcpy(distancesD, distances, distancesSize*sizeof(precision), cudaMemcpyHostToDevice);

			// printf("Copied distances and distancesRowStartIndex in Device Memory\n");

			UINT height, width;
            BYTE *dataBuf, *dataBufD, *dataAvD;

            dataBuf = JpegFile::JpegFileToRGB("images/monarchColor.jpg", &width, &height);

            // printf("Height = %d\n", (int)height);
            // printf("Width = %d\n", (int)width);

            int sizeDataBuf = width*height*3 * (int)sizeof(BYTE);
            int N=height*width;

            // Allocating Space for device copies and copyies them into device
            BYTE *dataAv = (BYTE *)malloc(sizeDataBuf);
            for(int i=0; i<3*N; i++){    dataAv[i] = 0;    }
            cudaMalloc((void **)&dataBufD, sizeDataBuf);
            cudaMalloc((void **)&dataAvD, sizeDataBuf);
            cudaMemcpy(dataBufD, dataBuf, sizeDataBuf, cudaMemcpyHostToDevice);
            cudaMemcpy(dataAvD, dataAv, sizeDataBuf, cudaMemcpyHostToDevice);

            // printf("Copied dataBuf and dataAv in Device Memory\n");

            averageCalc<<<blocks, threadsPerBlock>>>(dataBufD, dataAvD, distancesD, distancesRowStartIndexD, rowStartD, rowEndD, height, width, rInt);

            // printf("Finished Kernal\n");

            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();

            // Copy new data from the device
            cudaMemcpy(dataBuf, dataAvD, sizeDataBuf, cudaMemcpyDeviceToHost);
            cudaMemcpy(rowStart, rowStartD, rInt21*sizeof(int), cudaMemcpyDeviceToHost);
            cudaMemcpy(rowEnd, rowEndD, rInt21*sizeof(int), cudaMemcpyDeviceToHost);
            // for(int i=0; i<rInt21; i++){	printf("%d, ", rowStart[i]);	}
           	// printf("\n");
            // for(int i=0; i < rInt21; i++){	printf("%d, ", rowEnd[i]);	}
            // printf("\n");
            // printf("%d, %d, %d \n", dataBuf[100*227*3], dataBuf[100*227*3+1], dataBuf[100*227*3+2]);

			// Write the gray lumin to another jpg file
            JpegFile::RGBToJpegFile("images/monarchBlur5.jpg", dataBuf, width, height, true, 100);

            // printf("Finished Jpeg Image\n");
            
            // Cleanup 
            free(dataBuf);
            cudaFree(dataBufD);
 			cudaFree(dataAvD);

 			free(distances);
 			cudaFree(distancesD);
 			free(distancesRowStartIndex);
 			cudaFree(distancesRowStartIndexD);

 			free(rowStart);
 			cudaFree(rowStartD);
 			free(rowEnd);
 			cudaFree(rowEndD);

 			// printf("Finished Cleanup\n");

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("%f & ", cpu_time_used);

        }
        printf("\\\\ \n");
    }

    return 0;
}

