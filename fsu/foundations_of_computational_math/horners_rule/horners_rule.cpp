


#include <limits>
#include <fstream>
#include <iostream>
using namespace std;
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>  // This is to set precision of displayed long floats


// Write the polynomial in product form here
double evalDouble(double x, int n){
	double answer = 1;
	// double y = x-2.0;  // Problem 2
	//double y = x+4.0;    // Problem 3c
	//double y = x-15.0;   // Problem 3c
	double y = x-50;     //Problem 3c
	for(int i=1; i<=n; i++){
		answer = answer*(y);
	}
	return answer;
}

// Horner's Rule Single Precision
double hornerDouble(double x, int n, double coeffs[]){
	double answer = coeffs[n] ;
	for (int i = n-1; i>=0; i--){
		answer = x*answer + coeffs[i];
	}
	return answer;
}

double forwardErrorDouble(double x, int n, double coeffs[], double u){
	double answer = fabs(coeffs[n]) ;
	for (int i = n-1; i>=0; i--){
		answer = fabs(x*answer) + fabs(coeffs[i]);
	}
	return 2*n*u/(1-n*u)*answer;
}

double runningErrorDouble(double x, int n, double coeffs[], double u){
	double beta = 0;
	double c_0 = coeffs[n];
	for(int i = n-1; i>=0; i--){
		double c_1 = c_0;
		c_0 = x*c_0 + coeffs[i];
		beta = fabs(x)*beta + fabs(x)*fabs(c_0) + fabs(c_1);
	}
	return u*beta;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


// Write the polynomial in product form here
float evalSingle(float x, int n){
	float answer = 1;
	//float y = x-2.0;  // Problem 2
	float y = x+4.0;    // Problem 3c
	//float y = x-15.0;   // Problem 3c
	//double y = x-50;     //Problem 3c
	cout << y << "\n";
	for(int i=1; i<=n; i++){
		answer = answer*(y);
		cout << answer << "\n";
	}
	return answer;
}

// Horner's Rule Single Precision
float hornerSingle(float x, int n, float coeffs[]){
	float answer = coeffs[n] ;
	//cout << answer << "\n";
	for (int i = n-1; i>=0; i--){
		//cout << x << "*" << answer << "+" << coeffs[i] <<" = ";
		answer = x*answer + coeffs[i];
		//cout << answer << "\n";
	}
	return answer;
}

float forwardErrorSingle(float x, int n, float coeffs[], float u){
	float answer = fabs(coeffs[n]) ;
	//cout << answer << "\n";
	for (int i = n-1; i>=0; i--){
		//cout << x << "*" << answer << "+" << coeffs[i] <<" = ";
		answer = fabs(x*answer) + fabs(coeffs[i]);
		//cout << answer << "\n";
	}
	// cout << answer << ", " << 2*n*u/(1-n*u) << "\n";
	return 2*n*u/(1-n*u)*answer;
}

float runningErrorSingle(float x, int n, float coeffs[], float u){
	float beta = 0;
	float c_0 = coeffs[n];
	for(int i = n-1; i>=0; i--){
		float c_1 = c_0;
		c_0 = x*c_0 + coeffs[i];
		beta = fabs(x)*beta + fabs(x)*fabs(c_0) + fabs(c_1);
	}
	// cout << beta << ", " << u << "\n";
	return u*beta;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


int main(){

	fstream fout;
	fout.open("../data/data.txt", ios_base::out);
	// fout.open("../data/dataP2b.txt", ios_base::out);
	// fout.open("../data/dataDouble.txt", ios_base::out);
	// fout.open("../data/dataP3c1.txt", ios_base::out);
	// fout.open("../data/dataP3c2.txt", ios_base::out);
	// fout.open("../data/dataP3c3.txt", ios_base::out);

	char answer; 
	cout << "Single or Double Precision for Horner's rule and Both Errors? Type 'S' for Single or 'D' for double: ";
	cin >> answer;
	int n;
	cout << "what degree is the polynomial you are working with? ";
	cin >> n;

	// Want to hardcode the single or double and the degree of the polynomial
	// char answer = 'S';
	// int n = 4; 

	if(answer == 'S' || answer == 's'){
		// The next 14 lines are to get info from user. Comment out if you are hardcoding info in.
		float coeffs[n+1];
		for(int i=0; i<=n; i++){
			cout << "coefficient of x^" << i << " = ";
			cin >> coeffs[i];
		}
		float upBound;
		cout << "What upper bound do you want for evaluation? ";
		cin >> upBound;
		float lowBound;
		cout << "What lower bound do you want for evaluation? ";
		cin >> lowBound;
		int numberPoints;
		cout << "How many points do you want evaluated between those bounds? ";
		cin >> numberPoints;

		// These are if you want to hardcode info into the computer
		// float coeffs[n+1] = {};
		// float lowBound = 49.9;
		// float upBound = 50.1;
		// int numberPoints = 50;

		// These next few lines are if you just want to hardcode the coefficients and 
		// degree of the polynomial directly into the code
		// Put these in order of least degree to greatest
		// float coeffs[n+1] = {-512, 2304, -4608, 5376, -4032, 2016, -672, 144, -18, 1};  // Problem 2
		// float coeffs[n+1] = {65536, 131072, 114688, 57344, 17920, 3584, 448, 32, 1};     // Problem 3c
		// float coeffs[n+1] = {50625, -13500, 1350, -60, 1};                     // Problem 3c
		// float coeffs[n+1] = {6250000, -500000, 15000, -200, 1};               // Problem 3c

		float dx = (upBound-lowBound)/numberPoints;

		for (int i=0; i<=numberPoints; i++){
			float u = numeric_limits<float>::epsilon();     
			double exact = evalDouble(lowBound+i*dx, n);         // This is for P2a
			// float exact = evalSingle(lowBound+i*dx);          // This is for P2b
			float fError = forwardErrorSingle(lowBound+i*dx, n, coeffs, u); 
			float horner = hornerSingle(lowBound+i*dx, n, coeffs);
			float runError = runningErrorSingle(lowBound+i*dx, n, coeffs, u);

			// Thus every 4 lines is the information evaluated at the next x coordinate.
			// fout << "horners = " << horner << ", fError = " << fError<< ", runError = " << runError << "\n";
			
			fout << setprecision(7) << exact << "\n" << horner << "\n" << fError << "\n" << runError << "\n";
			// cout << setprecision(7) << exact << "\n" << horner << "\n" << fError << "\n" << runError << "\n";	
		}

	} else {
		// The next 14 lines are to get info from user. Comment out if you are hardcoding info in.
		double coeffs[n+1];
		for(int i=0; i<=n; i++){
			cout << "coefficient of x^" << i << " = ";
			cin >> coeffs[i];
		}
		double upBound;
		cout << "What upper bound do you want for evaluation? ";
		cin >> upBound;
		double lowBound;
		cout << "What lower bound do you want for evaluation? ";
		cin >> lowBound;
		int numberPoints;
		cout << "How many points do you want evaluated between those bounds? ";
		cin >> numberPoints;

		// These are if you want to hardcode info into the computer
		// double coeffs[n+1] = {};
		// double lowBound = 49.9;
		// double upBound = 50.1;
		// int numberPoints = 50;

		// These next few lines are if you just want to hardcode the coefficients and 
		// degree of the polynomial directly into the code
		// Put these in order of least degree to greatest
		// double coeffs[n+1] = {-512, 2304, -4608, 5376, -4032, 2016, -672, 144, -18, 1};  // Problem 2
		// double coeffs[n+1] = {65536, 131072, 114688, 57344, 17920, 3584, 448, 32, 1};     // Problem 3c
		// double coeffs[n+1] = {50625, -13500, 1350, -60, 1};                     // Problem 3c
		// double coeffs[n+1] = {6250000, -500000, 15000, -200, 1};               // Problem 3c
		
		double dx = (upBound-lowBound)/numberPoints;

		for (int i=0; i<=numberPoints; i++){
			double u = numeric_limits<double>::epsilon();
			double exact = evalDouble(lowBound+i*dx, n);
			double fError = forwardErrorDouble(lowBound+i*dx, n, coeffs, u);
			double horner = hornerDouble(lowBound+i*dx, n, coeffs);
			double runError = runningErrorDouble(lowBound+i*dx, n, coeffs, u);
			// fout << "horners = " << horner << ", fError = " << fError<< ", runError = " << runError << "\n";
			// Thus every 4 lines is the information evaluated at the next x coordinate.
			fout << exact << "\n" << horner << "\n" << fError << "\n" << runError << "\n";
		}
	}	

	return 0;
}
