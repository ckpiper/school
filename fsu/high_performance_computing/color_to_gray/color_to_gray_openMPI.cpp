#include <stdio.h>
#include <stdlib.h>
#include "../Jpegfile.h"
#include <time.h>
#include "mpi.h"





int main(int argc, char *argv[]) {



	// This initializes the MPI Region
	MPI_Init(&argc, &argv);

	double t1;
	t1 = MPI_Wtime();

	// These are all our variables which need to be initialized
	UINT height, width;
	int id, p, numPixels, totalPixels;
	BYTE *dataBuf = NULL;

	// These get the id of worker / process and the number of processes
	MPI_Comm_rank ( MPI_COMM_WORLD, &id ); 
    MPI_Comm_size ( MPI_COMM_WORLD, &p ); 

	if( id==0 ){
		dataBuf = JpegFile::JpegFileToRGB("monarchColor.jpg", &width, &height);
		totalPixels = (int) height * (int) width;
		numPixels = (int)(totalPixels / p);

		// for(int i=totalPixels-10; i<totalPixels; i++){
		// 	printf( "%d, %d, %d\n", (int)(*(dataBuf+i*3)), (int)(*(dataBuf+i*3 + 1)), (int)(*(dataBuf+i*3+2)) ) ;
		// }
		// printf("\n");
	}

	// This gives the number of pixels to every worker
	MPI_Bcast(&numPixels, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // This allocates memory for the pixels that will be sent to this worker (Each pixle has 3 words)
    BYTE *workerBuf = NULL;
	workerBuf = new BYTE[numPixels*3];

    // This scatters the datta from dataBuf into the private workerBuf array
    MPI_Scatter(dataBuf, numPixels*3, MPI_BYTE, workerBuf, numPixels*3, MPI_BYTE, 0, MPI_COMM_WORLD);

  //   if(id==3){
		// printf("Before the woker pixels\n");
		// for(int i=numPixels-7; i<numPixels; i++){
		// 	printf( "%d, %d, %d\n", (int)(workerBuf[3*i]), (int)(workerBuf[3*i+1]), (int)(workerBuf[3*i+2]) ) ;
		// }
  //   }
    // This does the computations for the numPixels*p pixels in workerBuf
    for(int i=0; i<numPixels; i++){
    	BYTE pRed = workerBuf[3*i];
    	BYTE pGrn = workerBuf[3*i+1];
    	BYTE pBlu = workerBuf[3*i+2];

		// luminance
		BYTE lum = (BYTE)(.299 * (double)(pRed) + .587 * (double)(pGrn) + .114 * (double)(pBlu));

		workerBuf[3*i] = lum;
		workerBuf[3*i+1] = lum;
		workerBuf[3*i+2] = lum;
    }
  //   if(id==3){
  //   	printf("After the woker pixels\n");
		// for(int i=numPixels-7; i<numPixels; i++){
		// 	printf( "%d, %d, %d\n", (int)(workerBuf[3*i]), (int)(workerBuf[3*i+1]), (int)(workerBuf[3*i+2]) ) ;
		// }
  //   }
	
	// The master does the left over pixels
	if( id==0 ){
		// printf("numPixels*p = %d \ntotalPixels = %d\n", numPixels*p, totalPixels);
		// for(int i=totalPixels-10; i<totalPixels; i++){
		// 	printf( "%d, %d, %d\n", (int)(*(dataBuf+i*3)), (int)(*(dataBuf+i*3 + 1)), (int)(*(dataBuf+i*3+2)) ) ;
		// }
		// printf("\n");
		for(int i=numPixels*p; i<totalPixels; i++){
	    	BYTE *pRed, *pGrn, *pBlu;

			pRed = dataBuf + i*3;
			pGrn = dataBuf + i*3 + 1;
			pBlu = dataBuf + i*3 + 2;

			// luminance
			int lum = (int)(.299 * (double)(*pRed) + .587 * (double)(*pGrn) + .114 * (double)(*pBlu));

			*pRed = (BYTE)lum;
			*pGrn = (BYTE)lum;
			*pBlu = (BYTE)lum;
	    }
	    // int pixx[p*numPixels*3];
	}

	MPI_Gather(workerBuf, numPixels*3, MPI_BYTE, dataBuf, numPixels*3, MPI_BYTE, 0, MPI_COMM_WORLD);

	// Delete the allocated memory for the workerBuf, clear to preven using invalid memory reference
	delete [] workerBuf;
	workerBuf = NULL;

	// The Mast
	if( id==0 ){
		// for(int i=totalPixels-10; i<totalPixels; i++){
		// 	printf( "%d, %d, %d\n", (int)(*(dataBuf+i*3)), (int)(*(dataBuf+i*3 + 1)), (int)(*(dataBuf+i*3+2)) ) ;
		// }

		JpegFile::RGBToJpegFile("monarchGray.jpg", dataBuf, width, height, true, 75);

	}
	if( id ==0 ){
		printf("Elapsed time is %f\n", MPI_Wtime() - t1);
	}

	MPI_Finalize();

	return 0;


}




