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

	precision pi = M_PI;

	precision radius = 5.0;
	precision std = 5.0;
	precision std2 = 2*std*std;
	precision bottom = pi*std2;		// what the exponential function gets divided by

	// We a double array for each color to store average so the averages do not get added to the next iteration
	vector<vector<int>> redAvg;
	vector<vector<int>> grnAvg;
	vector<vector<int>> bluAvg;
	
	UINT height;
	UINT width;
	BYTE *dataBuf;
	//read the file to dataBuf with RGB format
	dataBuf = JpegFile::JpegFileToRGB("plots/monarchColor.jpg", &width, &height);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// This is pre-processing to get distances/weights of gaussian distribution into a vector of vectors
	// We will find the border of our ball and then calculate the distances of each pixel in our ball from our zero pixel
	// In this we will treat the center of the ball as the the origin so roww=0 and coll=0. 
	// RowStart and RowEnd are inclusive so rowStart[2] = -2 and rowEnd[2] = 2; the row has 5 elements with index (-2,-1,0,1,2)
	vector<int> rowStart;
	vector<int> rowEnd;
	vector<vector<precision>> distances;
	int rInt = (int)radius;
	int roww = -1*rInt;		// This is the row of the top most pixel of ball
	int coll = 0;			// This is the column of the top most pixel of ball 

	// This gets the 2nd qudrant of the border and we will use symmetry to get the rest of the border
	// This starts at top and finds the border by moving left measuring the distance from center and
	// 		if the distance is larger than the radius we move back right, put that index into the our rowStart indices vector, and move down to start this over
	//		if it is smaller then we start the while loop over again to find the start of this row
	while(roww != 0){	
		coll--;
		precision length = sqrt(coll*coll + roww*roww);
		if(length > radius){
			coll++;
			rowStart.push_back(coll);
			roww++;
		}
	}
	rowStart.push_back(-1*rInt); // This is the middle row start

	// These next two for loops fill in rowStart and rowEnd using symmetry
	for(int i=1; i <= rInt; i++){		
		rowStart.push_back(rowStart[rInt-i]);	// the +-i from center will have same starting point
	}
	for(int i=0; i <= rInt*2; i++){
		rowEnd.push_back(-1*rowStart[i]);	// the ends are same distance from center but on other side so just times them by negative 1
	}

	// This fills in the distances data structure by just going through the the rows of the ball and calculating the distance and storing it
	precision sum = 0.0;
	for(int i=0; i<=rInt*2; i++){	// i corresponds to row, but starts with origin at top left corner.
		distances.push_back({});
		for(int j=0; j<=rowEnd[i]-rowStart[i];j++){	// j correspnds to column, but starts with origin at top left corner
			distances[i].push_back(sqrt((rInt-i)*(rInt-i) + (rowStart[i]+j)*(rowStart[i]+j)));
			distances[i][j] = exp(-1*distances[i][j]/std2) / bottom;
			sum = sum + distances[i][j];
		}
	}

 	// Now we have finished the preprocessing
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// precision time = omp_get_wtime();
	
	UINT row,col;

	// This piece of code is to put zeroes in our 2D vectors for averages
	for (row=0;row<height;row++) {
		redAvg.push_back({});
		grnAvg.push_back({});
		bluAvg.push_back({});
		for (col=0;col<width;col++) {
			redAvg[(int)row].push_back(0); 
			grnAvg[(int)row].push_back(0); 
			bluAvg[(int)row].push_back(0);
		}
	}

	int i, j;
	omp_set_num_threads(4);
	#pragma omp parallel for private(col, i, j) //shared(redAvg, grnAvg, bluAvg, rowStart, rowEnd, distances, height) //collapse(2)
	for (row=0;row<height;row++) {
		for (col=0;col<width;col++) {
			// These will hold the averages of the three colors
			precision rAvg = 0.0;
			precision gAvg = 0.0;
			precision bAvg = 0.0;

			// These are for the borders 
			int borderTop = 0;
			int borderBot = 0.;
			vector<int> rowStartBord;
			vector<int> rowEndBord;
			// This fills in the new rowStartBord and rowEndBord with the original from above
			for(i=0; i<rowStart.size(); i++){
				rowStartBord.push_back(rowStart[i]);
				rowEndBord.push_back(rowEnd[i]);
			}

			////// These then change the border variables accordingly if we need to //////
			// This tell the next nested loop to start at a higher row 
			if((int)row < rInt){ borderTop = rInt - row; }

			// This will tell the next nested loop to stop at a lower row
			if((int)row > height - rInt - 1){ borderBot = row - (height - rInt - 1); }

			// This is for the left boundary and changes the indices of rowStartBord if they are outside boundary
			if((int)col < rInt){		
				for(i=0; i< rowStart.size(); i++){
					if(rowStart[i] < -1*(int)col){
						rowStartBord[i] = -1*col;
					}
				}
			}
			// This is for the right boundary and changes the indices of rowEndBord if the end outside boundary
			if((int)col > (int)width - rInt - 1){		
				for(i=0; i<rowEnd.size(); i++){
					if(rowEnd[i] > (int)width-(int)col - 1){
						rowEndBord[i] = (int)width-(int)col - 1;
					}
				}
			}

			BYTE *pRed, *pGrn, *pBlu;
			for(i=borderTop; i <= rInt*2 - borderBot; i++){
				for(j=0; j <= rowEndBord[i] - rowStartBord[i]; j++){
					// We need to shift the row and columns accordingly to the pixel in the ball we want
					// row is at center of ball then (i-rInt) is the +-indicating if we are above the center(+) or below(-)
					// col is at center of ball and rowStartBord[i] is 0 at most so j runs throught the row of the ball
					pRed = dataBuf + (row+i-rInt) * width * 3 + (col+rowStartBord[i]+j) * 3;
					pGrn = dataBuf + (row+i-rInt) * width * 3 + (col+rowStartBord[i]+j) * 3 + 1;
					pBlu = dataBuf + (row+i-rInt) * width * 3 + (col+rowStartBord[i]+j) * 3 + 2;

					// This adds new information to the average times the corresponding weight 
					rAvg = rAvg + (precision)(*pRed)*(distances[i][j]);
					gAvg = gAvg + (precision)(*pGrn)*(distances[i][j]);
					bAvg = bAvg + (precision)(*pBlu)*(distances[i][j]);
				}	
			}
			// Divide by the sum to get the weighted average and turn it into an int and add it to the vector
			redAvg[(int)row][(int)col] = (int)(rAvg/sum); 
			grnAvg[(int)row][(int)col] = (int)(gAvg/sum); 
			bluAvg[(int)row][(int)col] = (int)(bAvg/sum);
		}
	}

	// time = omp_get_wtime() - time;
	// cout << "Time = " << time << endl;

	// This fills in the new bytes of the jpeg with the averages
	for (row=0;row<height;row++) {
		for (col=0;col<width;col++) {
			BYTE *pRed, *pGrn, *pBlu;
			pRed = dataBuf + row * width * 3 + col * 3;
			pGrn = dataBuf + row * width * 3 + col * 3 + 1;
			pBlu = dataBuf + row * width * 3 + col * 3 + 2;

			*pRed = (BYTE)redAvg[(int)row][(int)col];
			*pGrn = (BYTE)grnAvg[(int)row][(int)col];
			*pBlu = (BYTE)bluAvg[(int)row][(int)col];
		}
	}

	// Write the new blurred image to another jpeg file
	JpegFile::RGBToJpegFile("plots/monarchBlurP10.jpg", dataBuf, width, height, true, 75);

	delete dataBuf;

	time = omp_get_wtime() - time;
	cout << "Time = " << time << endl;

	return 1;
}
