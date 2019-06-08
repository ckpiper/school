#include <stdio.h>
#include <stdlib.h>
#include "Jpegfile.h"
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "omp.h"
#include <time.h>


int main()
{	
	// clock_t t;
	// int f;
	// t = clock();

	UINT height;
	UINT width;
	BYTE *dataBuf;
	//read the file to dataBuf with RGB format
	dataBuf = JpegFile::JpegFileToRGB("monarchColor.jpg", &width, &height);

	//the following code convert RGB to gray luminance.
	UINT row,col;

	clock_t t;
	int f;
	t = clock();

	// This creates the threads which will be dispersed for the rows
	// double st = omp_get_wtime();
	omp_set_num_threads(4);
	#pragma omp parallel for private(col) //collapse(2)
	for (row=0;row<height;row++) {
		for (col=0;col<width;col++) {
			BYTE *pRed, *pGrn, *pBlu;
			pRed = dataBuf + row * width * 3 + col * 3;
			pGrn = dataBuf + row * width * 3 + col * 3 + 1;
			pBlu = dataBuf + row * width * 3 + col * 3 + 2;

			// luminance
			int lum = (int)(.299 * (double)(*pRed) + .587 * (double)(*pGrn) + .114 * (double)(*pBlu));

			*pRed = (BYTE)lum;
			*pGrn = (BYTE)lum;
			*pBlu = (BYTE)lum;
		}
		// int c = omp_get_num_threads();
		// printf("Number of Threads = %d\n", c);
	}

	// double time = omp_get_wtime() - st;
	// printf("It took me %f.\n", st);

	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", (int)t, ((float)t)/CLOCKS_PER_SEC);

	//write the gray luminance to another jpg file
	JpegFile::RGBToJpegFile("monarchMono.jpg", dataBuf, width, height, true, 75);
	
	delete dataBuf;

	// t = clock() - t;
	// printf("It took me %d clicks (%f seconds).\n", (int)t, ((float)t)/CLOCKS_PER_SEC);
	
	return 1;
}
