#include <stdio.h>
#include <stdlib.h>
#include "Jpegfile.h"
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

	clock_t t;
	int f;
	t = clock();
	//the following code convert RGB to gray luminance.
	UINT row,col;
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
	}

	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", (int)t, ((float)t)/CLOCKS_PER_SEC);

	//write the gray luminance to another jpg file
	JpegFile::RGBToJpegFile("monarchMono.jpg", dataBuf, width, height, true, 75);

	delete dataBuf;

	// t = clock() - t;
	// printf("It took me %d clicks (%f seconds).\n", (int)t, ((float)t)/CLOCKS_PER_SEC);

	return 1;
}
