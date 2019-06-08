#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Jpegfile.h"


__global__ void luminanceCalc(BYTE *dataBufD, int ND){
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    int stride = blockDim.x * gridDim.x;
    for(int i=index; i<ND; i+=stride){    
        BYTE *pRed, *pGrn, *pBlu;
        pRed = dataBufD + i*3;
        pGrn = dataBufD + i*3 +  1;
        pBlu = dataBufD + i*3 +  2;

        int lum = (int)(.299 * (double)(*pRed) + .587 * (double)(*pGrn) + .114 * (double)(*pBlu));

        *pRed = (BYTE)lum;
        *pGrn = (BYTE)lum;
        *pBlu = (BYTE)lum;
    }
}

// #define blocks 1
// #define threadsPerBlock 1
int main(){

    int experiment = 1;

    for(int blockMult=0; blockMult<experiment; blockMult++){
        printf("%d & ", (int)(pow(2, blockMult)));
        for(int threadMult=0; threadMult<experiment; threadMult++){

            clock_t start, end;
            double cpu_time_used;
             
            start = clock();

            int blocks = (int)(pow(2, blockMult)), threadsPerBlock = (int)(pow(2, threadMult));

            UINT height, width;
            BYTE *dataBuf, *dataBufD;

            dataBuf = JpegFile::JpegFileToRGB("images/monarchColor.jpg", &width, &height);

            int sizeDataBuf = width*height*3 * (int)sizeof(BYTE);

            int N=height*width;

            // Allocating Space for device copies
            cudaMalloc((void **)&dataBufD, sizeDataBuf);

            // Copy inputs into the device
            cudaMemcpy(dataBufD, dataBuf, sizeDataBuf, cudaMemcpyHostToDevice);

            // Launch the luminanceCalc function
            luminanceCalc<<<blocks,threadsPerBlock>>>(dataBufD, N);

            // Wait for GPU to finish before accessing on host
            cudaDeviceSynchronize();

            // Copy new data from the device
            cudaMemcpy(dataBuf, dataBufD, sizeDataBuf, cudaMemcpyDeviceToHost);

            // Write the gray luminance to another jpg file
            JpegFile::RGBToJpegFile("images/monarchMonoExp.jpg", dataBuf, width, height, true, 75);
            
            // Cleanup 
            free(dataBuf);
            cudaFree(dataBufD);

            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            printf("%f & ", cpu_time_used);

        }
        printf("\\\\ \n");
    }

    return 0;
}

