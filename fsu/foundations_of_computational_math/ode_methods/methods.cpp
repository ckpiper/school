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
// #include <cmath>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>  // This is to set precision of displayed long floats

precision initCond = 1.0;
precision lambda = -10;

precision exact(precision t){
	precision eval = (initCond - sin(0))*exp(lambda*t) + sin(t);
	return eval;
}


precision ff(precision t, precision y){
	precision eval = lambda*(y - sin(t)) + cos(t);
	return eval;
}


void method1(precision * yy, precision start, precision end, int N);

// Explicit Midpoint
void method2(precision * yy, precision start, precision end, int N);

// Adams-Bashford two-step
void method3(precision * yy, precision start, precision end, int N);

// Adams-Moulton one-step
void method4(precision * yy, precision start, precision end, int N);

// BDF one-step (Backward Euler)
void method5(precision * yy, precision start, precision end, int N);

// BDF two-step
void method6(precision * yy, precision start, precision end, int N);


int main(){

	int N = 10000;
	precision yy1[N+1];
	precision yy2[N+1];
	precision yy3[N+1];
	precision yy4[N+1];
	precision yy5[N+1];
	precision yy6[N+1];
	precision start = 0.0;
	precision end = 1.0;

	method1(yy1, start, end, N);
	method2(yy2, start, end, N);
	method3(yy3, start, end, N);
	method4(yy4, start, end, N);
	method5(yy5, start, end, N);
	method6(yy6, start, end, N);

	precision h = (end-start)/N;
	cout << "Step & Exact & Method 1 & Method 2 & Method 3 & Method 4 & Method 5 & Method 6 \\\\" << endl; 
	for(int i = 0; i <= N; i++){
		cout << i << " & " << exact(start + i*h) << " & " << yy1[i] << " & " << yy2[i] << " & " << yy3[i] << " & " << yy4[i] << " & " << yy5[i] << " & " << yy6[i] << " \\\\ " << endl; 
	}

	return 0;
}


void method1(precision * yy, precision start, precision end, int N){

	precision h = (end-start)/N; 
	yy[0] = exact(start);
	yy[1] = exact(start + h);
	// cout << 0 << " : " << yy[0] << endl;
	// cout << 1 << " : " << yy[1] << endl;

	// This loop uses the method and prints out each result the method produces
	for (int i = 2; i <= N; i++){
		yy[i] = -4*yy[i-1] + 5*yy[i-2] + h*(4*ff(start+(i-1)*h, yy[i-1]) + 2*ff(start+(i-2)*h, yy[i-2]));
		// cout << i << " : " << exact(start + i*h) << " : " << yy[i] << endl;
	}

	return;
}



void method2(precision * yy, precision start, precision end, int N){

	precision h = (end-start)/N; 
	yy[0] = exact(start);
	yy[1] = exact(start + h);
	// cout << 0 << " : " << yy[0] << endl;
	// cout << 1 << " : " << yy[1] << endl;

	// This loop uses the method and prints out each result the method produces
	for (int i = 2; i <= N; i++){
		yy[i] = yy[i-2] + 2*h*ff(start+(i-1)*h, yy[i-1]);
		// cout << i << " : " << exact(start + i*h) << " : " << yy[i] << endl;
	}

	return;
}

void method3(precision * yy, precision start, precision end, int N){

	precision h = (end-start)/N; 
	yy[0] = exact(start);
	yy[1] = exact(start + h);
	// cout << 0 << " : " << yy[0] << endl;
	// cout << 1 << " : " << yy[1] << endl;

	// This loop uses the method and prints out each result the method produces
	for (int i = 2; i <= N; i++){
		yy[i] = yy[i-1] + h*(3*ff(start + (i-1)*h, yy[i-1]) - ff(start + (i-2)*h, yy[i-2]))/2.0;
		// cout << i << " : " << exact(start + i*h) << " : " << yy[i] << endl;
	}

	return;
}

void method4(precision * yy, precision start, precision end, int N){
	precision h = (end-start)/N;
	yy[0] = exact(start);
	// cout << 0 << " : " << yy[0] << endl;

	// This loop uses the method and prints out each result the method produces
	for (int i=1; i<=N; i++){
		yy[i] = (yy[i-1] - h*(lambda*sin(start + i*h) - cos(start + i*h) - ff(start + (i-1)*h, yy[i-1]))/2.0)/(1-h/2.0);
		// cout << i << " : " << exact(start + i*h)  << " : " << yy[i] << endl;
	}

	return;

}


void method5(precision * yy, precision start, precision end, int N){

	precision h = (end-start)/N;
	yy[0] = exact(start);
	// cout << 0 << " : " << yy[0] << endl;

	// This loop uses the method and prints out each result the method produces
	for (int i=1; i<=N; i++){
		yy[i] = (yy[i-1] - h*lambda*sin(start + i*h) + h*cos(start + i*h))/(1-h*lambda);
		// cout << i << " : " << exact(start + i*h)  << " : " << yy[i] << endl;
	}

	return;
}



void method6(precision * yy, precision start, precision end, int N){
	precision h = (end-start)/N; 
	yy[0] = exact(start);
	yy[1] = exact(start + h);
	// cout << 0 << " : " << yy[0] << endl;
	// cout << 1 << " : " << yy[1] << endl;

	// This loop uses the method and prints out each result the method produces
	for (int i = 2; i <= N; i++){
		yy[i] = (4*yy[i-1] - yy[i-2] + 2*h*(-sin(start + i*h) + cos(start + i*h)))/(3 - 2*h*lambda);
		// cout << i << " : " << exact(start + i*h) << " : " << yy[i] << endl;
	}

	return;
}
