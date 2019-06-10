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
	int m = A[0].size();

	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cout << A[i][j] << " & ";
		}

		cout << "\\\\" << endl;
	}
	cout << endl;
}
vector<precision> vectorGenerator(int maxInt, int n, precision decimal){
	precision random;
	vector<precision> b;
	for(int j=0; j<=n-1; j++){
		random = rand() % maxInt * pow(-1.0,(precision) (rand() % maxInt));
		// random = random/decimal;
		b.push_back(random);
	}
	return b;
}
// The arguement a is for if we are generating a=0 or LU==1
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
precision vectorPNorm(precision p, vector<precision> x){
	int n = x.size();
	x[0] = pow(fabs(x[0]), p);
	for(int i=1; i<=n-1; i++){
		x[0] = x[0] + pow(fabs(x[i]), p);
	}
	x[0] = pow(fabs(x[0]), 1.0/p);
	return x[0];
}
vector<precision> matVecProd(vector<vector<precision>> A, vector<precision> v){
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
vector<precision> vecMatProd(vector<precision> v, vector<vector<precision>> A){
	int n = v.size();
	int m = A[0].size();
	vector<precision> b;
	for(int i=0; i<=m-1; i++){
		b.push_back(0);
		for(int j=0; j<=n-1; j++){
			b[i] = b[i] + A[j][i]*v[j];
		}
	}
	return b;
}

vector<precision> reflectorUseSingle(vector<precision> v, vector<precision> u, int i);

vector<vector<precision>> leastSquaresTrap(vector<vector<precision>> A);

vector<precision> leastSquaresSolve(vector<vector<precision>> A, vector<precision> b);








int main(){
	srand(time(NULL));
	int maxInt = 10;
	int n = 6;
	int s = 25;

	// vector<precision> v{1, 3, 1, 5};
	// //v = vectorGenerator(maxInt, n, 0);
	// print(v);

	// v = reflectorUseSingle(v, v, 0);
	// print(v);

	vector<vector<precision>> A{{2, -1}, {1, 2}, {1, 1}};
	vector<vector<precision>> B{{2, -1}, {1, 2}, {1, 1}};
	vector<precision> b{2, 1, 4};

	// vector<vector<precision>> A{{1, 1, 1}, {1, 1, 0}, {0, 1, 1}, {1, 0, 0}, {0, 0, 1}};
	// vector<precision> b{89, 67, 53, 35, 20};

	// vector<vector<precision>> A{{2, 2, 4}, {1, 3, -2}, {3, 1, 3}};
	// vector<precision> a{18, 1, 14};

	print(A);
	A = leastSquaresTrap(A);
	printVec(b);
	b = leastSquaresSolve(A, b);
	printVec(b);

	// vector<vector<precision>> B{ {5.0, 1.0, -3.0, 1.0}, {10.0, 5.0, 12.0, -3.0}, {5.0, -10.0, 23.0, 5.0}, {15.0, -6.0, 19.0, 7.0}, {8.0, -6.0, -5.0, 3.0} };
	// vector<precision> b{1,-2,-3,4};
	// print(b);
	// b = matVecProd(B, b);

	// print(B);
	// B = leastSquaresTrap(B);
	// printVec(b);
	// b = leastSquaresSolve(B, b);
	// print(b);



	// vector<vector<precision>> A;
	// // There will be n rows no matter what is randomly chosen
	// for(int i=0; i<=n-1; i++){
	// 	A.push_back(vector<precision>());
	// }

	// vector<int> e;
	// e.push_back(rand()%n);
	// int ran = rand() % n;
	// for(int i=0; i<=ran; i++){
	// 	int rando = rand() % n;

	// 	// This checks for randos that are the same If they are the same then they do not get added
	// 	// but if they are not the same then the new rando gets added to the back
	// 	int duplicate = 0;
	// 	for(int j=0; j<=e.size()-1; j++){
	// 		if(rando == e[j]){
	// 			duplicate++;
	// 		}
	// 	}
	// 	if(duplicate == 0){
	// 		e.push_back(rando);
	// 	}
	// }
	// print(e);
	// // As there could have been duplicates the amount of columns we randomly chose may have decreased
	// ran = e.size();

	// // This fills A with initial e_i chosen at random
	// for(int i=0; i<=ran-1; i++){
	// 	// This adds 0 column
	// 	for(int j=0; j<=n-1; j++){
	// 		A[j].push_back(0);
	// 	}
	// 	A[e[i]][i] = 1;
	// }
	// print(A);

	// // This is for applying every Q_i to A
	// for(int i=0; i<=s-1; i++){
	// 	// This applies Q_i to all elementary columns we have chosen from Q
	// 	for(int k=0; k<=ran-1; k++){
	// 		vector<precision> vi;
	// 		vi = vectorGenerator(maxInt, n, 10);

	// 		// This calculates the norm squared of vi
	// 		precision norm = 0;
	// 		for(int j=0; j<=n-1; j++){
	// 			norm = norm + vi[j]*vi[j];
	// 		}

	// 		// w is in A and v is in vi calculates v^T*w
	// 		precision viTwi = 0;
	// 		for(int j=0; j<=n-1; j++){
	// 			viTwi = viTwi + vi[j]*A[j][k];
	// 		}

	// 		// This updates each w_i
	// 		for(int j=0; j<=n-1; j++){
	// 			A[j][k] = A[j][k] -2*viTwi*vi[j]/norm;
	// 		}
	// 	}
	// }
	// print(A);

	// vector<precision> a;
	// a = vectorGenerator(maxInt, n, 10);
	// cout << "a = ";
	// print(a);
	// vector<precision> xmin;
	// xmin = vectorGenerator(maxInt, ran, 10);
	// cout << "xmin = ";
	// print(xmin);
	// vector<precision> a1;
	// a1 = matVecProd(A, xmin);
	// cout << "a1 = ";
	// print(a1);
	// vector<precision> a2;
	// for(int i=0; i<=n-1; i++){
	// 	a2.push_back(a[i]-a1[i]);
	// }
	// cout << "a2 = ";
	// print(a2);
	// print(vecMatProd(a2, A));

	// A = leastSquaresTrap(A);
	// a2 = leastSquaresSolve(A, a);
	// print(a2);
	// for(int i=0; i<=ran-1; i++){
	// 	xmin[i] = a2[i];
	// }
	// a1 = matVecProd(A, xmin);
	// for(int i=0; i<=n-1; i++){
	// 	a2[i] = a[i] - a1[i];
	// }
	// print(vecMatProd(a2, A));





}












// This computes the vector Hu for any vector u where H is reflector for vector v on ith stage
vector<precision> reflectorUseSingle(vector<precision> v, vector<precision> u, int i){
	int n = v.size();

	// This turns v into x needed to create H, but x is only the elements after v[i-1]
	// We need to calculate the two norm of v_i because x_i = v_i + ||v_i||e_1
	precision norm = 0;
	for(int j=i; j<=n-1; j++){
		norm = norm + v[j]*v[j];
	}
	norm = pow(norm, 0.5);
	v[i] = v[i] + norm;

	// We can see that ||x||^2 = 2*||v||*(||v|| minus/plus v_i), but v_i = xi minus/plus x_i and v[i] = x_i
	norm = 2*norm*(norm + v[i]-norm);

	// This transforms the bottom of u which is u + (a*xT*u)*x, remember v is x 
	precision xTu = 0;
	for(int j=i; j<=n-1; j++){
		xTu = xTu + v[j]*u[j];
	}
	for(int j=i; j<=n-1; j++){
		u[j] = u[j] - 2*xTu*v[j]/norm;
	}

	return u;

}

// This computes the least squares for min ||b-Ax||
vector<vector<precision>> leastSquaresTrap(vector<vector<precision> > A){

	int n = A.size();
	int k = A[0].size();
	int p;
	//This if statement sets p which determines if the matrix is square or not.
	if(n==k){
		p = k-1;
	} else{
		p = k;
	}

	// This will store the original first element of each v used to create the Hi
	vector<precision> vi0;

	// We need to do k reflector matrices H and apply them to A and b
	for(int i=0; i<=p-1; i++){
		vi0.push_back(A[i][i]);

		// This solves for the vnorm
		precision norm = 0;
		for(int j=i; j<=n-1; j++){
			norm = norm + A[j][i]*A[j][i];
		}
		norm = pow(norm, 0.5);

		// This changes the diagonal to the norm which is what happens when Hi * vi 
		// This is where if we will have norm be positive or negative for numerical reasons
		A[i][i] = -1*norm;

		// We can see that ||x||^2 = 2*||v||*(||v|| + v_1) = 2*A[i][i]*(A[i][i] minus/plus v_i)
		norm = 2*A[i][i]*(A[i][i] - vi0[i]);

		// We need to find and apply Hi to all columns after ith column, the ith column we are using to store
		// x_i except for the first element which is vi_0 + ||vi||. vi_0 is stored in vi0 and ||v|| is in A[i][i]
		for(int j=i+1; j<=k-1; j++){

			// This solves for xT*u to get Hi*u = u + (a*xT*u)*x, the first element of x is vi0_i + vnorm which is diagonal of R
			precision xTu = (vi0[i]-A[i][i])*A[i][j];
			for(int l=i+1; l<=n-1; l++){
				xTu = xTu + A[l][i]*A[l][j];
			}

			// This changes elements past ith element of each column vector after ith column
			A[i][j] = A[i][j] - 2*xTu*(vi0[i]-A[i][i])/norm;
			for(int l=i+1; l<=n-1; l++){
				A[l][j] = A[l][j] - 2*xTu*A[l][i]/norm;
			}
		}

		// print(A);
	}

	A.push_back(vi0);
	// b is then xmin up to kth element and then the rest are zeros.
	return A;

}


vector<precision> leastSquaresSolve(vector<vector<precision>> A, vector<precision> b){
	// A has an extra row which is the first element of v
	int n = A.size();
	n--;
	int k = A[0].size();
	int p;
	// This if statement sets p which determines if the matrix is square or not.
	if(n==k){
		p = k-1;
	} else{
		p = k;
	}

	// This applies each H_i to b
	for(int i=0; i<=p-1; i++){
		// We can see that ||x||^2 = 2*||v||*(||v|| + v_1) = 2*A[i][i]*(A[i][i] minus/plus v_i)
		precision norm = 2*A[i][i]*(A[i][i] - A[n][i]);

		// This then applies Hi to b
		// This solves for xT*b to get Hi*b = b + (a*xT*b)*x, the first element of x is vi0_i + vnorm which is diagonal of R
		precision xTu = (A[n][i]-A[i][i])*b[i];
		for(int l=i+1; l<=n-1; l++){
			xTu = xTu + A[l][i]*b[l];
		}	
		b[i] = b[i] - 2*xTu*(A[n][i]-A[i][i])/norm;
		for(int l=i+1; l<=n-1; l++){
			b[l] = b[l] - 2*xTu*A[l][i]/norm;
		}
	}


	// This solves the system Rx = c by row oriented, but going from bottom->top because R=Upper
	for(int i=k-1; i>=0; i--){
		// Each row we need to update ith minus one constants
		for(int j=k-1; j>i; j--){
			b[i] = b[i] - A[i][j]*b[j];
		}
		b[i] = b[i]/A[i][i];
	}

	for(int i=k; i<=n-1; i++){
		b[i] = 0;
	}

	// b is then xmin up to kth element and then the rest are zeros.
	return b;
}



