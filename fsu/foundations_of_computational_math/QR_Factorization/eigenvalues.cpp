// For double precision type in "g++ -DDOUBLE=1 title.cpp" into the terminal
// To always do -std=c++11 do "alias g++="g++ -std=c++11" " at the begining of terminal
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

void printVec(vector<precision> v){
	int n = v.size();
	for(int i=0; i<=n-1; i++){
		cout << v[i] << " \\\\" << endl;
	}
	cout << endl;
}
void print(vector<precision> v){
	int n = v.size();
	for(int i=0; i<=n-1; i++){
		cout << v[i] << "," ;
	}
	cout << endl;
	cout << endl;
}
void print(vector<int> v){
	int n = v.size();
	for(int i=0; i<=n-1; i++){
		cout << v[i] << "," ;
	}
	cout << endl;
	cout << endl;
}
void print(vector<vector<precision>> A){
	int n = A.size();
	
	for(int i=0; i<n; i++){
		int m = A[i].size();
		for(int j=0; j<m; j++){
			cout << A[i][j] << " & ";
		}
		cout << endl;
	}
	cout << endl;
}



vector<precision> impQRAlg(vector<vector<precision>> tri);

vector<vector<precision>> symToTri(vector<vector<precision>> A);
vector<precision> symVecProd(vector<vector<precision>> A, vector<precision> v);

vector<precision> eigenVals(vector<vector<precision>> A);




int main(){

	vector<vector<precision>> A{{1}, {2,3}, {4,5,6}, {7,8,9,10}, {11,12,13,14,15}};
	vector<precision> eigenvalues;
	// print(A);
	// A = symToTri(A);
	// print(A);

	vector<vector<precision>> B{{4}, {2, -3}, {2,1,3}, {1,1,1,2}};
	print(B);
	B = symToTri(B);
	print(B);
	eigenvalues = impQRAlg(B);
	print(eigenvalues);

	vector<vector<precision>> C{{5}, {1,1}, {2,2,0}, {2, 1, 2, 1}, {4, 0, 1, 2, 4}};
	print(C);
	C = symToTri(C);
	print(C);
	eigenvalues = impQRAlg(C);
	print(eigenvalues);

	vector<vector<precision>> D{{4}, {1,2}, {2,0,3}, {-5, 4, -1, 1}, {1, 5, 2, 5, -2}, {4, 3, 1, 2, 4, 1}};
	print(D);
	D = symToTri(D);
	print(D);
	eigenvalues = impQRAlg(D);
	print(eigenvalues);

	// vector<vector<precision>> F{{4}, {2, -3}, {2,1,3}, {1,1,1,2}};
	// eigenvalues = eigenVals(F);
	// print(eigenvalues);

}


// Tri holds two vectors, the diagonal of length n, the sub/sup diagonal of length n-1.
// This returns a vector of approximated eigenvalues.
// Comments are for going down the stair case created by diagonal and subdiagonal of a 4 by 4 matrix,
// Then finding general equations of how givens rotations effect each element and exploiting them.
vector<precision> impQRAlg(vector<vector<precision>> tri){

	int n = tri[0].size();

	// This first for loop is for iterating for each eigenvalue
	for(int k=0; k<=n-1; k++){
		// This while loop checks the bottom right sub-diagonal element of the top-right (n-1-k) square matrix
		// for(int j=0; j<=10; j++){
		while(fabs(tri[1][n-2-k]) >= 0.000001){
			// This bulk of code creates the bulge, aka the first givens.
			// This is the norm and norm squared = norm2 of the our vector v.
			precision norm2 = tri[0][0]*tri[0][0] + tri[1][0]*tri[1][0];
			precision norm = pow(norm2, 0.5);

			// This sets two temporary variables for x1 and x2
			precision temp1 = tri[0][0];    //x1
			precision temp2 = tri[1][0];	//x2

			// This update the elements x1, x2, x3, x4 with !!!!! x3 coming after x1 and x2 !!!!!!.
			precision bulge = tri[1][0]*tri[1][1]/norm;
			tri[0][0] = temp1 + temp2*temp2*(temp1 + tri[0][1])/norm2;     //x1
			tri[1][0] = -1*temp2 + temp1*temp2*(temp1 + tri[0][1])/norm2;  //x2
			tri[0][1] = temp1*(temp1*tri[0][1] - temp2*temp2)/norm2;       //x3
			tri[1][1] = temp1*tri[1][1]/norm;  					           //x4

			// This is for the bulge as we go n-3-k times not including initiating the bulge 
			for(int i=1; i<=n-2-k; i++){
				// This is the norm and the norm squared, = norm2, of the our vector v.
				norm2 = tri[1][i-1]*tri[1][i-1] + bulge*bulge;
				norm = pow(norm2, 0.5);

				// These set two temporary variables for x3 and x4
				temp1 = tri[0][i]; //x3
				temp2 = tri[1][i]; //x4	

				// These update x3, x4, and last x5 because it does not have a temp variable
				// These need to come first as they depend on the bulge and x2.
				tri[0][i] =   ( tri[1][i-1]*tri[1][i-1]*temp1 + 2*tri[1][i-1]*temp2*bulge + tri[0][i+1]*bulge*bulge )/norm2; 				//x3
				tri[1][i] =   ( tri[1][i-1]*tri[1][i-1]*temp2 + (tri[0][i+1] - temp1)*tri[1][i-1]*bulge - temp2*bulge*bulge )/norm2;	//x4
				tri[0][i+1] = ( tri[1][i-1]*tri[1][i-1]*tri[0][i+1] - 2*tri[1][i-1]*temp2*bulge + temp1*bulge*bulge )/norm2;			//x5

				// These change, first bulge, then x6, then x2 specifically in that order as bulge depends on x6 and x6 depends on x2
				if(i < n-2-k){		// This if is for the last iteration which gets rid of the bulge
					bulge = tri[1][i+1]*bulge/norm;					//bulge
					tri[1][i+1] = tri[1][i-1]*tri[1][i+1]/norm;		//x6
				}
				tri[1][i-1] = norm;								//x2
			}

			print(tri);
		} 


	}

	return tri[0];

}


// Sym holds n vectors of length 1->n.
// This returns a vector of two vectors, the diagonal of length n, and the sub/sup of length n-1.
vector<vector<precision>> symToTri(vector<vector<precision>> A){
	int n = A.size();

	// We have H*A*H = A + a(x*y^T + z*x^T), where x = v plus/minus ||v||e_1, a = -2/||x||^2, A*x = y, w = x^T*y, and z = y + awx
	for(int j=0; j<=n-3; j++){

		// Declare variables 
		vector<precision> y;
		vector<precision> z;
		precision w = 0;
		precision norm = 0;
		precision xNorm;
		precision x0;

		// Calculate the norm of v, which is vector under the diagonal
		for(int i=j+1; i<=n-1; i++){
			norm = norm + A[i][j]*A[i][j];
		}

		// This code can be used to change if you want the norm to be a positive or negative addition to x-vector
		// if(A[j+1][j] <= 0){
			norm = pow(norm, 0.5);
			x0 = A[j+1][j] + norm;
			xNorm = 2*norm*(norm + A[j+1][j]);
		// } else {
		// 	norm = pow(norm, 0.5);
		// 	x0 = A[j+1][j] - norm;
		// 	xNorm = 2*norm*(norm - A[j+1][j]);
		// 	norm = -1*norm;
		// }

		// First we need to calculate y = A*x, so fill y in with x, v is the vector under the diagonal.
		y.push_back(x0);
		for(int i=j+2; i<=n-1; i++){
			y.push_back(A[i][j]);
		}
		y = symVecProd(A, y);

		// Then calculate the w=x^T*y, remember v is the vector under the diagonal
		w = x0*y[0];
		for(int i=j+2; i<=n-1; i++){
			w = w + A[i][j]*y[i-j-1];
		}

		// This will calculate z = y + awx = y - 2w/||x||^2 * x
		z.push_back(y[0] - 2*w*(x0)/xNorm); //This is for first term of x
		for(int i=j+2; i<=n-1; i++){
			z.push_back(y[i-j-1] - 2*w*A[i][j]/xNorm);
		}

		// Next we will calculate the lower triangle elements of A + a(x*y^T + z*x^T).
		// Thus we only need to do when i >= k
		A[j+1][j+1] = A[j+1][j+1] - 2*(x0*y[0] + z[0]*x0)/xNorm; // This is for first diag
		for(int i=j+2; i<=n-1; i++){
			A[i][j+1] = A[i][j+1] - 2*(A[i][j]*y[0] + z[i-j-1]*x0)/xNorm;  // This is for first col of sub-matrix
			for(int k=j+2; k<=i; k++){
				A[i][k] = A[i][k] -2*(A[i][j]*y[k-j-1] + z[i-j-1]*A[k][j])/xNorm;
			}
		}

		// This puts the sub as the norm
		A[j+1][j] = -1*norm;

	}

	vector<vector<precision>> tri(2);
	for(int i=0; i<=1; i++){
		for(int j=0; j<=n-1-i; j++){
			tri[i].push_back(A[j+i][j]);
		}
	}

	return tri;

}

// This does a matrix-vector product for a symmetric matrix A.
// If v is smaller in dimension than it uses the bottomright square matrix of A that is of the same dimensions as v
vector<precision> symVecProd(vector<vector<precision>> A, vector<precision> v){
	int n = A.size();
	int m = v.size();
	int p = n-m;

	// This loop is for rows of A
	for(int i=p; i<=n-1; i++){
		precision sum = 0;

		// We go through A regularly until the diagonal
		for(int k=p; k<=i; k++){
			sum = sum + A[i][k]*v[k-p]; 
		}

		// As A is symmetric we start going down column i after we reach the diagonal
		for(int k=i+1; k<=n-1; k++){
			sum = sum + A[k][i]*v[k-p];
		}
		A[i][0] = sum;
	}

	// As we stick the sums in the 1st column of A we switch those over to v to be returned
	for(int i=p; i<=n-1; i++){
		v[i-p] = A[i][0];
	}

	return v;
}


// This returns a vector of eigenvalues
vector<precision> eigenVals(vector<vector<precision>> A){
	vector<precision> eigenvalues;
	eigenvalues = impQRAlg(symToTri(A));
	return eigenvalues;
}


