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
#include <vector>
#include <string>
#include <iomanip>  // This is to set precision of displayed long floats


double exactEval(double x, int function){
	double y;
	if(function == 1){ y = exp(x);}							// 19.0855369232
	else if(function == 2){ y = exp(sin(2*x))*cos(2*x);}	// 0.6887213376
	else if(function == 3){ y = tanh(x);}					// -0.89122191687
	else if(function == 4){ y = x*cos(2*x*M_PI);}			// -0.050660591821169
	else if(function == 5){ y = x + 1.0/x ;}				// 6.3388758248682
	else if(function == 6){ y = 1/x ;}
	else if(function == 7){ y = pow(1-x*x, 0.5) ;}
	else if(function == 8){ y = (2*pow(x,5.0) - x + 3)/(pow(x, 2.0)) ;} // 1 -> 2, 8.30685281944
	return y;
}

precision trapRule(int numMesh, precision * xMesh, int function);

precision simpsonRule(int numMesh, precision * xMesh, int function);

precision midPointRule(int numMesh, precision * xMesh, int function);

precision openRule2(int numMesh, precision * xMesh, int function);

precision gaussLegendreRule(int numMesh, precision * xMesh, int function);

precision trapRule(int numMesh, precision * xMesh, int function, precision e, precision actual);

precision simpsonRule(int numMesh, precision * xMesh, int function, precision e, precision actual);

precision midPointRule(int numMesh, precision * xMesh, int function, precision e, precision actual);

precision openRule2(int numMesh, precision * xMesh, int function, precision e, precision actual);

precision gaussLegendreRule(int numMesh, precision * xMesh, int function, precision e, precision actual);


int main(){
	cout << std::setprecision(10)<< std::fixed;
	int intervals[5] = {620, 439, 358, 3, 53} ;
	precision actual[6] = {0, 19.0855369232, 0.6887213376, -0.89122191687, -0.050660591821169, 6.3388758248682}; 
	precision upBound[6] = {0, 3.0, M_PI/3.0, 1.0, 3.5, 2.5};
	precision lowBound[6] = {0, 0, 0, -2, 0, 0.1};
	int function = 5;
	precision error = 0.02;
	cout << "n & Trap & Midpoint & Open 2 & Simpson & Gauss \\\\ " << endl;
	cout << " \\hline " << endl; 
	cout << "Exact = " << actual[function] << endl;
	cout << "Iteration & Sub-Intervals & Error \\\\ " << endl;

	for(int j=4; j < 5; j++){
		int numMesh = intervals[j] + 1;
		precision dx = (upBound[function] - lowBound[function])/(numMesh-1);
		precision xMesh[numMesh];
		for (int i = 0; i < numMesh; i++){
			xMesh[i] = lowBound[function] + i*dx;
		}
		// cout << " n = " << intervals[j];
		// cout << "T = " << trapRule(numMesh, xMesh, function) << endl;
		// cout << "M = " << midPointRule(numMesh, xMesh, function) << endl;
		// cout << "O = " << openRule2(numMesh, xMesh, function) << endl;
		// cout << "S = " << simpsonRule(numMesh, xMesh, function) << endl;
		// cout << "G = " << gaussLegendreRule(numMesh, xMesh, function) << endl;

		cout << intervals[j];
		cout << " & " << fabs(actual[function] - trapRule(numMesh, xMesh, function)) ;
		cout << " & " << fabs(actual[function] - midPointRule(numMesh, xMesh, function)) ;
		cout << " & " << fabs(actual[function] - openRule2(numMesh, xMesh, function)) ;
		cout << " & " << fabs(actual[function] - simpsonRule(numMesh, xMesh, function)) ;
		cout << " & " << fabs(actual[function] - gaussLegendreRule(numMesh, xMesh, function)) << " \\\\ " << endl;

		// cout << " \\hline " << endl; 
		// trapRule(numMesh, xMesh, function, error, actual[function]);
		// cout << " \\hline " << endl; 
		// midPointRule(numMesh, xMesh, function, error, actual[function]);
		// cout << " \\hline " << endl; 
		// openRule2(numMesh, xMesh, function, error, actual[function]);
		// cout << " \\hline " << endl; 
		// simpsonRule(numMesh, xMesh, function, error, actual[function]);
		// cout << " \\hline " << endl; 
		// gaussLegendreRule(numMesh, xMesh, function, error, actual[function]);

	}
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


// h is dx/2. it is the distance to midpoint of each subinterval
precision simpsonRule(int numMesh, precision * xMesh, int function){
	precision h = 0.5*(xMesh[numMesh-1] - xMesh[0])/(numMesh-1);
	precision sum = exactEval(xMesh[0], function)+exactEval(xMesh[numMesh-1], function);
	for(int i=1; i < 2*numMesh-2; i++){
		sum = sum + 2*(1+i%2)*exactEval(xMesh[0] + i*h, function);
	}
	sum = sum*h/3;
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


precision midPointRule(int numMesh, precision * xMesh, int function){
	precision dx = (xMesh[numMesh-1] - xMesh[0])/(numMesh-1);
	precision h = dx/2.0;
	precision sum = 0;
	for (int i=0; i < numMesh-1; i++){
		sum = sum + exactEval(xMesh[i]+h, function);
	}
	sum = dx*sum;
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


precision openRule2(int numMesh, precision * xMesh, int function){
	precision dx = (xMesh[numMesh-1] - xMesh[0])/(numMesh-1);
	precision h = dx/3.0;
	precision sum = 0;
	for(int i=0; i < numMesh-1; i++){
		sum = sum + exactEval(xMesh[i]+h, function) + exactEval(xMesh[i]+2.0*h, function);
	}
	sum = dx/2.0*sum;
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


precision gaussLegendreRule(int numMesh, precision * xMesh, int function){
	precision sum;
	for(int i=1; i<numMesh; i++){
		precision x1 = xMesh[i] + (xMesh[i] - xMesh[i-1])*(-pow(3, -0.5)-1)/2.0;
		precision x2 = xMesh[i] + (xMesh[i] - xMesh[i-1])*(pow(3, -0.5)-1)/2.0;
		sum = sum + exactEval(x1, function) + exactEval(x2, function);
	}
	sum = (xMesh[numMesh-1]-xMesh[0])/(2.0*(numMesh-1))*sum;
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


// In this dx is the distance on the x-axis between each new evaluation being used in this iteration
precision trapRule(int numMesh, precision * xMesh, int function, precision e, precision actual){
	cout << " & Trapezoidal Rule & " << " \\\\" << endl;
	precision dx = (xMesh[numMesh-1]-xMesh[0])/(numMesh-1);
	precision sum = trapRule(numMesh, xMesh, function);
	// cout << "Iteration " << 0 << ": h = " << dx << ": Sum = " << sum << endl;
	cout << 0 << " & " << 1 << " &  " << fabs(sum-actual) << " \\\\" << endl;
	int iterationCount = 1;
	while (fabs(sum-actual) > e){

		// The new evaluations start at a + 0.5*dx to the last start. After though each new eval goes by dx spacing.
		precision newEvalSum = 0;
		for(int i=0; i < pow(2.0, iterationCount-1)*(numMesh-1); i++){
			newEvalSum = newEvalSum + exactEval(xMesh[0] + 0.5*dx + i*dx, function) ;
		}

		// Then get the new dx and multiply it by 
		dx = 0.5*dx;
		newEvalSum = dx*newEvalSum ;
		sum = sum/2.0 + newEvalSum;
		// cout << "Iteration " << iterationCount << ": h = " << dx << ": Sum = " << sum << endl;
		cout << iterationCount << " & " << pow(2, iterationCount) << " & " << fabs(sum-actual) << " \\\\" << endl;
		iterationCount++;
	}
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


// In this dx is the distance on the x-axis between each evaluation being used in this iteration
precision simpsonRule(int numMesh, precision * xMesh, int function, precision e, precision actual){
	cout << " & Simpson Rule & " << " \\\\" << endl;
	int j = 0;
	precision dx = 0.5*(xMesh[numMesh-1]-xMesh[0])/(numMesh-1);
	precision eval;
	precision nockOffSum = 0;

	// This next for loop finds simpsons rule with the given mesh and prepares nockOffSum to bring 4*f down to 2*f for next iteration if needed.
	precision sum = exactEval(xMesh[0], function);
	for(int i=1; i < 2*numMesh-2; i++){
		eval = exactEval(xMesh[0] + i*dx, function);
		sum = sum + 2*(1+i%2)*eval;
		if(i%2 == 1){
			nockOffSum = nockOffSum + eval;
		}
	}
	sum = sum + exactEval(xMesh[numMesh-1], function);
	sum = sum*dx/3;
	//cout << "Iteration " << 0 << ": h = " << dx << ": Sum = " << sum << endl;
	cout << 0 << " & " << 1 << " & " << fabs(sum-actual) << " \\\\" << endl;


	// This if statement checks if 1st try is good enough, if it is not then it makes the
	// 4*ab in the parantheses go down to 2*ab as in the next iteration it will need to be 2*ab
	if(fabs(sum-actual) > e){		
		sum = sum - dx/3.0*2.0*nockOffSum;
		j = 1;
	}

	// This while loop is refinement process. 
	// It first calculates simpsons rule for new set of subintervals while using the old set,
	// then at the end checks if the sum is within the tolerance given. If it is not then it
	// prepares the next iteration by making all new 4*f add ons down to 2*f as it will be that in next iteration.
	int iterationCount = 1;
	while (j == 1){		
		sum = sum/2.0;				

		// This for loop adds in the new evals together.		
		precision newEvalSum = 0;				
		precision newEvalStart = xMesh[0] + 0.5*dx;
		nockOffSum = 0;
		for(int i = 0; i < pow(2, iterationCount)*(numMesh-1); i++){
			eval = exactEval(newEvalStart + i*dx, function);
			nockOffSum = nockOffSum + eval;
			newEvalSum = newEvalSum + eval;
		}
		dx = 0.5*dx;
		sum = sum + dx/3.0*4.0*newEvalSum;
		//cout << "Iteration " << iterationCount << ": h = " << dx << ": Sum = " << sum << endl;
		cout << iterationCount << " & " << pow(2, iterationCount) << " & " << fabs(sum-actual) << " \\\\" << endl;

		// This checks if new some is within tolerance and nocks new evals 4*f down to 2*f if it is not.
		// This is where the transformation for the next iteration actually begins, if needed.
		if(fabs(sum-actual) > e){
			sum = sum - dx/3.0*2.0*nockOffSum;
		} else {
			j = 0;
		}
		iterationCount++;
	}
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


// In this dx is the size of the sub-intevals NOT the step size for evaluations h = 0.5*dx
precision midPointRule(int numMesh, precision * xMesh, int function, precision e, precision actual){
	cout << " & Midpoint Rule & " << " \\\\" << endl;
	precision dx = (xMesh[numMesh-1]-xMesh[0])/(numMesh-1);
	precision sum = midPointRule(numMesh, xMesh, function);
	//cout << "Iteration " << 0 << ": h = " << dx << ": Sum = " << sum << endl;
	cout << 0 << " & " << 1 << " & " << fabs(sum-actual) << " \\\\" << endl;
	int iterationCount = 1;
	while (fabs(sum-actual) > e){
		sum = sum/3.0;
		dx = dx/3.0;
		precision newEvalStart = xMesh[0] + 0.5*dx;
		precision newEvalSum = exactEval(newEvalStart, function);

		// The new stuff x's are not uniform. Switching back and fourth between dx and 2*dx
		for(int i=1; i < pow(3.0, iterationCount-1)*2*(numMesh-1); i++){
			newEvalStart = newEvalStart + (1 + i%2)*dx;
			newEvalSum = newEvalSum + exactEval(newEvalStart, function);
		}
		newEvalSum = dx*newEvalSum ;
		sum = sum + newEvalSum;
		//cout << "Iteration " << iterationCount << ": h = " << dx << ": Sum = " << sum << endl;
		cout << iterationCount << " & " << pow(3, iterationCount) << " & " << fabs(sum-actual) << " \\\\" << endl;
		iterationCount++;
	}
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


// In this dx is the size of the sub-intevals NOT the step size for evaluations h = dx/3
precision openRule2(int numMesh, precision * xMesh, int function, precision e, precision actual){
	cout << " & Open Rule 2 & " << " \\\\" << endl;
	precision dx = (xMesh[numMesh-1]-xMesh[0])/(numMesh-1);
	precision sum = openRule2(numMesh, xMesh, function);
	// cout << "Iteration " << 0 << ": h = " << dx << ": Sum = " << sum << endl;
	cout << 0 << " & " << 1 << " & " << fabs(sum-actual) << " \\\\" << endl;	
	int iterationCount = 1;
	while (fabs(sum-actual) > e){
		sum = sum/2.0;
		dx = dx/2.0;
		precision newEvalStart = xMesh[0] + dx/3.0;
		precision newEvalSum = exactEval(newEvalStart, function);

		//This loop adds new stuff to the sum. new mesh being added is not uniform going by adding 4/3dx and then 2/3dx 
		for(int j=1; j < pow(2.0, iterationCount)*(numMesh-1); j++){
			newEvalStart = newEvalStart + (dx - pow(-1, j%2)*dx/3.0);
			newEvalSum = newEvalSum + exactEval(newEvalStart, function);
		}
		newEvalSum = dx/2.0*newEvalSum;
		sum = sum + newEvalSum;
		// cout << "Iteration " << iterationCount << ": h = " << dx << ": Sum = " << sum << endl;
		cout << iterationCount << " & " << pow(2, iterationCount) << " & " << fabs(sum-actual) << " \\\\" << endl;
		iterationCount++;
	}
	return sum;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////


precision gaussLegendreRule(int numMesh, precision * xMesh, int function, precision e, precision actual){
	cout << " & Gauss-Legendre Rule & " << " \\\\" << endl;
	precision sum = gaussLegendreRule(numMesh, xMesh, function);
	precision dx = (xMesh[numMesh-1]-xMesh[0])/(numMesh-1);
	// cout << "Iteration " << 0 << ": h = " << dx << ": Sum = " << sum << endl;
	cout << 0 << " & " << 1 << " & " << fabs(sum-actual) << " \\\\" << endl;
	int iterationCount = 1;
	while (fabs(sum-actual) > e){
		numMesh = numMesh*2.0-1;
		dx = dx/2.0;
		precision x1 = (xMesh[0]+dx) + ((xMesh[0]+dx) - xMesh[0])*(-pow(3, -0.5)-1)/2.0; 
		precision x2 = (xMesh[0]+dx) + ((xMesh[0]+dx) - xMesh[0])*(pow(3, -0.5)-1)/2.0;
		sum = exactEval(x1, function) + exactEval(x2, function);
		for(int i=1; i<numMesh-1; i++){
			x1 = x1 + dx;
			x2 = x2 + dx;
			sum = sum + exactEval(x1, function) + exactEval(x2, function);
		}
		sum = sum*dx/2.0;
		// cout << "Iteration " << iterationCount << ": h = " << dx << ": Sum = " << sum << endl;
		cout << iterationCount << " & " << pow(2, iterationCount) << " & " << fabs(sum-actual) << " \\\\" << endl;
		iterationCount ++;
	}
	return sum;
}

