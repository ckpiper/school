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
#include "../../vectorFuncs.h"
#include <cmath>

// const pi = M_PI;


vector<vector<precision>> setZeros(int cells, int N);
vector<precision> initial(int cells, int example, precision h);
vector<vector<precision>> exact(precision a, precision h, precision k, int cells, int example, precision T);
vector<vector<precision>> constantV(precision a, precision h, precision k, int cells, int example, precision T);
vector<vector<precision>> linearV(precision a, precision h, precision k, int cells, int example, precision T);
precision alpha(precision mp1, precision m, precision mm1, precision h);
vector<vector<precision>> minmodV(precision a, precision h, precision k, int cells, int example, precision T);

precision vectorL2(vector<precision> v){
	precision norm = 0;
	int n = v.size();
	for(int i=0; i<n; i++){
		norm = norm + v[i]*v[i];
	}
	norm = sqrt(norm);
	return norm;
}


int main(){
	int example = 2;				// 1 = 0.25-0.75 step,  2 = sin, 3 = 0-0.5 step, 4 = 0.5 - | x - 0.5 |, 5 = cos
	precision a = 1;
	int cells = 25;
	precision L = 1.0;
	precision h = L/cells;
	precision scale = 0.25;
	precision k = h/a * scale;
	precision T = 100*k;

	// Round it to nearest integer as it should be an exact division add 1 for initial
	// int = floor function brings N down then add 1 for initial then add one in  setZeros function for final
	int N, final;
	if(fabs(round(T/k) - T/k) < 0.000001){
		N = round(T/k) + 1;
		final = 0;
		printf("epsilon Main\n");
	} else {
		N = int(T/k) + 1;
		final = 1;
		printf("non-epsilon Main\n");
	}

	cout << "\nExact" << endl;
	vector<vector<precision>> u = exact(a, h, k, cells, example, T);
	cout << "\nConstant V" << endl;
	vector<vector<precision>> v1 = constantV(a, h, k, cells, example, T);
	cout << "\nLinear V" << endl;
	vector<vector<precision>> v2 = linearV(a, h, k, cells, example, T);
	cout << "\nLinear Minmod V\n" << endl;
	vector<vector<precision>> v3 = minmodV(a, h, k, cells, example, T);

	vector<vector<vector<precision>>> vv;
	vv.push_back(u);
	vv.push_back(v1);
	vv.push_back(v2);
	vv.push_back(v3);

	vector<string> fileName;
	fileName.push_back("data/exact.txt");
	fileName.push_back("data/constant.txt");
	fileName.push_back("data/linear.txt");
	fileName.push_back("data/minmod.txt");

	// This prints the results of the methods to a txt file in the data directory in this directory then to be read in and plotted by python
	for(int m=0; m<4; m++){
		ofstream myfile (fileName[m]);
		if (myfile.is_open()) {
			for(int i=0; i<N; i++){
				for(int j=0; j<cells; j++){
					myfile << vv[m][i][j] << " ";
				}
				myfile << "\n";
			}
			// This is for the final time step if we have a smaller final time step
			if(final==1){
				for(int j=0; j<cells; j++){
					myfile << vv[m][N][j] << " ";
				}
				myfile << "\n";
			}

			myfile.close();
		} else {
			cout << "Unable to open file";
		}
	}


	// This will take the l2 norm of the errors vector at time T of each scheme then place them in a vector of errors
	vector<precision> errConst;
	vector<precision> errLinear;
	vector<precision> errMinmod;
	vector<precision> errors;

	cells = 16;
	for(int i=0; i<=6; i++){
		h = L/cells;
		k = h/a * scale;

		if(fabs(round(T/k) - T/k) < 0.000001){
			N = round(T/k) + 1;
			final = 0;
			printf("epsilon Main\n");
		} else {
			N = int(T/k) + 1;
			final = 1;
			printf("non-epsilon Main\n");
		}

		cout << "cells = " << cells << ", h = " << h << endl;
		u = exact(a, h, k, cells, example, T);
		v1 = constantV(a, h, k, cells, example, T);
		v2 = linearV(a, h, k, cells, example, T);
		v3 = minmodV(a, h, k, cells, example, T);

		errors = subtract(u[N-1], v1[N-1]);
		// errConst.push_back(vectorPNorm(2.0, errors));
		errConst.push_back(vectorL2(errors));
		errConst[i] = errConst[i] * sqrt(h);

		errors = subtract(u[N-1], v2[N-1]);
		// errLinear.push_back(vectorPNorm(2.0, errors));
		errLinear.push_back(vectorL2(errors));
		errLinear[i] = errLinear[i] * sqrt(h);

		errors = subtract(u[N-1], v3[N-1]);
		// errMinmod.push_back(vectorPNorm(2.0, errors));
		errMinmod.push_back(vectorL2(errors));
		errMinmod[i] = errMinmod[i] * sqrt(h);

		cells = cells*2;
		cout << endl;
	}

	cout << "----- L2 Norm of Constant V -----" << endl;
	print(errConst);
	cout << "----- L2 Norm of Linear V -----" << endl;
	print(errLinear);
	cout << "----- L2 Norm of Minmod V -----" << endl;
	print(errMinmod);


	return 0;
}



vector<vector<precision>> setZeros(int cells, int N){
	vector<vector<precision>> vv;
	for(int i=0; i<N; i++){
		vv.push_back({});
		for(int j=0; j<cells; j++){
			vv[i].push_back(0);
		}
	}
	return vv;
}


vector<precision> initial(int cells, int example, precision h){
	vector<precision> u;
	for(int i=0; i<cells; i++){
		u.push_back(0);
	}

	precision L = h*cells;
	for(int i=0; i<cells; i++){
		precision x = i*h+ h/2 ;

		if (example == 1){
			if( x >= L*0.25 && x <= L*0.75){
				u[i] = 1;
			}else{
				u[i] = 0;
			}
		} else if(example == 2){
			u[i] = sin(x*2*M_PI);
		} else if(example == 3){
			if(x <= L*0.5){
				u[i] = 1;
			}else{
				u[i] = 0;
			}
		} else if(example == 4){
			if (x<=0.5){
				u[i] = 0.5 - (0.5 - x);
			}else{
				u[i] = 0.5 - (x - 0.5);
			}
		} else if(example == 5){
			u[i] = cos(x*2*M_PI);
		}
	}
	return u;
}


vector<vector<precision>> exact(precision a, precision h, precision k, int cells, int example, precision T){
	// Round it to nearest integer as it should be an exact division add 1 for initial
	// int = floor function brings N down then add 1 for initial then add one in  setZeros function for final
	vector<vector<precision>> uu;
	int N, final;
	if(fabs(round(T/k) - T/k) < 0.000001){
		N = round(T/k) + 1;
		final = 0;
		// printf("epsilon Exact\n");
		uu = setZeros(cells, N);
	} else {
		N = int(T/k) + 1;
		final = 1;
		// printf("non-epsilon Exact\n");
		uu = setZeros(cells, N+1);
	}

	//This is the positions of the middle of each cell
	precision L = cells*h;
	vector<precision> x;
	for(int i=0; i<cells; i++){
		x.push_back(i*h + h/2);
	}

	// This is the double nested for loop to find the solution at each time
	for(int i=0; i<N; i++){
		precision move = a*i*k; // This is the amount each point moves 
		for(int j=0; j<cells; j++){
			precision z = x[j] - move;  // z = x - a*t
			if (example == 1){
				// fmod only returns a number smaller than L in magnitude and same sign as z
				// So I have to add L if it is negative to get it back into [0,L] interval
				precision mod = fmod(z,L);
				if(mod < 0){
					mod = mod + L;
				}
				if(mod >= L*0.25 && mod <= L*0.75){
					uu[i][j] = 1;
				}else{
					uu[i][j] = 0;
				}
			} else if(example == 2){
				precision mod = fmod(z, L);
				if(mod < 0){
					mod = mod + L;
				}
				uu[i][j] = sin(mod*2*M_PI);
			} else if(example == 3){
				precision mod = fmod(z,L);
				if(mod < 0){
					mod = mod + L;
				}
				if(mod <= L*0.5){
					uu[i][j] = 1;
				}else{
					uu[i][j] = 0;
				}
			} else if(example == 4){
				precision mod = fmod(z,L);
				if(mod < 0){
					mod = mod + L;
				}
				if (mod<=0.5){
					uu[i][j] = 0.5 - (0.5 - mod);
				}else{
					uu[i][j] = 0.5 - (mod - 0.5);
				}
			} else if(example == 5){
				precision mod = fmod(z, L);
				if(mod < 0){
					mod = mod + L;
				}
				uu[i][j] = cos(mod*2*M_PI);
			}
		}
	}
	// If k does not divide T exactly then we have a shortened last time step. 
	// This will be the (N+1)th row as we said it would be when we set Zeroes at top with N+1.
	// It is the same exact code as before but with N and T instead of i and a*i respectively
	if(final == 1){
		precision move = a*T; 
		for(int j=0; j<cells; j++){
			precision z = x[j] - move;
			if (example == 1){
				precision mod = fmod(z,L);
				if(mod < 0){
					mod = mod + L;
				}
				if(mod >= L*0.25 && mod <= L*0.75){
					uu[N][j] = 1;
				}else{
					uu[N][j] = 0;
				}
			} else if(example == 2){
				precision mod = fmod(z, L);
				if(mod < 0){
					mod = mod + L;
				}
				uu[N][j] = sin(mod*2*M_PI);
			} else if(example == 3){
				precision mod = fmod(z,L);
				if(mod < 0){
					mod = mod + L;
				}
				if(mod <= L*0.5){
					uu[N][j] = 1;
				}else{
					uu[N][j] = 0;
				}
			} else if(example == 4){
				precision mod = fmod(z,L);
				if(mod < 0){
					mod = mod + L;
				}
				if (mod<=0.5){
					uu[N][j] = 0.5 - (0.5 - mod);
				}else{
					uu[N][j] = 0.5 - (mod - 0.5);
				}
			} else if(example == 5){
				precision mod = fmod(z, L);
				if(mod < 0){
					mod = mod + L;
				}
				uu[N][j] = cos(mod*2*M_PI);
			}
		}
	}

	return uu;
}


vector<vector<precision>> constantV(precision a, precision h, precision k, int cells, int example, precision T){
	// Round it to nearest integer as it should be an exact division add 1 for initial
	// int = floor function brings N down then add 1 for initial then add one in  setZeros function for final
	vector<vector<precision>> vv;
	int N, final;
	if(fabs(round(T/k) - T/k) < 0.000001){
		N = round(T/k) + 1;
		final = 0;
		// printf("epsilon Consant\n");
		vv = setZeros(cells, N);
	} else {
		N = int(T/k) + 1;
		final = 1;
		// printf("non-epsilon Consant\n");
		vv = setZeros(cells, N+1);
	}

	precision lam = k/h;

	vv[0] = initial(cells, example, h);
	for(int i=1; i<N; i++){
		for(int j=1; j<cells; j++){
			vv[i][j] = vv[i-1][j] - a*lam*(vv[i-1][j] - vv[i-1][j-1]);
		}
		vv[i][0] = vv[i-1][0] - a*lam*(vv[i-1][0] - vv[i-1][cells-1]);
	}

	if(final == 1){
		precision kFin = T-k*N;
		precision lamFin = kFin/h;
		for(int j=1; j<cells; j++){
			vv[N][j] = vv[N-1][j] - a*lamFin*(vv[N-1][j] - vv[N-1][j-1]);
		}
		vv[N][0] = vv[N-1][0] - a*lam*(vv[N-1][0] - vv[N-1][cells-1]);
	}

	return vv;
}


vector<vector<precision>> linearV(precision a, precision h, precision k, int cells, int example, precision T){
	// Round it to nearest integer as it should be an exact division add 1 for initial
	// int = floor function brings N down then add 1 for initial then add one in  setZeros function for final
	vector<vector<precision>> vv;
	int N, final;
	if(fabs(round(T/k) - T/k) < 0.000001){
		N = round(T/k) + 1;
		final = 0;
		// printf("epsilon Linear\n");
		vv = setZeros(cells, N);
	} else {
		N = int(T/k) + 1;
		final = 1;
		// printf("non-epsilon Linear\n");
		vv = setZeros(cells, N+1);
	}

	precision lam = k/h;
	precision lam2 = lam*lam;
	precision mu = k/(h*h);

	vv[0] = initial(cells, example, h);
	for(int i=1; i<N; i++){
		for(int j=2; j<cells-1; j++){
			vv[i][j] = vv[i-1][j] - a*lam*(vv[i-1][j] - vv[i-1][j-1]) - 0.25*a*mu*(h-a*k)*(vv[i-1][j+1] - vv[i-1][j] - vv[i-1][j-1] + vv[i-1][j-2]);
		}
		vv[i][0] = vv[i-1][0] - a*lam*(vv[i-1][0] - vv[i-1][cells-1]) - 0.25*a*mu*(h-a*k)*(vv[i-1][1] - vv[i-1][0] - vv[i-1][cells-1] + vv[i-1][cells-2]);
		vv[i][1] = vv[i-1][1] - a*lam*(vv[i-1][1] - vv[i-1][0]) - 0.25*a*mu*(h-a*k)*(vv[i-1][2] - vv[i-1][1] - vv[i-1][0] + vv[i-1][cells-1]);
		vv[i][cells-1] = vv[i-1][cells-1] - a*lam*(vv[i-1][cells-1] - vv[i-1][cells-2]) - 0.25*a*mu*(h-a*k)*(vv[i-1][0] - vv[i-1][cells-1] - vv[i-1][cells-2] + vv[i-1][cells-3]);//vv[i][0];
		// for (int j=2; j<cells-1; j++){
		// 	vv[i][j] = 0.25*a*vv[i-1][j+1]*(a*lam2 - lam) + vv[i-1][j]*(1-0.75*a*lam - 0.25*a*a*lam2) + 0.25*a*vv[i-1][j-1]*(5*lam - a*lam2) + 0.25*a*vv[i-1][j-2]*(a*lam2 - lam);
		// }
		// vv[i][0] = 0.25*a*vv[i-1][1]*(a*lam2 - lam) + vv[i-1][0]*(1-0.75*a*lam - 0.25*a*a*lam2) + 0.25*a*vv[i-1][cells-2]*(5*lam - a*lam2) + 0.25*a*vv[i-1][cells-3]*(a*lam2 - lam);
		// vv[i][1] = 0.25*a*vv[i-1][2]*(a*lam2 - lam) + vv[i-1][1]*(1-0.75*a*lam - 0.25*a*a*lam2) + 0.25*a*vv[i-1][0]*(5*lam - a*lam2) + 0.25*a*vv[i-1][cells-2]*(a*lam2 - lam);
		// vv[i][cells-1] = vv[i][0];
	}

	if(final == 1){
		precision kFin = T-k*N;
		precision lamFin = kFin/h;
		precision muFin = kFin/(h*h);
		for(int j=2; j<cells-1; j++){
			vv[N][j] = vv[N-1][j] - a*lamFin*(vv[N-1][j] - vv[N-1][j-1]) - 0.25*a*muFin*(h-a*kFin)*(vv[N-1][j+1] - vv[N-1][j] - vv[N-1][j-1] + vv[N-1][j-2]);
		}
		vv[N][0] = vv[N-1][0] - a*lamFin*(vv[N-1][0] - vv[N-1][cells-2]) - 0.25*a*muFin*(h-a*kFin)*(vv[N-1][1] - vv[N-1][0] - vv[N-1][cells-2] + vv[N-1][cells-3]);
		vv[N][1] = vv[N-1][1] - a*lamFin*(vv[N-1][1] - vv[N-1][0]) - 0.25*a*muFin*(h-a*kFin)*(vv[N-1][2] - vv[N-1][1] - vv[N-1][0] + vv[N-1][cells-2]);
		vv[N][cells-1] = vv[N-1][cells-1] - a*lamFin*(vv[N-1][cells-1] - vv[N-1][cells-2]) - 0.25*a*muFin*(h-a*kFin)*(vv[N-1][0] - vv[N-1][cells-1] - vv[N-1][cells-2] + vv[N-1][cells-3]);//vv[N][0];
	}

	return vv;
}


precision alpha(precision mp1, precision m, precision mm1, precision h){
	mp1 = (mp1 - m) / h;
	mm1 = (m - mm1) / h;
	// if(signbit(mp1)*signbit(mm1) > 0){

	// }
	if(mp1*mm1 <= 0){
		return 0.0;
	} else if(fabs(mp1) <= fabs(mm1)){
		return mp1;
	} else {
		return mm1;
	}

	return m;
}
vector<vector<precision>> minmodV(precision a, precision h, precision k, int cells, int example, precision T){
	// Round it to nearest integer as it should be an exact division add 1 for initial
	// int = floor function brings N down then add 1 for initial then add one in  setZeros function for final
	vector<vector<precision>> vv;
	int N, final;
	if(fabs(round(T/k) - T/k) < 0.000001){
		N = round(T/k) + 1;
		final = 0;
		// printf("epsilon Linear minmod\n");
		vv = setZeros(cells, N);
	} else {
		N = int(T/k) + 1;
		final = 1;
		// printf("non-epsilon Linear minmod\n");
		vv = setZeros(cells, N+1);
	}

	precision lam = k/h;
	precision mu = k/(h*h);

	vv[0] = initial(cells, example, h);
	for(int i=1; i<N; i++){
		for(int j=2; j<cells-1; j++){
			vv[i][j] = vv[i-1][j] - a*lam*( (vv[i-1][j]-vv[i-1][j-1]) + 0.5*(h-a*k)*(alpha(vv[i-1][j+1], vv[i-1][j], vv[i-1][j-1], h) - alpha(vv[i-1][j], vv[i-1][j-1], vv[i-1][j-2], h)));
		}
		vv[i][0] = vv[i-1][0] - a*lam*( (vv[i-1][0]-vv[i-1][cells-1]) + 0.5*(h-a*k)*(alpha(vv[i-1][1], vv[i-1][0], vv[i-1][cells-1], h) - alpha(vv[i-1][0], vv[i-1][cells-1], vv[i-1][cells-2], h)));	
		vv[i][1] = vv[i-1][1] - a*lam*( (vv[i-1][1]-vv[i-1][0]) + 0.5*(h-a*k)*(alpha(vv[i-1][2], vv[i-1][1], vv[i-1][0], h) - alpha(vv[i-1][1], vv[i-1][0], vv[i-1][cells-1], h)));
		vv[i][cells-1] = vv[i-1][cells-1] - a*lam*( (vv[i-1][cells-1]-vv[i-1][cells-2]) + 0.5*(h-a*k)*(alpha(vv[i-1][0], vv[i-1][cells-1], vv[i-1][cells-2], h) - alpha(vv[i-1][cells-1], vv[i-1][cells-2], vv[i-1][cells-3], h)));
	}

	if(final == 1){
		precision kFin = T-k*N;
		precision lamFin = kFin/h;
		precision muFin = kFin/(h*h);
		for(int j=2; j<cells-1; j++){
			vv[N][j] = vv[N-1][j] - a*lamFin*( (vv[N-1][j]-vv[N-1][j-1]) + 0.5*(h-a*kFin)*(alpha(vv[N-1][j+1], vv[N-1][j], vv[N-1][j-1], h) - alpha(vv[N-1][j], vv[N-1][j-1], vv[N-1][j-2], h)));
		}
		vv[N][0] = vv[N-1][0] - a*lamFin*( (vv[N-1][0]-vv[N-1][cells-1]) + 0.5*(h-a*kFin)*(alpha(vv[N-1][1], vv[N-1][0], vv[N-1][cells-1], h) - alpha(vv[N-1][0], vv[N-1][cells-1], vv[N-1][cells-2], h)));	
		vv[N][1] = vv[N-1][1] - a*lamFin*( (vv[N-1][1]-vv[N-1][0]) + 0.5*(h-a*kFin)*(alpha(vv[N-1][2], vv[N-1][1], vv[N-1][0], h) - alpha(vv[N-1][1], vv[N-1][0], vv[N-1][cells-1], h)));
		vv[N][cells-1] = vv[N-1][cells-1] - a*lamFin*( (vv[N-1][cells-1]-vv[N-1][cells-2]) + 0.5*(h-a*kFin)*(alpha(vv[N-1][0], vv[N-1][cells-1], vv[N-1][cells-2], h) - alpha(vv[N-1][cells-1], vv[N-1][cells-2], vv[N-1][cells-3], h)));
	}

	return vv;
}
