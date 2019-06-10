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

void print(vector<vector<precision>> A){
	int n = A[0].size();
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cout << A[i][j] << ",";
		}
		cout << endl;
	}
	cout << endl;
}

void print(vector<precision> v){
	int n = v.size();
	for(int i=0; i<=n-1; i++){
		cout << v[i] << ",";
	}
	cout << endl;
	cout << endl;
}

vector<vector<precision>> LUFactor(int pivot, vector<vector<precision>> A);

vector<precision> systemSolver(int pivot, vector<vector<precision>> LU, vector<precision> b);

vector<vector<precision>> LUFactorCheck(vector<vector<precision>> LU);

vector<vector<precision>> PMatrix(vector<precision> P, vector<vector<precision>> A);
vector<precision> PVector(vector<precision> P, vector<precision> v);
vector<vector<precision>> QMatrix(vector<precision> Q, vector<vector<precision>> A);
vector<precision> QVector(vector<precision> Q, vector<precision> v);

precision vectorPNorm(precision p, vector<precision> x);
precision vectorInfNorm(vector<precision> x);
precision matrix1Norm(vector<vector<precision>> A);
precision matrixInfNorm(vector<vector<precision>> A);
precision matrixFNorm(vector<vector<precision>> A);
vector<precision> vectorDiff(vector<precision> v, vector<precision> w);
vector<vector<precision>> matrixDiff(vector<vector<precision>> A, vector<vector<precision>> B);

// The arguement a is for if we are generating a=0 or LU==1
vector<vector<precision>> LUGenerator(int maxInt, int n, int a, precision decimal){
	
	vector<vector<precision>> M;
	for(int i=0; i<=n-1; i++){
		M.push_back(vector<precision>());
		precision random;
		for(int j=0; j<=n-1; j++){
			random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
			random = random/decimal;
			M[i].push_back(random);
		}
		if(a == 1 && M[i][i] == 0){
			random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
			random = random/decimal;
			M[i][i] = random + 1;
		}
		// if(fabs(M[i][i]) < vectorInfNorm(M[i])){
		// 	M[i][i] = vectorInfNorm(M[i]);
		// }
	}
	return M;
}

vector<precision> vectorGenerator(int maxInt, int n, precision decimal){
	precision random;
	vector<precision> b;
	for(int j=0; j<=n-1; j++){
		random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
		random = random/decimal;
		b.push_back(random);
	}
	return b;
}

vector<precision> matrixVector(vector<vector<precision>> A, vector<precision> v){
	int n = v.size();
	int m = A.size();
	vector<precision> b;
	for(int i=0; i<=m-1; i++){
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[i][j]*v[j];
		}
	}
	return b;
}


int main(){
	srand(time(NULL));
	cout.precision(2);
	// ofstream outLU("../data/CompleteLU.txt");
	// ofstream outSolve("../data/CompleteSolve.txt");
	// ofstream outResidual("../data/CompleteResidual.txt");


	vector<int> n{ 5, 10, 25, 50, 100, 150, 200, 300, 500, 750, 1000} ;
	int pivot = 2;

	// for(int i=0; i<=10; i++){
	// 	vector<vector<precision>> AOrig;
	// 	vector<vector<precision>> A;
	// 	vector<precision> b;
	// 	vector<precision> P;
	// 	vector<precision> Q;
	// 	vector<precision> bOrig;
	// 	vector<precision> xOrig;
	// 	AOrig = LUGenerator(100000, n[i], 1, 1000);
	// 	xOrig = vectorGenerator(100000, n[i], 1000);
	// 	A = AOrig;

	// 	b = matrixVector(A, xOrig); // Turns x -> b
	// 	bOrig = b; // Turns original b

	// 	AOrig = A;

	// 	A = LUFactor(pivot, A); // Turns A -> LU

	// 	P = A[n[i]];
	// 	Q = A[n[i]+1];

	// 	b = systemSolver(pivot, A, b);

	// 	A = LUFactorCheck(A); // Turns LU -> A

	// 	A = PMatrix(P, AOrig);
	// 	// cout << "Hello" << endl;
	// 	A = QMatrix(Q, AOrig);
	// 	A = matrixDiff(A, AOrig);



	// 	precision norm1 = matrix1Norm(A)/matrix1Norm(AOrig);
	// 	// cout << "n = " << n[i] << ", 1-Norm = " << norm1 << endl;
	// 	outLU << "n = " << n[i] << ", 1-Norm = " << norm1 << endl;

	// 	precision normInf = matrixInfNorm(A)/matrixInfNorm(AOrig);
	// 	// cout << "n = " << n[i] << ", Infinity Norm = " << normInf << endl;
	// 	outLU << "n = " << n[i] << ", Infinity Norm = " << normInf << endl;

	// 	precision normF = matrixFNorm(A)/matrixFNorm(AOrig);
	// 	// cout << "n = " << n[i] << ", F-Norm = " << normF << endl;
	// 	outLU << "n = " << n[i] << ", F-Norm = " << normF << endl;
	// 	// cout << endl;

	// 	// b = systemSolver(pivot, B, b);
	// 	b = vectorDiff(b, xOrig);
	// 	precision vNorm1 = vectorPNorm(1, b)/vectorPNorm(1, xOrig);
	// 	precision vNorm2 = vectorPNorm(2, b)/vectorPNorm(2, xOrig);
	// 	precision vNormInf = vectorInfNorm(b)/vectorInfNorm(xOrig);
	// 	// cout << "n = " << n[i] << ", 1-Norm = " << vNorm1 << endl;
	// 	outSolve << "n = " << n[i] << ", 1-Norm = " << vNorm1 << endl;
	// 	// cout << "n = " << n[i] << ", 2-Norm = " << vNorm2 << endl;
	// 	outSolve << "n = " << n[i] << ", 2-Norm = " << vNorm2 << endl;
	// 	// cout << "n = " << n[i] << ", Infinity Norm = " << vNormInf << endl;
	// 	outSolve << "n = " << n[i] << ", Infinity Norm = " << vNormInf << endl;
	// 	// cout << endl;

	// 	b = matrixVector(AOrig, b); // This gets us b-tilda
	// 	precision vbNorm1 = vectorPNorm(1, b)/vectorPNorm(1, bOrig);
	// 	precision vbNorm2 = vectorPNorm(2, b)/vectorPNorm(2, bOrig);
	// 	precision vbNormInf = vectorInfNorm(b)/vectorInfNorm(bOrig);
	// 	// cout << "n = " << n[i] << ", 1-Norm = " << vbNorm1 << endl;
	// 	outResidual << "n = " << n[i] << ", 1-Norm = " << vbNorm1 << endl;
	// 	// cout << "n = " << n[i] << ", 2-Norm = " << vbNorm2 << endl;
	// 	outResidual << "n = " << n[i] << ", 2-Norm = " << vbNorm2 << endl;
	// 	// cout << "n = " << n[i] << ", Infinity Norm = " << vbNormInf << endl;
	// 	outResidual << "n = " << n[i] << ", Infinity Norm = " << vbNormInf << endl;
	// 	// cout << endl;
	// 	cout << n[i] << " & " << norm1 << " & " << normInf << " & " << normF << " & " << vNorm1 << " & " << vNorm2 << " & " << vNormInf << " & " << vbNorm1 << " & " << vbNorm2 << " & " << vbNormInf << " \\\\" << endl;
	// }


	// vector<vector<precision>> C{ {3.0, 4.0, 5.0}, {6.0, 7.0, 8.0}, {9.0, 1.0, 2.0} }; //No pivot
	// vector<vector<precision>> A{ {3.0, 4.0, 5.0, 1.0}, {6.0, 7.0, 8.0, 2.0}, {9.0, 11.0, 12.0, 0.0}, {13.0, 14.0, 15.0, 16.0} }; //No pivot
	// vector<vector<precision>> A{ {3.0, 17.0, 10.0}, {2.0, 4.0, -2.0}, {6.0, 18.0, -12.0} }; //pivot
	// vector<vector<precision>> A{ {5.0, 1.0, 3.0, 1.0}, {10.0, 5.0, 12.0, 3.0}, {5.0, 10.0, 23.0, 5.0}, {15.0, 6.0, 19.0, 7.0} };

	// vector<precision> c{1,2,3};
	// print(C);
	// vector<vector<precision>> COrig;
	// COrig = C;
	// c = matrixVector(C, c);
	// print(c);
	// C = LUFactor(pivot, C);
	// c = systemSolver(pivot, C, c);
	// print(c);
	// c = matrixVector(COrig, c);
	// print(c);


	vector<vector<precision>> A{ {5.0, 1.0, 3.0, 1.0}, {10.0, 5.0, 12.0, 3.0}, {5.0, 10.0, 23.0, 5.0}, {15.0, 6.0, 19.0, 7.0} };
	vector<precision> b{1,2,3,4};

	A = LUFactor(2, A);
	b = systemSolver(2, A, b);
	print(b);




}	



/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////



// pivot = 1 = partial pivot, pivot = 0 = no pivot, pivot = 2 = complete pivot
vector<vector<precision>> LUFactor(int pivot, vector<vector<precision>> A){

	int n = A.size();

	// This adds rows for the row permutations and if needed column permutations
	if(pivot == 1){
		A.push_back(vector<precision>());
	} else if(pivot == 2){
		A.push_back(vector<precision>());
		A.push_back(vector<precision>());
	}

	// This will solve it by first changing columns into L and computing submatrix each change of column
	for(int j=0; j<n-1; j++){

		// This is for either partial=1 or complete=2 pivoting
		if(pivot == 1){			

			// The searches for max magnitude in the jth column under the jth row
			precision max = A[j][j];
			int rowChangeIndex = j;  
			for(int i=j+1; i<=n-1; i++){
				if(fabs(A[i][j]) > max){
					max = A[i][j];
					rowChangeIndex = i;
				}
			}
			A[n].push_back(rowChangeIndex);

			// This switches the two rows
			vector<precision> temp = A[rowChangeIndex];
			A[rowChangeIndex] = A[j];
			A[j] = temp;
		} else if(pivot == 2){

			// This searches for the max magnitude in the sub-matrix
			precision max = A[j][j];
			int rowChangeIndex = j;
			int columnChangeIndex = j;
			for(int i=j+1; i<n; i++){
				for(int k=j+1; k<n; k++){
					if(fabs(A[i][k]) > max){
						max = A[i][k];
						rowChangeIndex = i;
						columnChangeIndex = k;
					}
				}
			}
			A[n].push_back(rowChangeIndex);
			A[n+1].push_back(columnChangeIndex);

			// This switches the two rows
			vector<precision> temp = A[rowChangeIndex];
			A[rowChangeIndex] = A[j];
			A[j] = temp;

			// This switches the two columns
			precision switchVariable;
			for(int i=0; i<n; i++){
				switchVariable = A[i][j];
				A[i][j] = A[i][columnChangeIndex];
				A[i][columnChangeIndex] = switchVariable;
			}
		}

		// This checks if no pivoting fails and returns a Matrix full of zeros if it does
		if(pivot == 0 && fabs(A[j][j]) < 0.000000001){
			for(int i=0; i<=n-1; i++){
				for(int k=0; k<=n-1; k++){
					A[i][k] = 0;
				}
			}
			return A;
		}

		// This loop fills in the column of A that equates to 1st column of L
		for(int i=j+1; i<=n-1; i++){
			A[i][j] = A[i][j]/A[j][j];
		}

		// This loop computes the new sub matrix for A, k=columns of sub matrix
		for(int k=j+1; k<=n-1; k++){
			// This then computes the columns of the submatrix
			for(int i=j+1; i<=n-1; i++){
				//A[i][k] is submatrix, A[i][j] = l[i], A[j][k] is element on top of submatrix column, 
				// j we conseptualize as the columns, but it is also the row we are on as well
				A[i][k] = A[i][k] - A[i][j]*A[j][k];
			}
		}
	}

	return A;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////



// This solves the system Ax=b by P * A * Q * Q^{-1} x = P * b where LU = PAQ
vector<precision> systemSolver(int pivot, vector<vector<precision>> LU, vector<precision> b){

	// This gets size and changes corrects it for if pivot rows were added
	int n = b.size();

	// This solves for Pb or b-tilda
	if(pivot){
		precision rowChangeTemp;
		for(int i=0; i<=n-2; i++){
			rowChangeTemp = b[i];
			b[i] = b[LU[n][i]];
			b[LU[n][i]] = rowChangeTemp;
		}
	}

	// This solves the system Ly = b-tilda by row oriented, but going from top->bottom because L=Lower
	for(int i=1; i<n; i++){
		// Each row we need to update ith minus one constants
		for(int j=0; j<=i-1; j++){
			b[i] = b[i] - LU[i][j]*b[j];
		}
	}

	// This solves the system Ux = y by row oriented, but going from bottom->top because U=Upper
	// This solves for x-tilda in complete pivoting		
	for(int i=n-1; i>=0; i--){
		// Each row we need to update ith minus one constants
		for(int j=n-1; j>i; j--){
			b[i] = b[i] - LU[i][j]*b[j];
		}
		b[i] = b[i]/LU[i][i];
	}

	// This solves for Q * x-tilda to get x, also becuase x = Qx-tilda we must go backwards in Q
	if(pivot == 2){
		precision rowChangeTemp;
		for(int j=n-2; j>=0; j--){
			rowChangeTemp = b[j];
			b[j] = b[LU[n+1][j]];
			b[LU[n+1][j]] = rowChangeTemp;
		}
	}

	return b;

}



/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////



vector<vector<precision>> LUFactorCheck(vector<vector<precision>> LU){

	int n = LU.size();
	vector<vector<precision>> M;
	M.push_back(vector<precision>());

	// This fills in the 1st row of M which is equal to the 1st row of U
	for(int i=0; i<=n-1; i++){
		M[0].push_back(LU[0][i]);
	}

	// This computes the ith row of M
	for(int i=1; i<=n-1; i++){
		M.push_back(vector<precision>());


		// This computes jth column for ith row of M
		for(int j=0; j<=n-1; j++){
			M[i].push_back(0);

			// This only goes to the i-1 or j (whichever is smaller) as different cases for when k= i or k=j
			for(int k=0; k<=i-1 && k<=j; k++){
				M[i][j] = M[i][j] + LU[i][k]*LU[k][j];
			}

			// This adds the 1 in Lower Diag * U[i][i] in Upper diag since its last one
			if(i == j || i < j){
				M[i][j] = M[i][j] + LU[i][j];
			} 
		}
	}

	return M;

}

vector<vector<precision>> PMatrix(vector<precision> P, vector<vector<precision>> A){

	int p = P.size();
	int n = A.size();	

	vector<precision> rowChangeTemp;
	for(int i=0; i<=p-1; i++){
		rowChangeTemp = A[i];
		A[i] = A[P[i]];
		A[P[i]] = rowChangeTemp;
	}

	return A;

}

vector<precision> PVector(vector<precision> P, vector<precision> v){

	int p = P.size()-1;
	int n = v.size();

	precision rowChangeTemp;
	for(int i=0; i<=p-1; i++){
		rowChangeTemp = v[i];
		v[i] = v[P[i]];
		v[P[i]] = rowChangeTemp;
	}

	return v;

}

vector<vector<precision>> QMatrix(vector<precision> Q, vector<vector<precision>> A){

	int p = Q.size()-1;
	int n = A.size();

	// This iterates through Q Forward as when we use Q it hits A in correct order
	for(int j=0; j<=p-1; j++){

		precision rowChangeTemp;
		for(int i=0; i<=n-1; i++){
			rowChangeTemp = A[i][j];
			A[i][j] = A[i][Q[j]];
			A[i][Q[j]] = rowChangeTemp;
		}

	}

	return A;

}

vector<precision> QVector(vector<precision> Q, vector<precision> v){

	int p = Q.size();
	int n = v.size();

	// This iterates through Q backwards as that what we do when doing x = Q x
	precision rowChangeTemp;
	for(int j=n-2; j>=0; j--){
		rowChangeTemp = v[j];
		v[j] = v[Q[j]];
		v[Q[j]] = rowChangeTemp;
	}

	return v;

}


/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////


// P-Norm of the vector
precision vectorPNorm(precision p, vector<precision> x){
	int n = x.size();
	x[0] = pow(fabs(x[0]), p);
	for(int i=1; i<=n-1; i++){
		x[0] = x[0] + pow(fabs(x[i]), p);
	}
	x[0] = pow(fabs(x[0]), 1.0/p);
	return x[0];
}

// Infinity-Norm of vector x
precision vectorInfNorm(vector<precision> x){
	int n = x.size();
	x[0] = fabs(x[0]);
	for(int i=1; i<=n-1; i++){
		if(fabs(x[i]) > x[0]){
			x[0] = fabs(x[i]);
		}
	}
	return x[0];
}

// This sees vector 1 norm of the columns of A
precision matrix1Norm(vector<vector<precision>> A){
	int m = A.size();
	int n = A[0].size();
	precision max = 0;
	precision temp;
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

// This sees vector 1 norm of the rows of A
precision matrixInfNorm(vector<vector<precision>> A){
	int m = A.size();
	A[0][0] = vectorPNorm(1, A[0]);
	precision max;
	for(int i=1; i<=m-1; i++){
		max = vectorPNorm(1, A[i]);
		if(A[0][0] < max){
			A[0][0] = max;
		}
	}
	return max;
}

precision matrixFNorm(vector<vector<precision>> A){
	int m = A.size();
	int n = A[0].size();
	precision norm = 0;
	for(int i=0; i<=m-1; i++){
		for(int j=0; j<=n-1; j++){
			norm = A[i][j]*A[i][j] + norm;
		}
	}
	norm = pow(norm, 0.5);
	return norm;
}

// Finds the difference between the vectors
vector<precision> vectorDiff(vector<precision> v, vector<precision> w){
	int n = v.size();
	for(int i=0; i<=n-1; i++){
		v[i] = v[i]-w[i];
	}
	return v;
}

// Finds the difference of each element between two matrices
vector<vector<precision>> matrixDiff(vector<vector<precision>> A, vector<vector<precision>> B){
	int n = B[0].size(); 
	for(int i=0; i<=n-1;i++){
		A[i] = vectorDiff(A[i],B[i]);
	}
	return A;
}





