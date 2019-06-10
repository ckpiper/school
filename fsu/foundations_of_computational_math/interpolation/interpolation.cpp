
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


// This is for exact evaluations of functions
double exactEval(double x){
	double alpha = 15;
	double eval = 1.0/x + x ;
	// double  eval = 1.0/(1.0+alpha*x*x);
	// double eval = fabs(alpha*x) + x/2.0 -x*x;
	// double eval = 1.0/(pow(x, 0.5));
	return eval;
}

void dividedDifference(precision *mesh, precision *yVals, precision *divDiff, int length);
precision newtonFormEval(precision *mesh, precision *yVals, int lengthInterPoints, precision *xx, int graphPoints);

void bubbleSort(precision *xVals, precision *yVals, int interpolPoints);

void piecewisePolynomialEval(int degree, int interpolPoints, precision *xVals, precision *yVals, precision *xx, int graphPoints);

void triDiagMat(int n, int boundary, precision *mew, precision *lambda, precision *d, precision *m);
void splineEval(int boundary, int interpolPoints, precision *xVals, precision *yVals, precision *xx, int graphPoints);

void triDiagMat(int n, int boundary, precision h, precision * f, precision * alpha);
precision basisPolyEval(precision xim2, precision xim1, precision xi, precision xip1, precision xip2, precision x, precision h);
void bSplineEval(int boundary, int interpolPoints, precision *xVals, precision *yVals, precision *xx, int graphPoints);

precision bernsteinPolyEval(int n, precision *yVals, precision a, precision b, precision x);
void bernsteinFuncEval(int n, precision *yVals, precision a, precision b);


int main(){
	// char answerPoly;
	// cout << "What type of interpolating Polynomial do you want to use? Type 'G' for a global interpolating polynomial, 'P' for a piecewise polynomial, and 'S' for a spline. ";
	// cin >> answerPoly;
	// answerPoly = 'p';

	// int interpolPoints, graphPoints;
	// precision xVals[interpolPoints], yVals[interpolPoints];
	// precision upBound, lowBound;
	// cout << "How many points are you going to interpolate? ";
	// cin >> interpolPoints;
	// cout << "How many points do you want evaluated for this approximated Polynomial? ";
	// cin >> graphPoints;

	precision upBound = 5;
	precision lowBound = 0.1;
	int graphPoints = 101;
	precision graphdx = (upBound-lowBound)/(graphPoints-1);
	int interpolPoints = 8;
	precision interdx = (upBound-lowBound)/(interpolPoints-1);
	precision xmesh[interpolPoints];
	precision ymesh[interpolPoints];

	for(int i=0; i<interpolPoints; i++){
		xmesh[i] = lowBound+i*interdx;
		cout << xmesh[i] << endl;
		ymesh[i] = exactEval(xmesh[i]);
	}
	precision xGraphVals[graphPoints];

	fstream fout;
	fout.open("../data/exactEval.txt", ios_base::out);
	for (int i = 0; i < graphPoints; i++){
		xGraphVals[i] = lowBound + i*graphdx;
		fout << exactEval(xGraphVals[i]) << endl;
	}

	splineEval(1, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);
	bSplineEval(1, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);


	// if(answerPoly == 'P' || answerPoly == 'p'){
	// 	int degree; 
	// 	cout << "What degree polynomials do you want with you piecewise function? ";
	// 	cin >> degree;
	// 	piecewisePolynomialEval(degree, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);
	// } else if(answerPoly == 'G' || answerPoly == 'g'){
	// 	newtonFormEval(xmesh, ymesh, interpolPoints, xGraphVals, graphPoints);
	// } else if(answerPoly == 'S' || answerPoly == 's'){
	// 	splineEval(1, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);
	// }
	// int degree = 2;
	// splineEval(0, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);
	// piecewisePolynomialEval(degree, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);
	// newtonFormEval(xmesh, ymesh, interpolPoints, xGraphVals, graphPoints);

	// // This next stuff of code is checking bernstein polynomials
	// fstream f1out;
	// f1out.open("../data/bernsteinExperiment.txt");	
	// fstream f2out;
	// f2out.open("../data/exactEval.txt");	
	// int bernsteinDegree = 3;
	// precision yVals[bernsteinDegree+1];
	// precision funcVals15[15];
	// bernsteinFuncEval(bernsteinDegree+12, funcVals15, lowBound, upBound);
	// for (int i=0; i<= graphPoints; i++){
	// 	precision y15 = bernsteinPolyEval(bernsteinDegree+12, funcVals15, lowBound, upBound, lowBound+i*graphdx);
	// 	precision exact = exactEval(lowBound+i*graphdx);
	// 	f1out << y15 << '\n';
	// 	f2out << exact << "\n" ;
	// }
	// f1out.close();
	// f2out.close();

	// ifstream fDemoIn1;
	// fDemoIn1.open("../data/1_cx.txt", ios_base::in);
	// ifstream fDemoIn2;
	// fDemoIn2.open("../data/1_cy.txt", ios_base::in);
	// ofstream fDemoOut;
	// fDemoOut.open("../data/demoOut.txt", ios_base::out);

	// if(fDemoIn1.fail()){
	// 	cerr << "Error Opening File" << endl;
	// 	exit(1);
	// } else {
	// 	// // This finds what the upper and lower bounds of interval are
	// 	// for(int i=0; i<=interpolPoints; i++){
	// 	// 	cout << "x_" << i << " = ";
	// 	// 	cin >> xVals[i];
	// 	// 	cout << "y_" << i << " = ";
	// 	// 	cin >> yVals[i];
	// 	// 	if(i==0){
	// 	// 		upBound = xVals[0];
	// 	// 		lowBound = xVals[0];
	// 	// 	} else {
	// 	// 		if(upBound < xVals[i])
	// 	// 			upBound = xVals[i];
	// 	// 		if(lowBound > xVals[i])
	// 	// 			lowBound = xVals[i];
	// 	// 	}
	// 	// }
	// 	precision upBound = 1;
	// 	precision lowBound = -1;
	// 	int interpolPoints = 21;
	// 	precision xmesh[interpolPoints];
	// 	precision ymesh[interpolPoints];
	// 	string fileLine;
	// 	int i = 0;
	// 	precision number ;
	// 	while ( fDemoIn1 >> number){
	// 		xmesh[i] = number;
	// 		i++;
	// 	}
	// 	i = 0;
	// 	while ( fDemoIn2 >> number){
	// 		ymesh[i] = number;
	// 		i++;
	// 	}

	// 	int graphPoints = 501;
	// 	precision graphdx = (upBound-lowBound)/(graphPoints-1);
	// 	precision xGraphVals[graphPoints];
	// 	for (int i = 0; i < graphPoints; i++){
	// 		xGraphVals[i] = lowBound + i*graphdx;
	// 	}

	// 	splineEval(1, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);
	// 	bSplineEval(1, interpolPoints, )
	// 	// piecewisePolynomialEval(degree, interpolPoints, xmesh, ymesh, xGraphVals, graphPoints);
	// 	// newtonFormEval(xmesh, ymesh, interpolPoints, xGraphVals, graphPoints);
	// }

	// fDemoIn1.close();
	// fDemoIn2.close();
	// fDemoOut.close();
	
	return 0;
}





//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////







// This will fill divDiff to look like {y[0], y[0,1], y[0,1,2], ... , y[0,1,...,n]}
void dividedDifference(precision *mesh, precision *yVals, precision *divDiff, int length){
	precision *divStart = divDiff;
	precision *meshStart = mesh;

	// This for loop initializes all of divDiff
	for(int i=0; i<length; i++){ 	
		*divDiff = *yVals;
		divDiff++;
		yVals++;
	}

	for(int i=1; i<length; i++){
		divDiff = divStart + i - 1; 	// 	The pointer needs to move back to the spot where 
		precision divDiffBehind = *divDiff;	//  the next order of divided difference begins
		precision divDiffAhead;

		// Computes the row or ith orders divided difference
		for(int j=0; j<length-i;j++){

			divDiff++;					//	This sets divDiffAhead to current spot of divDiff
			divDiffAhead = *divDiff;   	//  because we will still need it as a behind the next iteration

			*divDiff = (*divDiff-divDiffBehind)/(*(mesh+j+i)-*(mesh+j));
			divDiffBehind = divDiffAhead;
		}
	}
}

// This will evaluate the newton form of the interpolating polynomial at a specified x.
precision newtonFormEval(precision *mesh, precision *yVals, int lengthInterPoints, precision *xx, int graphPoints){
	fstream fout;
	fout.open("../data/newtonFormEvalC.txt", ios_base::out);	
	precision eval;
	precision *meshStart = mesh;			//We need to know the starting point of both array pointers
	precision divDiff[lengthInterPoints];
	dividedDifference(mesh, yVals, divDiff, lengthInterPoints);

	for(int j=0; j < graphPoints; j++){   // This iterates through the x to be evaluated at		
		mesh = meshStart;				//This sets the pointers back to the start of the array
		precision omega = 1;
		eval = 0;
		for(int i=0; i<lengthInterPoints; i++){		// This is the actual evaluation loop at a point
			eval = eval + divDiff[i]*omega;
			omega = omega*(*xx-*mesh);          	// This gets updated after because w_0(x)=1, w_1(x)=(x-x_0),  w_2(x)=(x-x_0)(x-x_1) and so on
			mesh++;
		}

		// fout <<  exactEval(*xx)-eval << '\n';
		fout << eval << '\n';
		xx++;									// This turns the pointer to the next number to be evaluated in xx
	}
	fout.close();
	return eval;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// This sorts the mesh in the correct order.
void bubbleSort(precision *xVals, precision *yVals, int interpolPoints){
	// This next for loop sorts the meshes and puts it in order of x, Bubble Sort
	precision *xValsStart = xVals; 	//We need to know the starting point of both array pointers
	precision *yValsStart = yVals;
	precision big;   
	int sortCount = 1;
	for(int j=0; j < interpolPoints-1 && sortCount > 0; j++){
		xVals = xValsStart;
		yVals = yValsStart;
		sortCount=0;
		for(int i=0; i<interpolPoints-1-j; i++){
			if(*xVals > *(xVals+1)){
				big = *xVals;
				*xVals = *(xVals+1);
				*(xVals+1) = big;
				sortCount++;
				big = *yVals;
				*yVals = *(yVals+1);
				*(yVals+1) = big;
			}
			xVals++;
			yVals++;
		}
	}
}

// This evaluates specified xx with the piecewis polynomial defined by xVals and yVals and degree
void piecewisePolynomialEval(int degree, int interpolPoints, precision *xVals, precision *yVals, precision *xx, int graphPoints){
	precision eval;
	// This first if decides if you can or cannot perform a piecewise polynomial with polys of the degree
	// If you cannot make this than it asks you to give a new degree and uses recursion to check again.
	if(interpolPoints % degree != 1 && degree != 1){
		cout << "You cannot have this degree polynomial with the amount of interpolating points. Pick a new degree. ";
		cin >> degree;
		piecewisePolynomialEval(degree, interpolPoints, xVals, yVals, xx, graphPoints);
	} else {
		fstream fout;
		fout.open("../data/piecewisePolynomialEval.txt", ios_base::out);	
		precision *xValsStart = xVals; 	//We need to know the starting point of both array pointers
		precision *yValsStart = yVals;
		bubbleSort(xVals, yVals, interpolPoints);
		for(int j=0; j < graphPoints; j++){   // This iterates through the x to be evaluated at
			int count = 0;
			xVals = xValsStart;		//This sets the pointers back to the start of the array
			yVals = yValsStart;
			while(*xx > *xVals){		// This finds the first xVal that is bigger than x
				xVals++;
				count++;
			}
			if(count % degree != 0){	  	// This puts the pointer of xVals back to the start of the subinterval
				xVals = xVals - count % degree;
				count = count - count % degree;
			} else if(count != 0) {
				xVals = xVals - degree;
				count = count - degree;
			}
			yVals = yVals + count;			// This puts the pointer of yVals to the start of the sub interval
			precision subXVals[degree+1], subYVals[degree+1];
			for(int i = 0; i <= degree; i++){  		// This fills in the sub arrays that hold the interpolPoints in the interval
				subXVals[i] = *xVals;
				subYVals[i] = *yVals;
				xVals++;
				yVals++;
			}
			// precision divDiff[degree+1];
			precision x[1] = {*xx};
			precision x1 = *xx ;
			eval = newtonFormEval(subXVals, subYVals, degree+1, x, 1);
			// fout <<  exactEval(x1)-eval << '\n';
			fout << eval << '\n';
			xx++;
		}
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// This solves the tridiagonal matrix using Thomas's Algorithm
void triDiagMat(int n, int boundary, precision *mew, precision *lambda, precision *d, precision *m){
	if(boundary == 0 || boundary == 2){
		lambda[1] = lambda[1]/2;
		d[1] = d[1]/2;
		for(int i=2; i<n-1; i++){
			lambda[i] = lambda[i]/(2-mew[i]*lambda[i-1]);
			d[i] = (d[i]-mew[i]*d[i-1])/(2-mew[i]*lambda[i-1]);
		}
		d[n-1] = (d[n-1]-mew[n-1]*d[n-2])/(2-mew[n-1]*lambda[n-2]);
		m[n-1] = d[n-1];
		for(int i=n-2; i>=1; i--){
			m[i] = d[i]-lambda[i]*m[i+1];
		}
	} else {
		lambda[0] = lambda[0]/2;
		d[0] = d[0]/2;
		for(int i=1; i<n; i++){
			lambda[i] = lambda[i]/(2-mew[i]*lambda[i-1]);
			d[i] = (d[i]-mew[i]*d[i-1])/(2-mew[i]*lambda[i-1]);
		}
		d[n] = (d[n]-mew[n]*d[n-1])/(2-mew[n]*lambda[n-1]);
		m[n] = d[n];
		for(int i=n-1; i>=0; i--){
			m[i] = d[i]-lambda[i]*m[i+1];
		}
	}
}

// This evaluates specified xx with splines defined by xVals and yVals
void splineEval(int boundary, int interpolPoints, precision *xVals, precision *yVals, precision *xx, int graphPoints){
	fstream fout;
	int n = interpolPoints-1;
	fout.open("../data/splinePolynomialEval.txt", ios_base::out);	
	precision *xValsStart = xVals; 	//We need to know the starting point of both array pointers
	precision *yValsStart = yVals;
	bubbleSort(xVals, yVals, interpolPoints);
	precision d[n+1], lambda[n], mew[n+1], m[n+1], gam[n], gamTil[n], h;

	// Computes mew, lambda, and d values
	for(int i=1; i<=n-1; i++){
		mew[i] = (*(xVals+1)-*xVals)/(*(xVals+2)-*xVals);
		lambda[i] = (*(xVals+2)-*(xVals+1))/(*(xVals+2)-*xVals);
		d[i] = 6.0*(  ( (*(yVals+2)-*(yVals+1))/(*(xVals+2)-*(xVals+1)) - (*(yVals+1)-*yVals)/(*(xVals+1)-*xVals) ) / (*(xVals+2)-*xVals)  );
						/////////////////////////////////////////////////////////////////////////////////////////////   ///////////////////
		xVals++;
		yVals++;
	}
	xVals = xValsStart;
	yVals = yValsStart;

	// Check for Boundary Conditions
	if(boundary == 0){
		m[0] = 0;
		m[n] = 0;
	} else if (boundary ==1) {
		precision f1a = 0;
		precision f1b = 0;
		precision h1 = xVals[1]-xVals[0];
		precision hn = xVals[n]-xVals[n-1];
		lambda[0] = 1;
		mew[n] = 1;
		d[0] = 6*((yVals[1]-yVals[0])/h1 - f1a) / h1;
		d[n] = 6*(f1b - (yVals[n]-yVals[n-1])/hn) / hn;
	} else if(boundary == 2){
		m[0] = -2;
		m[n] = -2;
		d[1] = d[1] - mew[1]*m[0];
		d[n] = d[n] - lambda[n-1]*m[n];
	}

	// Solves for m and tridiagonal matrix
	triDiagMat(n, boundary, mew, lambda, d, m);

	// Solves for gamma and gamma tilde
	for(int i=1; i<=n; i++){
		h = xVals[i]-xVals[i-1];
		gamTil[i-1] = yVals[i-1] - m[i-1]*h*h/6;
		gam[i-1] = (yVals[i]-yVals[i-1])/h - h*(m[i]-m[i-1])/6;
	}	

	// Gives evalations at the specified x
	for (int i=0; i < graphPoints; i++){
		int j = 0;
		while (xx[i] > xVals[j]){
			j++;
		}
		if(j == 0){j++;}
		h = xVals[j]-xVals[j-1];
		precision eval = m[j-1]*pow((xVals[j]-xx[i]), 3)/(6*h) + m[j]*pow((xx[i]-xVals[j-1]), 3)/(6*h) + gam[j-1]*(xx[i]-xVals[j-1]) + gamTil[j-1];
		// precision exact = exactEval(xx[i]);
		// fout << exactEval(xx[i])-eval << endl;
		fout << eval << '\n';
	}

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void triDiagMat(int n, int boundary, precision h, precision * f, precision * alpha){
	precision c[n+3];
	if(boundary == 1){
		// This will fill the modified c array for thomas algorithm
		c[0] = 2.0;
		for(int i = 1; i < n+2; i++){
			c[i] = 1.0/(4.0-c[i-1]) ;
		}
		c[n+2] = 0;

		// for(int i=0; i<= n+2; i++){ cout << c[i] << endl; }
		// cout << "----------" << endl;

		// This then fills the modified f array for thomas algorithm
		f[0] = -f[0]*h/(6.0);
		for(int i = 1; i <= n+1; i++){
			f[i] = (f[i]-f[i-1])/(4.0-c[i-1]);
		}
		f[n+2] = (f[n+2] - 12.0*f[n+1]/h) / (6.0-12.0*c[n+1]) * h;

		// for(int i=0; i<= n+2; i++){ cout << f[i] << endl; }
		// cout << "----------" << endl;

		// This uses the back substitution of thomas algorithm to get the alphas
		alpha[n+1] = (f[n+2] - f[n+1])/(3.0/h - (3+h)/c[n+1]);
		alpha[n+2] = f[n+2] - 3.0/h * alpha[n+1];
		for(int i = n; i>= 1; i--){
			alpha[i] = f[i] - c[i]*alpha[i+1];
		}
		alpha[0] = 3*alpha[1]/h + f[0]  - c[0]*alpha[1];

		// for(int i=0; i<= n+2; i++){ cout << alpha[i] << endl; }
		// cout << "----------" << endl;
	}

}


precision basisPolyEval(precision xim2, precision xim1, precision xi, precision xip1, precision xip2, precision x, precision h){
	precision eval;
	if(xim2 <= x && x <= xim1){
		eval = pow(x - xim2, 3)/(h*h*h);
	} else if(xim1 <= x && x <= xi){
		eval = ( 1 + 3*(x - xim1)/h + 3*pow(x - xim1, 2)/(h*h) - 3*pow(x - xim1, 3)/(h*h*h)  );
	} else if(xi <= x && x <= xip1){
		eval = ( 1 + 3*(xip1 - x)/h + 3*pow(xip1 - x, 2)/(h*h) - 3*pow(xip1 - x, 3)/(h*h*h)  );
	} else if(xip1 <= x && x <= xip2){
		eval = pow(xip2 - x, 3)/(h*h*h);
	}
	return eval;
}


void bSplineEval(int boundary, int interpolPoints, precision *xVals, precision *yVals, precision *xx, int graphPoints){
	fstream fout;
	int n = interpolPoints-1;
	fout.open("../data/bSplinePolynomialEval.txt", ios_base::out);	
	bubbleSort(xVals, yVals, interpolPoints);
	precision h = xVals[1] - xVals[0];
	precision xnm1 = xx[0] - h;
	precision xnm2 = xnm1 - h;
	precision xnp1 = xx[interpolPoints-1] + h;
	precision xnp2 = xnp1 + h;
	precision alpha[n+3], f[n+3];

	// This for loop puts the yVals in the function evals array in correct positions
	for(int i = 1; i <= interpolPoints; i++){
		f[i] = yVals[i-1];
	}

	// This emposes the boundary conditions
	if(boundary == 0){
		f[0] = 0;
		f[n+2] = 0;
	} else if (boundary ==1) {
		f[0] = 0;
		f[n+2] = 0;
		// The next to modifies them to make matrix into tridiagonal matrix
		f[0] = f[0] - 3.0*f[1]/h;
		f[n+2] = f[n+2] + 3.0*f[n+1]/h;
	} else if(boundary == 2){
		f[0] = -7.5;
		f[n+2] = 8.5;
	}

	// Solves for all the alphas
	triDiagMat(n, boundary, h, f, alpha);
	// for(int i=0; i<=n+2; i++){ cout << alpha[i] << endl;}

	// Produces evaluations for the specified x.
	// i starts at 1 because index goes from 0 -> n+2 instead of -1 -> n+1
	// int i = 1;
	// for (int j=0; j < graphPoints; j++){
	// 	precision dx = 
	// 	precision eval = 0;
	// 	eval = eval + alpha[i-1] * 

	// 	if(xx[j+1] >= )
	// }

	for(int j=0; j < graphPoints; j++){
		precision eval = 0;
		eval = eval + alpha[0] * basisPolyEval(xnm2-h, xnm2, xnm1, xVals[0], xVals[1], xx[j], h);
		eval = eval + alpha[1] * basisPolyEval(xnm2, xnm1, xVals[0], xVals[1], xVals[2], xx[j], h);
		eval = eval + alpha[2] * basisPolyEval(xnm1, xVals[0], xVals[1], xVals[2], xVals[3], xx[j], h);

		// The alphas start at alpha_{-1} where basisPoly starts at B_0		
		for (int i=2; i <= n-1; i++){ // In notes it goes from -1 -> n+1
			eval = eval + alpha[i+1] * basisPolyEval(xVals[i-2], xVals[i-1], xVals[i], xVals[i+1], xVals[i+2], xx[j], h);
		}

		eval = eval + alpha[n] * basisPolyEval(xVals[n-3], xVals[n-1], xVals[n-1], xVals[n], xnp1, xx[j], h);
		eval = eval + alpha[n+1] * basisPolyEval(xVals[n-2], xVals[n-1], xVals[n], xnp1, xnp2, xx[j], h);
		eval = eval + alpha[n+2] * basisPolyEval(xVals[n-1], xVals[n], xnp1, xnp2, xnp2+h, xx[j], h);
		fout << eval << '\n';
	}


}
 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// This will evaluate the Bernstein Polynomial on the interval [a,b] at a specific x.
// n is the degree of bernstein poly
precision bernsteinPolyEval(int n, precision *yVals, precision a, precision b, precision x){
	precision p2[n+1];
	p2[0] = 1;						//	p2 is the (1-(x-a)/(b-a))^(n-k) term in poly
	precision combinat[n+1];
	combinat[0] = 1;				//	combinat contains all factorials up to n
	precision c = (x-a)/(b-a);
	for(int i=1; i <= n; i++){		// This for loop fills p2 and combinat
		p2[i] = p2[i-1]*(1-c);
		combinat[i] = combinat[i-1]*i;
	}

	precision p1 = 1;					// p1 will represent ((x-a)/(b-a))^k
	precision eval = 0;
	for(int i=0; i <= n; i++){
		eval = eval + *yVals*combinat[n]/(combinat[i]*combinat[n-i])*p1*p2[n-i];
		p1 = p1*c;
		yVals++;
	}

	return eval;
}

// Evaluates a function at the required mesh for the bernstein polynomail
void bernsteinFuncEval(int n, precision *yVals, precision a, precision b){
	precision c = (b-a);
	for(int i=0; i <= n; i++){
		precision x = i*c/n+a;
		*yVals = exactEval(x);
		yVals++;
	}
}


