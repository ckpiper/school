// For double precision type in "g++ -DDOUBLE=1 title.cpp" into the terminal
#ifdef DOUBLE
typedef double precision;
#else
typedef float precision;
#endif

#include <limits>
#include <fstream>
#include <iostream>
using namespace std;
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <time.h>
#include <vector>
#include <iomanip>  // This is to set precision of displayed long floats

const precision pi = M_PI;
const complex i = 1*I;
const int n = 1024; // pow(2,10);
precision complex source[n][n];

void print(precision complex y){
	cout << creal(y) << " + " << cimag(y) << "*i";
}
void print(int p, precision complex *y){
	for (int k=0; k<p; k++){
		print(y[k]);
		cout << endl;
	}
	cout << endl;
}
void print(int p, precision complex y[n][n]){
	for(int k=0; k<p; k++){
		cout << "|(" ;
		for (int j=0; j<p; j++){
			print(y[k][j]);
			if(j != p-1){
				cout << ", ";
			}
		}
		cout << ")|" << endl;
	}
}
void zeroComplexArray(int p, precision complex *y){
	for(int k=0; k<p; k++){
		y[k] = 0;
	} 
}
void nChoice(int p, precision complex *y){
	for(int k=0; k<p; k++){
		y[k]= k + (k+1)*i;
	}
}
void fill2DArray(int p, precision complex y[n][n]){
	for(int k=0; k<p; k++){
		for(int j=0; j<p; j++){
			y[k][j] = rand()%10000 + (rand()%10000)*i;
			// y[k][j] = (k)*p +(j+1);
			// y[k][j] = 0;
		}
	}
}



void discreteFourierTransform(int p, precision complex *ff);
void inverseDiscreteFourierTransform(int p, precision complex *ff);

void fastFourierTransform(int p, precision complex *ff);
void inverseFastFourierTransform(int p, precision complex *ff);
void sortingAlgorithm(int p, precision complex *ff, precision complex *feven, precision complex *fodd);

void circLinearSystemSolver(int p, precision complex *bb, precision complex *cc);

void discreteFT2D(int p, precision complex ff[n][n]);
void discreteIFT2D(int p, precision complex ff[n][n]);
void compress(int p, precision complex ff[n][n], precision eps);

void focusImage(int p, precision complex circ[n], precision complex blur[n][n]);



int main(){
	// rand(time(0));
	// cout.precision(10);

	cout << "n = " << n << endl;
	// // This is for testing my DFT and IDFT
	// precision complex f[n];
	// nChoice(n, f);
	// // cout << "This is original" << endl;
	// // print(n, f);
	// clock_t dft = clock();
	// discreteFourierTransform(n, f);
	// dft = clock()-dft;
	// cout << "DFTtook " << dft << " ticks, or " << ((double)dft)/CLOCKS_PER_SEC << " seconds." << endl;
	// cout << "This is using DFT" << endl;
	// // print(n,f);
	// // inverseDiscreteFourierTransform(n, f);
	// // cout << "This is using IDFT" << endl;
	// // print(n,f);

	// // This is for testing my FFT and IFFT
	// precision complex z[n];// = {-3, 0, -1, 4};
	// nChoice(n, z);
	// clock_t fft = clock();
	// fastFourierTransform(n, z);
	// fft = clock()-fft;
	// cout << "FFTtook " << fft << " ticks, or " << ((double)fft)/CLOCKS_PER_SEC << " seconds." << endl;
	// cout << "This is using FFT" << endl;
	// // print(n,z);
	// // inverseFastFourierTransform(n, z);
	// // cout << "This is using IFFT" << endl;
	// // print(n,z);


	// // This is for checking the circulant Linear Sys tem Solver
	// precision complex bb[4] = {-3,0,-1,4};
	// cout << "This is bb original" << endl;
	// print(4, bb);
	// precision complex cc[4] = {1,2,3,4};
	// cout << "This is circ " << endl;
	// print (4, cc);
	// circLinearSystemSolver(4, bb, cc);
	// cout << "This is xx" << endl;
	// print(4, bb);


	// // This be for the 2D DFT image processing 
	// precision complex zz[8][8];
	// fill2DArray(8, zz);
	// zz[1][2] = 70; zz[1][3] = 80; zz[1][4] = 90; zz[2][2] = 90; zz[2][3] =100; zz[2][4] =110;
	// zz[3][2] =110; zz[3][3] =120; zz[3][4] =130; zz[4][2] =130; zz[4][3] =140; zz[4][4] =150;
	// print2D(n, zz);
	// cout << endl;
	// discreteFT2D(n, zz);
	// print2D(n, zz);
	// cout << endl;
	// discreteIFT2D(n, zz);
	// print2D(n, zz);
	// cout << endl;


	// // This is for to test compression and error check 
	// precision complex zz[n][n];
	// precision complex orig[n][n];
	// fill2DArray(n, zz);
	// for(int k=0; k<n; k++){
	// 	for(int j=0; j<n; j++){
	// 		orig[k][j] = zz[k][j];
	// 	}
	// }
	// // cout << "This is the original" << endl; print(n, zz); cout << endl; cout << endl;
	// discreteFT2D(n, zz);
	// // cout << "This is DFT" << endl; print(n, zz); cout << endl; cout << endl;
	// compress(n, zz, 30000);
	// cout << "This is the compressed" << endl; print(n, zz); cout << endl; cout << endl;
	// discreteIFT2D(n, zz);
	// cout << "This is the IDFT" << endl; print(n, zz); cout << endl; cout << endl;

	// // Finds the largest error with respect to the norm FInds 
	// precision bigErr = 0.0;
	// precision sumReal = 0.0;
	// precision sumImag = 0.0;
	// precision sum = 0.0;
	// for(int k=0; k<n; k++){
	// 	for(int j=0; j<n; j++){
	// 		precision errorNorm = cabs(zz[k][j]-orig[k][j]);
	// 		if(bigErr < errorNorm){
	// 			bigErr = errorNorm;
	// 			// cout << cabs(zz[k][j]-orig[k][j]) << endl;
	// 		}
	// 		// If real is below tolerance 
	// 		precision errorReal = abs(creal(zz[k][j])-creal(orig[k][j]));
	// 		if(errorReal/creal(orig[k][j]) > 0.05*creal(orig[k][j])){
	// 			sumReal++;
	// 		}
	// 		// If imaginary part error is below a tolerance
	// 		precision errorImag = abs(cimag(zz[k][j])-cimag(orig[k][j]));
	// 		if(errorImag/cimag(orig[k][j]) > 0.05*cimag(orig[k][j])){
	// 			sumImag++;
	// 		}

	// 		if(errorImag/cimag(orig[k][j]) > 0.05*cimag(orig[k][j]) || errorReal/creal(orig[k][j]) > 0.05*creal(orig[k][j])){
	// 			sum++;
	// 		}
	// 	}
	// }
	// cout << "Largest Error = " << bigErr << ", with respect to |z|" << endl;
	// cout << "Elements whose Real part is to out of error tolerance " << sumReal/(n*n) << endl;
	// cout << "Elements whose Imag part is to out of error tolerance " << sumImag/(n*n) << endl;
	// cout << "Elements where one part is to out of error tolerance " << sum/(n*n) << endl;


	ifstream inOrig("../data/blurredDemo.txt");
	ifstream incircD("../data/circulantDemo.txt");
	precision complex circD[n];

	// This fills in the 2D-Array
	for(int k=0; k<n; k++){
		precision c;
		for(int j=0; j<n; j++){
			inOrig >> c;
			source[k][j] = c + 0*i;
		}
		incircD >> c;
		circD[k] = c + 0*i;
	}
	inOrig.close();
	incircD.close();
	focusImage(n, circD, source);

	// This writes out to focusedDemo.txt
	ofstream outFocus("../data/focusedDemo.txt");
	for(int k=0; k<n; k++){
		for(int j=0; j<n; j++){
			outFocus << creal(source[k][j]) << "    "; // " + " << cimag(blur[k][j]) << "*i" << "    ";
		}
		outFocus << endl;
	}
	outFocus.close();

	discreteFT2D(n, source);
	compress(n, source, 0.5);
	discreteIFT2D(n, source);

	// This writes in the compressd file
	ofstream outCompress("../data/compressedDemo.txt");
	for(int k=0; k<n; k++){
		for(int j=0; j<n; j++){
			outCompress << creal(source[k][j]) << "    "; // " + " << cimag(blur[k][j]) << "*i" << "    ";
		}
		outCompress << endl;
	}
	outCompress.close();




	// // This is for testing focusing a blurry image
	// precision complex blur[n][n];
	// fill2DArray(n, blur);
	// precision complex circ[n] = {1,2,3,4};
	// focusImage(n, circ, blur);

	// cout << "Hello" << endl;
	// ifstream inblur("../data/blurred.txt");
	// ifstream incirc("../data/circulant.txt");
	// precision complex blur[n][n];
	// precision complex circ[n];
	// for(int k=0; k<n; k++){
	// 	precision c;
	// 	for(int j=0; j<n; j++){
	// 		inblur >> c;
	// 		blur[k][j] = c + 0*i;
	// 	}
	// 	incirc >> c;
	// 	circ[k] = c + 0*i;
	// }
	// inblur.close();
	// incirc.close();

	// focusImage(n, circ, blur);

	// // This writes in the focused data
	// ofstream outimage("../data/focused.txt");
	// for(int k=0; k<n; k++){
	// 	for(int j=0; j<n; j++){
	// 		outimage << creal(blur[k][j]) << "    "; // " + " << cimag(blur[k][j]) << "*i" << "    ";
	// 	}
	// 	outimage << endl;
	// }

	// // This checks to see if any error accumulates from original to focused 
	// ifstream inOrig("../data/source.txt");
	// precision errorBig = 0;
	// precision origin = 0;
	// precision error = 0;
	// for(int k=0; k<n; k++){
	// 	for(int j=0; j<n; j++){
	// 		inOrig >> origin;
	// 		error = origin - creal(blur[k][j]);
	// 		error = fabs(error);
	// 		if(errorBig < error){
	// 			errorBig = error;
	// 		}
	// 	}
	// 	// cout << " Original = " << origin << endl;
	// 	// cout << " Focused = " << creal(blur[k][n-1]) << endl;
	// }
	// // cout << errorBig << endl;

}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void discreteFourierTransform(int p, precision complex *ff){
	// Temporary holding array for new frequency domain fs
	precision complex ww[p];
	zeroComplexArray(p, ww);

	for(int k=0; k<p; k++){
		// Horners Rule
		precision complex muk = cexp((-2*pi*k/p)*i);
		ww[k] = ff[p-1];
		for(int j=p-2; j>=0; j--){
			ww[k] = ww[k]*muk + ff[j];
		}
	}

	// Scaling for DFT
	for(int k=0; k<p; k++){
		ff[k] = ww[k]/pow(p,0.5);
	}
}


void inverseDiscreteFourierTransform(int p, precision complex *ww){
	// Temporary holding array for origianl time sequence domain fs
	precision complex ff[p];
	zeroComplexArray(p, ff);

	for(int k=0; k<p; k++){
		// Horners Rule
		precision complex omk = cexp((2*pi*k/p)*i);
		ff[k] = ww[p-1];
		for(int j=p-2; j>=0; j--){
			ff[k] = ff[k]*omk + ww[j];
		}
	}

	// Scaling for IDFT
	for(int k=0; k<p; k++){
		ww[k] = ff[k]/pow(p,0.5);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void fastFourierTransform(int p, precision complex *ff){

	// Base case is when p=2
	if(p == 2){
		discreteFourierTransform(p, ff);
	} else {

		// Creating the feven/fodd arrays and filling them in
		precision complex feven[p/2];
		precision complex fodd[p/2];
		zeroComplexArray(p/2, feven);
		zeroComplexArray(p/2, fodd);
		sortingAlgorithm(p, ff, feven, fodd);

		// The recursion steps
		fastFourierTransform(p/2, feven);
		fastFourierTransform(p/2, fodd);

		// This find the fourier transform at the current level in the recursion we are at.
		precision complex scale = 1/pow(2,0.5);
		for(int k = 0; k<p; k++){
			ff[k] = scale*(feven[k%(p/2)] + cexp((-2*pi*k/p)*i)*fodd[k%(p/2)]);
		}
	}
}

void inverseFastFourierTransform(int p, precision complex *ff){

	// Base case is when p=2
	if(p == 2){
		inverseDiscreteFourierTransform(p, ff);
	} else {

		// Creating the feven/fodd arrays and filling them in
		precision complex feven[p/2];
		precision complex fodd[p/2];
		zeroComplexArray(p/2, feven);
		zeroComplexArray(p/2, fodd);
		sortingAlgorithm(p, ff, feven, fodd);

		// The recursion steps
		inverseFastFourierTransform(p/2, feven);
		inverseFastFourierTransform(p/2, fodd);

		// This find the fourier transform at the current level in the recursion we are at.
		precision complex scale = 1/pow(2,0.5);
		for(int k = 0; k<p; k++){
			ff[k] = scale*(feven[k%(p/2)] + cexp((2*pi*k/p)*i)*fodd[k%(p/2)]);
		}
	}
}


void sortingAlgorithm(int p, precision complex *ff, precision complex *feven, precision complex *fodd){
	// This sorts ff into its even indices and odd indices
	for(int k=0; k<p-1; k=k+2){
		feven[k/2] = ff[k];
		fodd[k/2] = ff[k+1];
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// This solves F_n^H * Gamma_n^{-1} * F_n * b = c
void circLinearSystemSolver(int p, precision complex *bb, precision complex *cc){

	// This solves the F_n * b = Fb
	fastFourierTransform(p, bb);
	
	// This gets the inverse of Gamma_n
	for(int k=0; k<p; k++){
		precision complex gamma = 0 + 0*i;
		precision complex muk = cexp((2*pi*k/p)*i);

		// Horner's Rule
		gamma = cc[p-1];
		for(int j=p-2; j>=0; j--){
			gamma = gamma*muk + cc[j];
		}

		// This then does Gamma_n^{-1} * Fb = GFb
		bb[k] = bb[k]/gamma;
	}

	inverseFastFourierTransform(p, cc);
	

	for(int j=0; j<p; j++){
		bb[j] = bb[j]/cc[j];// /pow(p,0.5);
	}

	// This then computes F_n^H * GFb = X
	inverseFastFourierTransform(p, bb);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// For A' = F * A * F^T, we first do DFT for rows of A then hitting tho
void discreteFT2D(int p, precision complex ff[n][n]){
	// This is the temporary array for columns of ff
	precision complex ww[p];

	// This does the DFT for columns of ff
	for(int k=0; k<p; k++){
		zeroComplexArray(p, ww);

		// This fills in ww with column entries of ff
		for(int j=0; j<p; j++){
			ww[j] = ff[j][k];
		}

		fastFourierTransform(p, ww);

		// This puts the now transformed ww into back into the column of ff from whence it came
		for(int j=0; j<p; j++){
			ff[j][k] = ww[j];
		}
	}

	// This does the DFT for the rows of the new ff from transforming its columns
	// It is shorter than the columns because we can pass the rows of ff itself into the FFT function
	for(int k=0; k<p; k++){
		fastFourierTransform(p,ff[k]);
	}
}

void discreteIFT2D(int p, precision complex ff[n][n]){
	// This is the temporary array for columns of ff
	precision complex ww[p];

	// This does the DFT for columns of ff
	for(int k=0; k<p; k++){
		zeroComplexArray(p, ww);

		// This fills in ww with column entries of ff
		for(int j=0; j<p; j++){
			ww[j] = ff[j][k];
		}

		inverseFastFourierTransform(p, ww);

		// This puts the now transformed ww into back into the column of ff from whence it came
		for(int j=0; j<p; j++){
			ff[j][k] = ww[j];
		}
	}

	// This does the DFT for the rows of the new ff from transforming its columns
	// It is shorter than the columns because we can pass the rows of ff itself into the FFT function
	for(int k=0; k<p; k++){
		inverseFastFourierTransform(p,ff[k]);
	}
}

// Compresses a matrix in the frequency complex domain by using the magnitude of the complex numbers
void compress(int p, precision complex ff[n][n], precision eps){
	precision compressed = 0;
	for(int k=0; k<p; k++){
		// for(int j=0; j<p; j++){
		// 	if(cabs(ff[k][j]) < eps){
		// 		ff[k][j] = 0 + 0*i;
		// 		compressed++;
		// 		cout << compressed << endl;
		// 	}
		// }


		// Last row to zero
		if(k==p-1){
			for(int j=0; j<p; j++){
				ff[k][j] = 0 + 0*i;
			}
		}

		// Last column to zero
		ff[k][0] = 0 + 0*i;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// We will solve M = C^T * I * C, by first solving M = C^T * L for L then solving L = I * C.
void focusImage(int p, precision complex circ[n], precision complex blur[n][n]){

	// Temporary circTran
	precision complex circTran[p];

	// This fills in circTran which is reverse then upshirft circ
	circTran[0] = circ[0];
	for(int k=1; k<p; k++){
		circTran[k] = circ[p-k];
	}

	// This solves M = C^T * L which is solving each column of L at a time
	for(int k=0; k<p; k++){
		precision complex colBlur[p];

		// This gets the k^th column of blurred image M
		for(int j=0; j<p; j++){
			colBlur[j] = blur[j][k];
		}

		// This then solves for the k^th column of blurred image M
		circLinearSystemSolver(p, colBlur, circTran);
		cout << "col " << k << endl;

		// colBlur gets changed into k^th column of L in circLinearSystemSolver, so we need to 
		// put it back in blur as we no longer need that column.
		for(int j=0; j<p; j++){
			blur[j][k] = colBlur[j];
		}
	}

	// This solves L = I * C which is solving each row of I at a time
	for(int k=0; k<p; k++){

		// Remember that our blurred image M is now L
		circLinearSystemSolver(p, blur[k], circTran);
		cout << "row " << k << endl;
	}
}
