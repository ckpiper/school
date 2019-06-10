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


double exactEval(double x, int function){
	double y;
	if(function == 1){ y = exp(x);}							// 19.0855369232
	else if(function == 2){ y = exp(sin(2.0*x))*cos(2.0*x);}	// 0.6887213376
	else if(function == 3){ y = tanh(x);}					// -0.89122191687
	else if(function == 4){ y = x*cos(2.0*x*M_PI);}			// -0.050660591821169
	else if(function == 5){ y = x + 1.0/x ;}				// 6.3388758248682
	else if(function == 6){ y = 1.0/x ;}
	else if(function == 7){ y = exp(sin(10*M_PI*x)) ;}
	else if(function == 8){ y = }
	return y;
}


precision trapRule(int numMesh, precision * xMesh, precision * intEvals, int function, int iterations, precision actual);

precision trapRule(int numMesh, precision * xMesh, int function);

precision romberg(int numMesh, precision * xMesh, int function, int iterations, precision actual);


int main(){
	cout << std::setprecision(13)<< std::fixed;
	precision actual[8] = {0, 19.0855369232, 0.688721337618082394, -0.89122191687, -0.050660591821169, 6.3388758248682, 0.6931471805599453094, 1.2660658777520083356}; 
	precision upBound[8] = {0, 3.0, M_PI/3.0, 1.0, 3.5, 2.5, 2.0, 1.0};
	precision lowBound[8] = {0, 0.0, 0.0, -2.0, 0.0, 0.1, 1.0, 0.0};
	int function = 7;
	int iterations = 8;

	cout << "Up = " << upBound[function] << ", low = " << lowBound[function] << endl;
	cout << "Actual = " << actual[function] << endl;
	cout << "--------------" << endl;

	int numMesh = 2;
		precision dx = (upBound[function] - lowBound[function])/(numMesh-1);
		precision xMesh[numMesh];
		for (int i = 0; i < numMesh; i++){
			xMesh[i] = lowBound[function] + i*dx;
		}

	precision approx = romberg(numMesh, xMesh, function, iterations, actual[function]);

	cout << "Approx = " << approx << endl;
	cout << "Error = " << fabs(actual[function] - approx) << endl;

}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


precision trapRule(int numMesh, precision * xMesh, int function){
	precision dx = (xMesh[numMesh-1] - xMesh[0])/(numMesh-1);
	precision sum = 0.5*(exactEval(xMesh[0], function) + exactEval(xMesh[numMesh-1], function));
	for(int i=1; i < numMesh-1; i++){
		sum = sum + exactEval(xMesh[i],function);
	}
	sum = sum*dx;
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


// In this dx is the distance on the x-axis between each new evaluation being used in this iteration
precision trapRule(int numMesh, precision * xMesh, precision * intEvals, int function, int iterations, precision actual){
	precision dx = (xMesh[numMesh-1]-xMesh[0])/(numMesh-1);
	precision sum = trapRule(numMesh, xMesh, function);
	intEvals[0] = sum;
	int iterationCount = 1;
	int intervals = numMesh-1;

	while (iterationCount < iterations){

		// The new evaluations start at a + 0.5*dx the last dx. After though each new eval goes by dx spacing.
		precision newEvalSum = 0;
		for(int i=0; i < pow(2.0, iterationCount-1)*(numMesh-1); i++){
			newEvalSum = newEvalSum + exactEval(xMesh[0] + 0.5*dx + i*dx, function) ;
		}

		// Then get the new dx and multiply it by 
		dx = 0.5*dx;
		newEvalSum = dx*newEvalSum ;
		sum = sum/2.0 + newEvalSum;
		
		intEvals[iterationCount] = sum;
		intervals = intervals*2;
		iterationCount++;
	}
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


precision romberg(int numMesh, precision * xMesh, int function, int iterations, precision actual){
	precision intEvals[(int) pow(2, iterations)];
	trapRule(numMesh, xMesh, intEvals, function, iterations, actual);
	
	for (int i=0; i < iterations; i++) { cout << fabs(actual - intEvals[i]) << " & "  << intEvals[i] << " & " << endl ;}
	cout << "--------------" << endl;

	// This is where each new level of extrapolations gets pushed into the intEvals array 
	// evatually keeping the highest degree of extrapolation with the given number of refinements
	for(int column = 1; column < iterations; column++){
		for(int row = iterations-1; row >= column; row--){
			intEvals[row] = (pow(4.0, column)*intEvals[row] - intEvals[row-1])/(pow(4.0, column) - 1);
		}

		for (int i=column; i < iterations; i++){ cout << fabs(actual - intEvals[i]) << " & " << intEvals[i] << " & " << endl ;}
		cout << "--------------" << endl;
	}

	// for (int i=0; i < iterations-1; i++){ cout << fabs(actual - intEvals[i]) << " & " ;}
	// cout << fabs(actual - intEvals[iterations-1]) << " \\\\" << endl;
	return intEvals[iterations-1];
}
