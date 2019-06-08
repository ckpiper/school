#include <stdio.h>
#include <stdlib.h>
#include "../Jpegfile.h"
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
//#include <time.h>


int main()
{	
	//clock_t t;
	//int f;
	//t = clock();

	UINT height;
	UINT width;
	BYTE *dataBuf;
	//read the file to dataBuf with RGB format
	dataBuf = JpegFile::JpegFileToRGB("images/monarchColor.jpg", &width, &height);

	//the following code convert RGB to gray luminance.
	// UINT row,col;

	// This creates the threads which will be dispersed for the rows
	#pragma acc kernels copy(dataBuf[0:height*width*3-1])
	{
	for (UINT row=0;row<height;row++) {
		for (UINT col=0;col<width;col++) {
			BYTE pRed, pGrn, pBlu;
			pRed = dataBuf[row * width * 3 + col * 3];
			pGrn = dataBuf[row * width * 3 + col * 3+1];
			pBlu = dataBuf[row * width * 3 + col * 3+2];
			// luminance
			int lum = (int)(.299 * (int)(pRed) + .587 * (int)(pGrn) + .114 * (int)(pBlu));

			dataBuf[row * width * 3 + col * 3] = (BYTE)lum;
			dataBuf[row * width * 3 + col * 3+1] = (BYTE)lum;
			dataBuf[row * width * 3 + col * 3+2] = (BYTE)lum;
		}
	}

	}
	
	//write the gray luminance to another jpg file
	JpegFile::RGBToJpegFile("images/monarchMono.jpg", dataBuf, width, height, true, 75);
	
	delete dataBuf;

	//t = clock() - t;
	//printf("It took me %d clicks (%f seconds).\n", (int)t, ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}

