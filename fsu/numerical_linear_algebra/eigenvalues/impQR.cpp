// For precision precision type in "g++ -Dprecision=1 title.cpp" into the terminal
// To always do -std=c++11 do "alias g++="g++ -std=c++11" " at the begining of terminal
#ifdef precision
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
			cout << A[i][j] << ", ";
		}
		cout << endl;
	}
	cout << endl;
}
vector<precision> subtract(vector<precision> x, vector<precision> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return vector<precision>();
	}
	for(int i=0; i<=n-1; i++){
		x[i] = x[i] - y[i];
	}
	return x;
}
precision innerProduct(vector<precision> x, vector<precision> y){
	int n = x.size();
	int m = y.size();
	if(n != m){
		cout << endl << endl << endl << endl << endl << endl << endl << endl << "These two vectors are not the same length" << endl;
		cout << "First vector length = " << n << endl;
		cout << "Second vector length = " << m << endl << endl << endl << endl << endl << endl << endl << endl << endl;
		return 0;
	}
	precision z = 0;
	for(int i=0; i<=n-1; i++){
		z = z + x[i]*y[i];
	}
	return z;
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
vector<precision> vectorGenerator(int maxInt, int n, precision decimal){ 
	precision random;
	vector<precision> b;
	for(int j=0; j<=n-1; j++){
		random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt)) + 1;
		random = random/decimal;
		b.push_back(random);
	}
	return b;
}
vector<vector<precision>> triSymToepGenerator(int maxInt, int n, precision decimal){
	precision alpha = ( rand() % maxInt + 1) / decimal;
	precision beta = ( rand() % maxInt + 1) / decimal;
	vector<vector<precision>> b;
	b.push_back({});
	b.push_back({});
	b[0].push_back(alpha);
	for(int j=0; j<=n-2; j++){
		b[0].push_back(alpha);
		b[1].push_back(beta);
	}
	return b;
}
int triSymToepEValCheck(precision alpha, precision beta, vector<precision> eigenValues){
	int n = eigenValues.size();
	int count = 0;
	for (int i=1; i<=n; i++){
		precision eVal = alpha + 2*beta*cos(i*M_PI/(n+1));
		// cout << eVal << ", ";
		for(int j=0; j<n; j++){
			if(fabs(eVal - eigenValues[j]) < 0.0001){
				count++;
				j=n;
			}
		}
	}
	// cout << endl;
	return (n-count);
}
vector<vector<precision>> matrixGenerator(int maxInt, int n, int k, precision decimal){
	vector<vector<precision>> M;
	for(int i=0; i<=n-1; i++){
		M.push_back(vector<precision>());
		precision random;
		for(int j=0; j<=k-1; j++){
			random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
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
vector<precision> projection(vector<precision> v, vector<precision> u){
	int n = u.size();
	precision c = innerProduct(u, v)/innerProduct(u, u);
	for(int i=0; i<n; i++){
		u[i] = u[i]*c;
	}
	return u;
}
vector<vector<precision>> gramSchmidt(int maxInt, int n, precision decimal){
	vector<vector<precision>> A;
	for(int i=0; i<n; i++){ A.push_back({}); }
	for(int i=0; i<n; i++){
		A[i] = vectorGenerator(maxInt, n, decimal);

		// This subtracts the projections of A[i] onto the A[j] where j<i from A[i]
		vector<precision> temp = A[i];
		for(int j=0; j<i; j++){
			A[i] = subtract(A[i], projection(temp, A[j]));
		}
		
		// This brings norm of A[i] down to 1
		precision norm = sqrt( innerProduct(A[i],A[i]) );
		for(int j=0; j<n; j++){
			A[i][j] = A[i][j]/norm;
		}

		// This checks to see if any vectors zeroed out, if it is then we start this iteration over again
		int count = 0;
		for(int j=0; j<n; j++){
			if(fabs(A[i][j]) == 0){
				count++;
			}
		}
		if(count == n){ i--; }
	}
	return A;
}
vector<vector<precision>> symMatGenerate(vector<vector<precision>> Q, vector<precision> eVals){
	vector<vector<precision>> A = Q;
	int n = eVals.size();
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			A[i][j] = A[i][j] * eVals[j];
		}
	}
	Q = transpose(Q);
	A = prodRegular(A,Q);
	vector<vector<precision>> B;
	for(int i=0; i<n; i++){
		B.push_back({});
		for(int j=0; j<=i; j++){
			B[i].push_back(A[i][j]);

		}	
	}
	return B;
}


vector<precision> impQRAlg(vector<vector<precision>> tri);

vector<vector<precision>> symToTri(vector<vector<precision>> A);
vector<precision> symVecProd(vector<vector<precision>> A, vector<precision> v);

vector<precision> eigenVals(vector<vector<precision>> A);




int main(){
	srand (time(NULL));
	setprecision(7);

	vector<vector<precision>> A{{1}, {2,3}, {4,5,6}, {7,8,9,10}, {11,12,13,14,15}};
	vector<precision> eigenValues;
	// print(A);
	// A = symToTri(A);
	// print(A);

	vector<vector<precision>> B{{4}, {2, -3}, {2,1,3}, {1,1,1,2}};
	print(B);
	B = symToTri(B);
	print(B);
	eigenValues = impQRAlg(B);
	print(eigenValues);

	vector<vector<precision>> C{{5}, {1,1}, {2,2,0}, {2, 1, 2, 1}, {4, 0, 1, 2, 4}};
	print(C);
	C = symToTri(C);
	print(C);
	eigenValues = impQRAlg(C);
	print(eigenValues);

	vector<vector<precision>> D{{4}, {1,2}, {2,0,3}, {-5, 4, -1, 1}, {1, 5, 2, 5, -2}, {4, 3, 1, 2, 4, 1}};
	print(D);
	D = symToTri(D);
	print(D);
	eigenValues = impQRAlg(D);
	print(eigenValues);

	// vector<vector<precision>> E{{4}, {2, -3}, {2,1,3}, {1,1,1,2}};
	// eigenValues = eigenVals(E);
	// print(eigenValues);

	int n = 6;

	vector<vector<precision>>  F;
	F = triSymToepGenerator(n+1, n, 1);
	print(F);
	eigenValues = impQRAlg(F);
	print(eigenValues);
	cout << "Number of incorrect EVals = " << (triSymToepEValCheck(F[0][0], F[1][0], eigenValues)) << endl << endl;



	vector<vector<precision>> Q = gramSchmidt(n+1,n,1);
	print(Q);
	vector<precision> eVals = vectorGenerator(n+1,n,1);
	print(eVals);
	A = symMatGenerate(Q, eVals);
	print(A);
	eigenValues = eigenVals(A);
	print(eigenValues);

	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			cout << innerProduct(Q[i], Q[j]) << ", ";
		}
		cout << endl;
	}

	return 0;
}


// Tri holds two vectors, the diagonal of length n, the sub/sup diagonal of length n-1.
// This returns a vector of approximated eigenValues.
// Comments are for going down the stair case created by diagonal and subdiagonal of a 4 by 4 matrix,
// Then finding general equations of how givens rotations effect each element and exploiting them.
vector<precision> impQRAlg(vector<vector<precision>> tri){

	int n = tri[0].size();

	// This first for loop is for iterating for each eigenValue
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
				tri[0][i] =   ( tri[1][i-1]*tri[1][i-1]*temp1 + 2*tri[1][i-1]*temp2*bulge + tri[0][i+1]*bulge*bulge )/norm2; 			//x3
				tri[1][i] =   ( tri[1][i-1]*tri[1][i-1]*temp2 + (tri[0][i+1] - temp1)*tri[1][i-1]*bulge - temp2*bulge*bulge )/norm2;	//x4
				tri[0][i+1] = ( tri[1][i-1]*tri[1][i-1]*tri[0][i+1] - 2*tri[1][i-1]*temp2*bulge + temp1*bulge*bulge )/norm2;			//x5

				// These change, first bulge, then x6, then x2 specifically in that order as bulge depends on x6 and x6 depends on x2
				if(i < n-2-k){		// This if is for the last iteration which gets rid of the bulge
					bulge = tri[1][i+1]*bulge/norm;					//bulge
					tri[1][i+1] = tri[1][i-1]*tri[1][i+1]/norm;		//x6
				}
				tri[1][i-1] = norm;								//x2
			}

			// print(tri);
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


// This returns a vector of eigenValues
vector<precision> eigenVals(vector<vector<precision>> A){
	vector<precision> eigenValues;
	eigenValues = impQRAlg(symToTri(A));
	return eigenValues;
}

