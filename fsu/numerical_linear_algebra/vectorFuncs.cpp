#include <limits>
#include <fstream>
#include <iostream>
using namespace std;
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iomanip>  // This is to set precision of displayed long floats


// g++ -c header.cpp
// ar rvs header.a header.o
// g++ main.cpp header.a

// g++ -c vectorFuncs.cpp								This compiles the library and makes vectorFuncs.o (the object code of vectorFuncs)
// ar rvs vectorFuncs.a vectorFuncs.o 					This then makes vectorFuncs.a, which is the actual static library to use
// g++ main.cpp vectorFuncs.a 							This is when you compile the code which uses the library 
	// Be sure to have #include "vectorFuncs.a" in the code if the main.cpp is in the same directory.
	// You must use the quotation marks instead of the angle brackets 

// g++ main.cpp ../vectorFuncs.a  if it is in one directory higher 
	// #include "../vectorFuncs.a" and
	
// You only need to run (g++ -c header.cpp) and (ar rvs header.a header.o) once to make the header.a code then you only
	// need to do those again if you add more functions to the library or change something in them


void print(vector<int> v){
	int length = v.size();
		cout << "[";
	for(int i = 0; i < length-1; i++){
		cout << v[i] << ", ";
	}
	if(length !=0){
		cout << v[length-1] << "]" << endl << endl;
	} else{
		cout << " ]" << endl;
	}
}
void print(vector<float> v){
	cout.precision(4);
	int length = v.size();
		cout << "[";
	for(int i = 0; i < length-1; i++){
		cout << v[i] << ", ";
	}
	if(length !=0){
		cout << v[length-1] << "]" << endl << endl;
	} else{
		cout << " ]" << endl;
	}
}
void print(vector<double> v){
	int length = v.size();
		cout << "[";
	for(int i = 0; i < length-1; i++){
		cout << v[i] << ", ";
	}	
	if(length !=0){
		cout << v[length-1] << "]" << endl << endl;
	} else{
		cout << " ]" << endl;
	}
}


void print(vector<vector<int>> A){
	int n = A.size();
	cout << endl << "[" << endl;
	for(int i=0; i<n; i++){
		int m = A[i].size();
		cout << " [";
		for(int j=0; j<m-1; j++){
			cout << A[i][j] << ", ";
		}
		cout << A[i][m-1] << "]," << endl;
	}
	cout << "]" << endl << endl;
}
void print(vector<vector<float>> A){
	cout.precision(4);
	int n = A.size();
	cout << endl << "[" << endl;
	for(int i=0; i<n; i++){
		int m = A[i].size();
		cout << " [";
		for(int j=0; j<m-1; j++){
			cout << A[i][j] << ", ";
		}
		cout << A[i][m-1] << "]," << endl;
	}
	cout << "]" << endl<< endl;
}
void print(vector<vector<double>> A){
	cout.precision(8);
	int n = A.size();
	cout << endl << "[" << endl;
	for(int i=0; i<n; i++){
		int m = A[i].size();
		cout << " [";
		for(int j=0; j<m-1; j++){
			cout << A[i][j] << ", ";
		}
		cout << A[i][m-1] << "]," << endl;
	}
	cout << "]" << endl << endl;
}


int isRectangular(vector<vector<int>> A){
	int n = A.size();
	int m = A[0].size();
	for(int i=1; i<=n-1; i++){
		if(m != A[i].size()){
			return 1;
		}
	}
	return 0;
}
int isRectangular(vector<vector<float>> A){
	int n = A.size();
	int m = A[0].size();
	for(int i=1; i<=n-1; i++){
		if(m != A[i].size()){
			return 1;
		}
	}
	return 0;
}
int isRectangular(vector<vector<double>> A){
	int n = A.size();
	int m = A[0].size();
	for(int i=1; i<=n-1; i++){
		if(m != A[i].size()){
			return 1;
		}
	}
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



vector<int> add(vector<int> x, vector<int> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<int>();
	}
	for(int i=0; i<=n-1; i++){
		x[i] = x[i] + y[i];
	}
	return x;
}
vector<float> add(vector<float> x, vector<float> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<float>();
	}
	for(int i=0; i<=n-1; i++){
		x[i] = x[i] + y[i];
	}
	return x;
}
vector<double> add(vector<double> x, vector<double> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<double>();
	}
	for(int i=0; i<=n-1; i++){
		x[i] = x[i] + y[i];
	}
	return x;
}


vector<vector<int>> add(vector<vector<int>> A, vector<vector<int>> B){
	int n = A.size();
	int n1 = B.size();
	if(n != n1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
		cout << "First 2D-Vectors has " << n << " rows" << endl;
		cout << "Second 2D-Vectors has " << n1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<vector<int>>({});
	}
	for(int i=0; i<=n-1; i++){
		int m = A[i].size();
		int m1 = B[i].size();
		if(m != m1){
			cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
			cout << "First 2D-Vectors has " << m << " columns" << endl;
			cout << "Second 2D-Vectors has " << m1 << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			return vector<vector<int>>({});
		}
		for(int j=0; j<=m-1; j++){
			A[i][j] = A[i][j] + B[i][j];
		}
	}
	return A;
}
vector<vector<float>> add(vector<vector<float>> A, vector<vector<float>> B){
	int n = A.size();
	int n1 = B.size();
	if(n != n1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
		cout << "First 2D-Vector has " << n << " rows" << endl;
		cout << "Second 2D-Vector has " << n1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<vector<float>>({});
	}
	for(int i=0; i<=n-1; i++){
		int m = A[i].size();
		int m1 = B[i].size();
		if(m != m1){
			cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
			cout << "First 2D-Vector has " << m << " columns" << endl;
			cout << "Second 2D-Vector has " << m1 << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			return vector<vector<float>>({});
		}
		for(int j=0; j<=m-1; j++){
			A[i][j] = A[i][j] + B[i][j];
		}
	}
	return A;
}
vector<vector<double>> add(vector<vector<double>> A, vector<vector<double>> B){
	int n = A.size();
	int n1 = B.size();
	if(n != n1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
		cout << "First 2D-Vector has " << n << " rows" << endl;
		cout << "Second 2D-Vector has " << n1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<vector<double>>({});
	}
	for(int i=0; i<=n-1; i++){
		int m = A[i].size();
		int m1 = B[i].size();
		if(m != m1){
			cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
			cout << "First 2D-Vector has " << m << " columns" << endl;
			cout << "Second 2D-Vector has " << m1 << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			return vector<vector<double>>({});
		}
		for(int j=0; j<=m-1; j++){
			A[i][j] = A[i][j] + B[i][j];
		}
	}
	return A;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


vector<int> subtract(vector<int> x, vector<int> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<int>();
	}
	for(int i=0; i<=n-1; i++){
		x[i] = x[i] - y[i];
	}
	return x;
}
vector<float> subtract(vector<float> x, vector<float> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<float>();
	}
	for(int i=0; i<=n-1; i++){
		x[i] = x[i] - y[i];
	}
	return x;
}
vector<double> subtract(vector<double> x, vector<double> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<double>();
	}
	for(int i=0; i<=n-1; i++){
		x[i] = x[i] - y[i];
	}
	return x;
}


vector<vector<int>> subtract(vector<vector<int>> A, vector<vector<int>> B){
	int n = A.size();
	int n1 = B.size();
	if(n != n1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
		cout << "First 2D-Vector has " << n << " rows" << endl;
		cout << "Second 2D-Vector has " << n1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<vector<int>>({});
	}
	for(int i=0; i<=n-1; i++){
		int m = A[i].size();
		int m1 = B[i].size();
		if(m != m1){
			cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
			cout << "First 2D-Vector has " << m << " columns" << endl;
			cout << "Second 2D-Vector has " << m1 << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			return vector<vector<int>>({});
		}
		for(int j=0; j<=m-1; j++){
			A[i][j] = A[i][j] - B[i][j];
		}
	}
	return A;
}
vector<vector<float>> subtract(vector<vector<float>> A, vector<vector<float>> B){
	int n = A.size();
	int n1 = B.size();
	if(n != n1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
		cout << "First 2D-Vector has " << n << " rows" << endl;
		cout << "Second 2D-Vector has " << n1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<vector<float>>({});
	}
	for(int i=0; i<=n-1; i++){
		int m = A[i].size();
		int m1 = B[i].size();
		if(m != m1){
			cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
			cout << "First 2D-Vector has " << m << " columns" << endl;
			cout << "Second 2D-Vector has " << m1 << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			return vector<vector<float>>({});
		}
		for(int j=0; j<=m-1; j++){
			A[i][j] = A[i][j] - B[i][j];
		}
	}
	return A;
}
vector<vector<double>> subtract(vector<vector<double>> A, vector<vector<double>> B){
	int n = A.size();
	int n1 = B.size();
	if(n != n1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
		cout << "First 2D-Vector has " << n << " rows" << endl;
		cout << "Second 2D-Vector has " << n1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<vector<double>>({});
	}
	for(int i=0; i<=n-1; i++){
		int m = A[i].size();
		int m1 = B[i].size();
		if(m != m1){
			cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two 2D-Vectors are not the same size" << endl;
			cout << "First 2D-Vector has " << m << " columns" << endl;
			cout << "Second 2D-Vector has " << m1 << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			return vector<vector<double>>({});
		}
		for(int j=0; j<=m-1; j++){
			A[i][j] = A[i][j] - B[i][j];
		}
	}
	return A;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int innnerProduct(vector<int> x, vector<int> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return 0;
	}
	int z = 0;
	for(int i=0; i<=n-1; i++){
		z = z + x[i]*y[i];
	}
	return z;
}
float innnerProduct(vector<float> x, vector<float> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return 0;
	}
	float z = 0;
	for(int i=0; i<=n-1; i++){
		z = z + x[i]*y[i];
	}
	return z;
}
double innnerProduct(vector<double> x, vector<double> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return 0;
	}
	double z = 0;
	for(int i=0; i<=n-1; i++){
		z = z + x[i]*y[i];
	}
	return z;
}
int dotProduct(vector<int> x, vector<int> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return 0;
	}
	int z = 0;
	for(int i=0; i<=n-1; i++){
		z = z + x[i]*y[i];
	}
	return z;
}
float dotProduct(vector<float> x, vector<float> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return 0;
	}
	float z = 0;
	for(int i=0; i<=n-1; i++){
		z = z + x[i]*y[i];
	}
	return z;
}
double dotProduct(vector<double> x, vector<double> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return 0;
	}
	double z = 0;
	for(int i=0; i<=n-1; i++){
		z = z + x[i]*y[i];
	}
	return z;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



vector<int> product(vector<vector<int>> A, vector<int> v){
	int n = v.size();
	int m = A[0].size();
	vector<int> b;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return b;
	}
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The vector length = " << n << endl;
		cout << "The matrix has " << m << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return b;
	}
	m = A.size();
	for(int i=0; i<=m-1; i++){
		// b.push_back(innnerProduct(A[i], v));
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[i][j]*v[j];
		}
	}
	return b;
}
vector<float> product(vector<vector<float>> A, vector<float> v){
	int n = v.size();
	int m = A[0].size();
	vector<float> b;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return b;
	}
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The vector length = " << n << endl;
		cout << "The matrix has " << m << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return b;
	}
	m = A.size();
	for(int i=0; i<=m-1; i++){
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[i][j]*v[j];
		}
	}
	return b;
}
vector<double> product(vector<vector<double>> A, vector<double> v){
	int n = v.size();
	int m = A[0].size();
	vector<double> b;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return b;
	}
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The vector length = " << n << endl;
		cout << "The matrix has " << m << " columns" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return b;
	}
	m = A.size();
	for(int i=0; i<=m-1; i++){
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[i][j]*v[j];
		}
	}
	return b;
}


vector<int> product(vector<int> v, vector<vector<int>> A){
	int n = v.size();
	int m = A.size();
	vector<int> b;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return b;
	}
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The vector length = " << n << endl;
		cout << "The matrix has " << m << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return b;
	}
	m = A[0].size();
	for(int i=0; i<=m-1; i++){
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[j][i]*v[j];
		}
	}
	return b;
}
vector<float> product(vector<float> v, vector<vector<float>> A){
	int n = v.size();
	int m = A.size();
	vector<float> b;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return b;
	}
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The vector length = " << n << endl;
		cout << "The matrix has " << m << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return b;
	}
	m = A[0].size();
	for(int i=0; i<=m-1; i++){
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[j][i]*v[j];
		}
	}
	return b;
}
vector<double> product(vector<double> v, vector<vector<double>> A){
	int n = v.size();
	int m = A.size();
	vector<double> b;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return b;
	}
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The vector length = " << n << endl;
		cout << "The matrix has " << m << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return b;
	}
	m = A[0].size();
	for(int i=0; i<=m-1; i++){
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[j][i]*v[j];
		}
	}
	return b;
}


vector<vector<int>> product(vector<vector<int>> A, vector<vector<int>> B){
	int a1 = A.size();
	int a2 = A[0].size();
	int b1 = B.size();
	vector<vector<int>> C;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return C;
	}
	if(isRectangular(B) == 1){
		cout << endl << endl << endl << endl << endl << "The second inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return C;
	}
	if (a2 != b1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The 1st matrix has " << a2 << " columns" << endl;
		cout << "The 2nd matrix has " << b1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return C;
	}
	for(int i=0; i<=a1-1; i++){
		C.push_back(product(A[i], B));
	}
}
vector<vector<float>> product(vector<vector<float>> A, vector<vector<float>> B){
	int a1 = A.size();
	int a2 = A[0].size();
	int b1 = B.size();
	vector<vector<float>> C;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return C;
	}
	if(isRectangular(B) == 1){
		cout << endl << endl << endl << endl << endl << "The second inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return C;
	}
	if (a2 != b1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The 1st matrix has " << a2 << " columns" << endl;
		cout << "The 2nd matrix has " << b1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return C;
	}
	for(int i=0; i<=a1-1; i++){
		C.push_back(product(A[i], B));
	}
}
vector<vector<double>> product(vector<vector<double>> A, vector<vector<double>> B){
	int a1 = A.size();
	int a2 = A[0].size();
	int b1 = B.size();
	vector<vector<double>> C;
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return C;
	}
	if(isRectangular(B) == 1){
		cout << endl << endl << endl << endl << endl << "The second inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return C;
	}
	if (a2 != b1){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "The dimensions do not line up" << endl;
		cout << "The 1st matrix has " << a2 << " columns" << endl;
		cout << "The 2nd matrix has " << b1 << " rows" << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return C;
	}
	for(int i=0; i<=a1-1; i++){
		C.push_back(product(A[i], B));
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



vector<vector<int>> outerProduct(vector<int> x, vector<int> y){
	int n = x.size();
	int m = y.size();
	vector<vector<int>> A;
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return A;
	}
	for(int i=0; i<=n-1; i++){
		A.push_back({});
		for(int j=0; j<=n-1; j++){
			A[i].push_back(x[i]*y[j]);
		}
	}
	return A;
}
vector<vector<float>> outerProduct(vector<float> x, vector<float> y){
	int n = x.size();
	int m = y.size();
	vector<vector<float>> A;
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return A;
	}
	for(int i=0; i<=n-1; i++){
		A.push_back({});
		for(int j=0; j<=n-1; j++){
			A[i].push_back(x[i]*y[j]);
		}
	}
	return A;
}
vector<vector<double>> outerProduct(vector<double> x, vector<double> y){
	int n = x.size();
	int m = y.size();
	vector<vector<double>> A;
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return A;
	}
	for(int i=0; i<=n-1; i++){
		A.push_back({});
		for(int j=0; j<=n-1; j++){
			A[i].push_back(x[i]*y[j]);
		}
	}
	return A;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




// Gives the P norm of a vector
float vectorPNorm(float p, vector<int> x){
	int n = x.size();
	x[0] = pow(fabs(x[0]), p);
	for(int i=1; i<=n-1; i++){
		x[0] = x[0] + pow(fabs(x[i]), p);
	}
	x[0] = pow(fabs(x[0]), 1.0/p);
	return x[0];
}
float vectorPNorm(float p, vector<float> x){
	int n = x.size();
	x[0] = pow(fabs(x[0]), p);
	for(int i=1; i<=n-1; i++){
		x[0] = x[0] + pow(fabs(x[i]), p);
	}
	x[0] = pow(fabs(x[0]), 1.0/p);
	return x[0];
}
double vectorPNorm(double p, vector<double> x){
	int n = x.size();
	x[0] = pow(fabs(x[0]), p);
	for(int i=1; i<=n-1; i++){
		x[0] = x[0] + pow(fabs(x[i]), p);
	}
	x[0] = pow(fabs(x[0]), 1.0/p);
	return x[0];
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Infinity-Norm of vector x
float vectorInfNorm(vector<int> x){
	int n = x.size();
	x[0] = fabs(x[0]);
	for(int i=1; i<=n-1; i++){
		if(fabs(x[i]) > x[0]){
			x[0] = fabs(x[i]);
		}
	}
	return x[0];
}
float vectorInfNorm(vector<float> x){
	int n = x.size();
	x[0] = fabs(x[0]);
	for(int i=1; i<=n-1; i++){
		if(fabs(x[i]) > x[0]){
			x[0] = fabs(x[i]);
		}
	}
	return x[0];
}
double vectorInfNorm(vector<double> x){
	int n = x.size();
	x[0] = fabs(x[0]);
	for(int i=1; i<=n-1; i++){
		if(fabs(x[i]) > x[0]){
			x[0] = fabs(x[i]);
		}
	}
	return x[0];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// This sees vector 1 norm of the columns of A
float matrix1Norm(vector<vector<int>> A){
	print(A);
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	int n = A[0].size();
	int max = 0;
	int temp;
	for(int j=0; j<=n-1; j++){
		temp = 0;
		for(int i=0; i<=m-1; i++){
			temp = abs(A[i][j]) + temp;
		}
		if(temp > max){
			max = temp;
		}
	}
	return max;
}
float matrix1Norm(vector<vector<float>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	int n = A[0].size();
	float max = 0;
	float temp;
	for(int j=0; j<=n-1; j++){
		temp = 0;
		for(int i=0; i<=m-1; i++){
			temp = fabs(A[i][j]) + temp;
		}
		if(temp > max){
			max = temp;
		}
	}
	return max;
}
double matrix1Norm(vector<vector<double>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	int n = A[0].size();
	double max = 0;
	double temp;
	for(int j=0; j<=n-1; j++){
		temp = 0;
		for(int i=0; i<=m-1; i++){
			temp = fabs(A[i][j]) + temp;
		}
		if(temp > max){
			max = temp;
		}
	}
	return max;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// This sees vector 1 norm of the rows of A
float matrixInfNorm(vector<vector<int>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	A[0][0] = vectorPNorm(1, A[0]);
	for(int i=1; i<=m-1; i++){
		float max = vectorPNorm(1, A[i]);
		if(A[0][0] < max){
			A[0][0] = max;
		}
	}
	return A[0][0];
}
float matrixInfNorm(vector<vector<float>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	A[0][0] = vectorPNorm(1, A[0]);
	for(int i=1; i<=m-1; i++){
		float max = vectorPNorm(1, A[i]);
		if(A[0][0] < max){
			A[0][0] = max;
		}
	}
	return A[0][0];
}
double matrixInfNorm(vector<vector<double>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	A[0][0] = vectorPNorm(1, A[0]);
	for(int i=1; i<=m-1; i++){
		double max = vectorPNorm(1, A[i]);
		if(A[0][0] < max){
			A[0][0] = max;
		}
	}
	return A[0][0];
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// Matrix Frobenius Norm
float matrixFNorm(vector<vector<int>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	int n = A[0].size();
	float norm = 0;
	for(int i=0; i<=m-1; i++){
		for(int j=0; j<=n-1; j++){
			norm = A[i][j]*A[i][j] + norm;
		}
	}
	norm = pow(norm, 0.5);
	return norm;
}
float matrixFNorm(vector<vector<float>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	int n = A[0].size();
	float norm = 0;
	for(int i=0; i<=m-1; i++){
		for(int j=0; j<=n-1; j++){
			norm = A[i][j]*A[i][j] + norm;
		}
	}
	norm = pow(norm, 0.5);
	return norm;
}
double matrixFNorm(vector<vector<double>> A){
	if(isRectangular(A) == 1){
		cout << endl << endl << endl << endl << endl << "The first inputted Matrix is not rectangular" << endl << endl << endl << endl << endl ;
		return 0.0;
	}
	int m = A.size();
	int n = A[0].size();
	double norm = 0;
	for(int i=0; i<=m-1; i++){
		for(int j=0; j<=n-1; j++){
			norm = A[i][j]*A[i][j] + norm;
		}
	}
	norm = pow(norm, 0.5);
	return norm;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


vector<float> vectorGenerator(int maxInt, int n, float decimal){ 
	srand(time(NULL));
	float random;
	vector<float> b;
	for(int j=0; j<=n-1; j++){
		random = rand() % maxInt * pow(-1.0,(float) (rand() % maxInt));
		// random = random/decimal;
		b.push_back(random);
	}
	return b;
}
vector<double> vectorGenerator(int maxInt, int n, double decimal){ 
	srand(time(NULL));
	double random;
	vector<double> b;
	for(int j=0; j<=n-1; j++){
		random = rand() % maxInt * pow(-1.0,(double) (rand() % maxInt));
		// random = random/decimal;
		b.push_back(random);
	}
	return b;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


vector<vector<float>> matrixGenerator(int maxInt, int n, int k, float decimal){
	vector<vector<float>> M;
	for(int i=0; i<=n-1; i++){
		M.push_back(vector<float>());
		float random;
		for(int j=0; j<=k-1; j++){
			random = rand() % maxInt * pow(-1.0,(float) (rand() % maxInt));
			random = random/decimal;
			M[i].push_back(random);
		}
		// if(a == 1 && M[i][i] == 0){
		// 	random = rand() % maxInt * pow(-1.0,(float) (rand() % maxInt));
		// 	random = random/decimal;
		// 	M[i][i] = random + 1;
		// }
		// if(fabs(M[i][i]) < vectorInfNorm(M[i])){
		// 	M[i][i] = vectorInfNorm(M[i]);
		// }
	}
	return M;
}
vector<vector<double>> matrixGenerator(int maxInt, int n, int k, double decimal){

	vector<vector<double>> M;
	for(int i=0; i<=n-1; i++){
		M.push_back(vector<double>());
		double random;
		for(int j=0; j<=k-1; j++){
			random = rand() % maxInt * pow(-1.0,(double) (rand() % maxInt));
			random = random/decimal;
			M[i].push_back(random);
		}
		// if(a == 1 && M[i][i] == 0){
		// 	random = rand() % maxInt * pow(-1.0,(double) (rand() % maxInt));
		// 	random = random/decimal;
		// 	M[i][i] = random + 1;
		// }
		// if(fabs(M[i][i]) < vectorInfNorm(M[i])){
		// 	M[i][i] = vectorInfNorm(M[i]);
		// }
	}
	return M;
}

