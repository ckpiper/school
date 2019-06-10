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
#include <vector>
#include <iomanip>  // This is to set precision of displayed long floats
#include "../../../vectorFuncs.h" // This is my own library of functions for vectors

vector<vector<precision>> prodRegular(vector<vector<precision>> A, vector<vector<precision>> B);
vector<vector<precision>> matrixGenerate(int maxInt, int n, int m, precision decimal);
vector<precision> vectorGenerate(int maxInt, int n, precision decimal);
vector<vector<precision>> prodRegular(vector<vector<precision>> A, vector<vector<precision>> B);
precision equalityCheck(vector<vector<precision>> A, vector<vector<precision>> B);
vector<vector<precision>> transpose(vector<vector<precision>> A);
vector<vector<precision>> cholesky(vector<vector<precision>> A);
vector<vector<precision>> schur(vector<vector<precision>> A);






int main(){
	srand (time(NULL));
	setprecision(7);

	int maxInt = 5;
	int n1 = 4;
	precision decimal = 1; // This divides the rand()%maxInt number to get decimals

	vector<vector<precision>> A;
	vector<vector<precision>> B;
	A = matrixGenerator(maxInt, n1, n1, decimal);
	cout << "Print A " ;
	B = transpose(A);
	A = prodRegular(A,B);
	print(A);
	A = cholesky(A);
	cout << "Print Cholesky Factor of A " ;
	print(A);
	B = transpose(A);
	A = prodRegular(A,B);
	cout << "Print A back out again " ;
	print(A);



	vector<precision> v;
	v = vectorGenerate(maxInt, n1, decimal);
	cout << "Random v " << endl;
	print(v);
	v[0] = v[0]*v[0];
	for(int i=1; i<n1; i++){
		v[0] = v[0] + v[i]*v[i];
	}
	cout << "Definite v" << endl;
	print(v);
	vector<vector<precision>> C;
	for(int i=0; i<n1; i++){
		C.push_back({});
		for(int j=i; j>=0; j--){
			C[i].push_back(v[j]);
		}
	}
	cout << "Print C (v toeplitz) ";
	print(C);
	cout << "Cholesky Factor" << endl;
	print(cholesky(C));
	cout <<	"SchurAlgorithm" << endl;
	print(schur(C));


}


// This returns the Lower triangular of the cholesky factorization
vector<vector<precision>> cholesky(vector<vector<precision>> A){
	int n = A.size();
	int m = A[0].size();

	// This will solve it by first changing columns into L and computing submatrix each change of column
	for(int i=0; i<n; i++){
		for(int j=0; j<=i; j++){
			if(i == j){
				precision temp = 0;
				for(int k=0; k<j; k++){
					temp = temp + A[i][k]*A[i][k];
				}
				A[i][j] = sqrt(A[i][j] - temp);
			} else {
				precision temp = 0;
				for(int k=0; k<j; k++){
					temp = temp + A[i][k]*A[j][k];
				}
				A[i][j] = (A[i][j] - temp)/A[j][j];
			}
		}
		// This fills in the zeros if a full matrix is given instead of just the lower part(as it is symmetric)
		if(m == n){
			for(int j=i+1; j<n; j++){
				A[i][j] = 0;
			}
		}
	}

	return A;
}



vector<vector<precision>> schur(vector<vector<precision>> A){
	int n = A.size();
	// First we need to divide first row/column of A by the square root of the top left element
	A[0][0] = sqrt(A[0][0]);
	for(int i=1; i<n; i++){
		A[i][0] = A[i][0]/A[0][0];
	}

	vector<vector<precision>> GT;
	GT.push_back({});
	GT.push_back({});
	// This fills up GT
	for(int i=0; i<n-1; i++){
		GT[0].push_back(A[i][0]);
		GT[1].push_back(A[i+1][0]);
	}
	
	// This is the main for loop that will drive GT to just one non zero using hyperbolic transformations
	for(int i=0; i<n-1; i++){
		// U is meant to drive the first non zero column of GT to have a zero in GT[1]. 
			// U = { {C, -S}, {-S, C} }
			// Let X = g2/g1 and then C = 1/sqrt(1-x^2) and S = x*C
		vector<vector<precision>> U;
		precision x = GT[1][i]/GT[0][i];
		U.push_back({1/sqrt(1-x*x)});
		U[0].push_back(-1*x*U[0][0]);
		U.push_back({U[0][1], U[0][0]});
		// This applies U to GT
		GT = prodRegular(U, GT);

		// Then GT[0] is the next row of the cholesky factorization // The next column of A in our case
		for(int j=i; j<n-1; j++){
			A[j+1][i+1] = GT[0][j];
		}

		// Then we have to shift GT[0] one to the right
		for(int j=n-2; j>i-1; j--){
			GT[0][j] = GT[0][j-1];
		}
		GT[0][i] = 0;
		GT[0][i] = 0;
	}

	return A;
}

vector<vector<precision>> setZeros(int n, int m){
	vector<vector<precision>> A;
	for(int i=0; i<n; i++){
		A.push_back({});
		for(int j=0; j<m; j++){
			A[i].push_back(0);
		}
	}
	return A;
}

vector<vector<precision>> prodRegular(vector<vector<precision>> A, vector<vector<precision>> B){
	int n1 = A.size();
	int n2 = A[0].size();
	int n3 = B[0].size();
	vector<vector<precision>> AB;

	if(n2 != B.size()){
		cout << "Dimensions do not match" << endl;
		cout << "Matrix A dimensions are " << n1 << "x" << n2 << endl;
		cout << "Matrix B dimensions are " << B.size() << "x" << n3 << endl;
		return AB;
	}

	for(int i=0; i<n1; i++){
		AB.push_back({});
		for(int j=0; j<n3; j++){
			AB[i].push_back(0.0);
			for(int k=0; k<n2; k++){
				AB[i][j] = AB[i][j] + A[i][k]*B[k][j];
			}
		}
	}

	return AB;
}	

vector<vector<precision>> matrixGenerate(int maxInt, int n, int m, precision decimal){
	vector<vector<precision>> M;
	for(int i=0; i<n; i++){
		M.push_back(vector<precision>());
		precision random;
		for(int j=0; j<m; j++){
			// The pow part is to put negatives into the matrix 
			random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt)) ;
			// The decimal is to put decimals
			random = random/decimal;
			M[i].push_back(random);
		}
		// if(a == 1 && M[i][i] == 0){
		// 	random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
		// 	random = random/decimal;
		// 	M[i][i] = random + 1;
		// }
		// if(fabs(M[i][i]) < vectorInfNorm(M[i])){
		// 	M[i][i] = vectorInfNorm(M[i]);
		// }
	}
	return M;
}
vector<precision> vectorGenerate(int maxInt, int n, precision decimal){
	vector<precision> v;
	for(int j=0; j<n; j++){
		// The pow part is to put negatives into the matrix // plus 1 to ensure no zeros
		precision random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
		if(random == 0 || random == -0){
			random++;
		}
		// The decimal is to put decimals
		random = random/decimal;
		v.push_back(random);
	}
	// if(a == 1 && M[i][i] == 0){
	// 	random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
	// 	random = random/decimal;
	// 	M[i][i] = random + 1;
	// }
	// if(fabs(M[i][i]) < vectorInfNorm(M[i])){
	// 	M[i][i] = vectorInfNorm(M[i]);
	// }
	return v;
}


precision equalityCheck(vector<vector<precision>> A, vector<vector<precision>> B){
	precision error = 0;

	for(int i=0; i<A.size(); i++){
		for(int j=0; j<A[0].size(); j++){
			error = error + fabs(A[i][j] - B[i][j]);
		}
	}

	return error;
}

vector<vector<precision>> transpose(vector<vector<precision>> A){
	vector<vector<precision>> B;
	int n = A.size();
	int m = A[0].size();

	for(int j=0; j<m; j++){
		B.push_back({});
		for(int i=0; i<n; i++){
			B[j].push_back(A[i][j]);
		}
	}

	return B;
}
