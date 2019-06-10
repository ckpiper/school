	# This is Project 3 for Numerical Solutions for Partial Differential Equations
import math
import matplotlib.pyplot as plt
import numpy as np

pi = math.pi

# A is a 2d array
# A is a 2x2 matrix for project 3
def exact(XI, T, mesh, k, initial, bound, B1, B2, c, rho, u0):
	M = mesh-1 
	h = 1/M
	rangM = np.asarray([z for z in range(0, M+1)])

	# This if statement is for floating point round-off error purposes. If T/k divides perfectly (perfectly meaning equals an integer, but might not on computer),
			# then we round T/k to the integer it is with-in epsilon about and have N equal that plus 1. Hence we do not need a separate final time step.
			# If not then we floor T/k and set final=1 so that the final time step is applied after the loop. 
			# Notice N is always the amount of steps we can do with just k withouth kFin
	# The 1st dimension is system size (size of vector u), 2nd dimension is time, 3rd dimension is space
			# When you print our array each u_i will be own piece and then time is vertical, space is horizontal
	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		u = np.zeros([ XI.shape[0], N, M+1,])
		rangN = np.asarray([z for z in range(0, N)])
		# print("epsilon")
	else:
		N = int(T/k) + 1
		final = 1
		u = np.zeros([ XI.shape[0], N+1, M+1,])
		rangN = np.asarray([z for z in range(0, N)])
		# print("non-epsilon")

	if (initial==1):
		# Main Solution
		for n in rangN:
			u[0,n,:] = c*rho*( np.sin(rangM/M-(u0+c)*n*k) - np.cos(rangM/M-(u0-c)*n*k) )
			u[1,n,:] = np.sin(rangM/M-(u0+c)*n*k) + np.cos(rangM/M-(u0-c)*n*k)
		# Last step
		if(final == 1):
			u[0,N,:] = c*rho*( np.sin(rangM/M-(u0+c)*T) - np.cos(rangM/M-(u0-c)*T) )
			u[1,N,:] = np.sin(rangM/M-(u0+c)*T) + np.cos(rangM/M-(u0-c)*T)

	elif(initial==2):
		# Main Solution
		for n in rangN:
			u[0,n,:] = 3+3*rangM/M
			u[1,n,:] = 4*n*k + 3*rangM/M + 5
		# Last step
		if(final == 1):
			u[0,N,:] = 3+3*rangM/M
			u[1,N,:] = 4*T + 3*rangM/M + 5

	elif(initial==3):
		# Main Solution
		for n in rangN:
			u[0,n,:] = c*rho*(6*u0*n*k-4*c*n*k-6*rangM/M)
			u[1,n,:] = 6*c*n*k-4*u0*n*k+4*rangM/M
		# Last step
		if(final == 1):
			u[0,N,:] = c*rho*(6*u0*T-4*c*T-6*rangM/M)
			u[1,N,:] = 6*c*T-4*u0*T+4*rangM/M

	elif(initial==4):												# Example to present
		# Main Solution
		for n in rangN:
			u[0,n,:] = -1*n*k-rangM/M
			u[1,n,:] = n*k-2*rangM/M
		# Initial Solution
		if(final == 1):
			u[0,N,:] = -1*T-rangM/M 
			u[1,N,:] = T-2*rangM/M 

	elif(initial==5):
		# Main Solution
		for n in rangN:
			u[0,n,:] = -2*n*k+3*rangM/M
			u[1,n,:] = n*k+3*rangM/M
		# Initial Solution
		if(final == 1):
			u[0,N,:] = -2*T+3*rangM/M
			u[1,N,:] = T+3*rangM/M

	elif(initial==6):
		# Main Solution
		for n in rangN:
			u[0,n,:] = np.sin(rangM/M)
			u[1,n,:] = np.cos(rangM/M)
		# Initial SOlution
		if(final == 1):
			u[0,n,:] = np.sin(rangM/M)
			u[1,n,:] = np.cos(rangM/M)

	return u


###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################


# num is always just the example I want to use
def initCond(num, mesh, LAM, c, rho):
	M = mesh-1
	h = 1/M
	rang = np.asarray([z for z in range(0, M+1)])

	u = np.empty([LAM.shape[0], M+1])

	if(num==1):
		u[0] = c*rho*( np.sin(rang/M) - np.cos(rang/M) )
		u[1] = np.sin(rang/M) + np.cos(rang/M)

	elif(num==2):
		u[0] = 3 + 3*rang/M
		u[1] = 5 + 3*rang/M

	elif(num==3):
		u[0] = -6*c*rho*rang/M
		u[1] = 4*rang/M

	elif(num==4):
		u[0] = -1*rang/M 
		u[1] = -2*rang/M 

	elif(num==5):
		u[0] = 3*rang/M
		u[1] = 3*rang/M

	elif(num==6):
		u[0] = np.sin(rang/M)
		u[1] = np.cos(rang/M)

	return u


###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################


# num is always just the example I want to use
def force(num, mesh, t, rangM, rang, XI, c, rho, u0):
	M = mesh-1
	F = np.zeros([XI.shape[0],len(rangM)])

	if(num==1):
		F[0] = 0
		F[1] = 0

	elif(num==2):
		F[0] = 3*(u0+c**2*rho)
		F[1] = 3*(u0+1/rho) + 4

	elif(num==3):
		F[0] = 0
		F[1] = 0

	elif(num==4):
		F[0] = -1
		F[1] = 4

	elif(num==5):
		F[0] = -5
		F[1] = -2

	elif(num==6):
		F[0] = u0*np.cos(rangM/M) - c**2*rho*np.sin(rangM/M)
		F[1] = np.cos(rangM/M)/rho - u0*np.sin(rangM/M)

	FW = np.dot(XI,F)

	return FW[rang]


###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################


def boundFunc1(num, t, rang, B, c, rho, u0):
	u = np.empty([B.shape[0]])

	if (num==1):
		u[0] = math.sin(-(u0+c)*t)*(c*rho*B[0,0] + B[0,1]) + math.cos(-(u0-c)*t)*(B[0,1] - c*rho*B[0,0])
		u[1] = math.sin(-(u0+c)*t)*(c*rho*B[1,0] + B[1,1]) + math.cos(-(u0-c)*t)*(B[1,1] - c*rho*B[1,0])

	elif(num==2):
		u[0] = 3*B[0,0] + B[0,1]*(4*t+5)
		u[1] = 3*B[1,0] + B[1,1]*(4*t+5)

	elif(num==3):
		u[0] = B[0,0]*(c*rho*(6*u0*t-4*c*t)) + B[0,1]*(6*c*t-4*u0*t)
		u[1] = B[1,0]*(c*rho*(6*u0*t-4*c*t)) + B[1,1]*(6*c*t-4*u0*t)

	# elif(num==4):
	# 	u[0] = -1*t - 1
	# 	u[1] = t - 2

	# elif(num==5):
	# 	u[0] = t+3
	# 	u[1] = 3-2*t

	elif(num==6):
		u[0] = 0
		u[1] = 1

	return u[rang]



###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################



def boundFunc2(num, t, rang, B, c, rho, u0):
	u = np.empty([B.shape[0]])

	if (num==1):
		u[0] = math.sin(1-(u0+c)*t)*(c*rho*B[0,0] + B[0,1]) + math.cos(1-(u0-c)*t)*(B[0,1] - c*rho*B[0,0])
		u[1] = math.sin(1-(u0+c)*t)*(c*rho*B[1,0] + B[1,1]) + math.cos(1-(u0-c)*t)*(B[1,1] - c*rho*B[1,0])

	elif(num==2):
		u[0] = 6*B[0,0] + B[0,1]*(4*t+8)
		u[1] = 6*B[1,0] + B[1,1]*(4*t+8)

	elif(num==3):
		u[0] = B[0,0]*(c*rho*(6*u0*t-4*c*t-6)) + B[0,1]*(6*c*t-4*u0*t+4)
		u[1] = B[1,0]*(c*rho*(6*u0*t-4*c*t-6)) + B[1,1]*(6*c*t-4*u0*t+4)

	elif(num==4):
		u[0] = -1*t - 1
		u[1] = t - 2

	elif(num==5):
		u[0] = 3-2*t
		u[1] = t+3

	elif(num==6):
		u[0] = math.sin(1)
		u[1] = math.cos(1)

	return u[rang]



###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################



def boundCondition(num, mesh, t, B1, B2, X, w, pos, neg, c, rho, u0):
	M = mesh-1
	# Actual Boundary Conditions ( slash is not division and ^(-1) is inverse and ^(mm/pp) is for part of whole B1*X or B2*X matrix) 
	# w[pos/neg,n+1,0/M] = [ Cp*(B1/2*X)^(pp/pm) + Cm*(B1/2*X)^(mp/mm) ]^(-1)  *  [  Cp*gp + Cm*gm - [ Cp*(B1/2*X)^(pm/pp) + Cm*(B1/2*X)^(mm/mp) ] * w[neg/pos,n+1,M/0] ]  ]
	# What I code below is just for the problem in project 3 since we know what X and B1X will be for equation aboved
	B1X = np.dot(B1,X)
	B2X = np.dot(B2,X)
	D1 = B1X[0,0] + B1X[1,0]
	E1 = B1X[0,1] + B1X[1,1]
	D2 = B2X[0,0] + B2X[1,0]
	E2 = B2X[0,1] + B2X[1,1]

	w[pos,0] = ( boundFunc1(num, t, pos, B1, c, rho, u0) + boundFunc1(num, t, neg, B1, c, rho, u0) - E1*w[neg,0] ) / D1
	w[neg,M] = ( boundFunc2(num, t, pos, B2, c, rho, u0) + boundFunc2(num, t, neg, B2, c, rho, u0) - D2*w[pos,M] ) / E2
 
	return w[neg,M], w[pos,0]


def boundConditionPos(num, mesh, t, B1, X, w, pos, c, rho, u0):
	M = mesh-1
	# we need to just find the inverse of B1X and then we have w = (B1X)^{-1} g_1
	B1X = np.dot(B1,X)
	B1XI = 1/(B1X[0,0]*B1X[1,1]-B1X[0,1]*B1X[1,0])*np.asarray([ [B1X[1,1], -1*B1X[0,1]],[-1*B1X[1,0], B1X[0,0]] ])

	w[:,0] = np.dot( B1XI, boundFunc1(num, t, pos, B1, c, rho, u0) )
 
	return w[:,0]


def boundConditionNeg(num, mesh, t, B2, X, w, neg, c, rho, u0):
	M = mesh-1
	# we need to just find the inverse of B1X and then we have w = (B2X)^{-1} g_2
	B2X = np.dot(B2,X)
	B2XI = 1/(B2X[0,0]*B2X[1,1]-B2X[0,1]*B2X[1,0])*np.asarray([ [B2X[1,1], -1*B2X[0,1]],[-1*B2X[1,0], B2X[0,0]] ])

	w[:,M] = np.dot( B2XI, boundFunc2(num, t, neg, B2, c, rho, u0) )
 
	return w[:,M]


###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################


def numericalBound(num, mesh, LAM, w, pos, neg, lam, k, n, XI, c, rho, u0):
	M = mesh-1
	MM = np.asarray([M])
	M0 = np.asarray([0])
	# Numerical Boundary Conditions
	if(num[0]==1):
		w[pos,1,M] = w[pos,0,M] - lam*LAM[pos]*(w[pos,0,M] - w[pos,0,M-1]) + k*force(num[1], mesh, k*(n+1), MM, pos, XI, c, rho, u0)
		w[neg,1,0] = w[neg,0,0] - lam*LAM[neg]*(w[neg,0,1] - w[neg,0,0])  + k*force(num[1], mesh, k*(n+1), M0, neg, XI, c, rho, u0)

	elif(num[0]==2):
		w[pos,1,M] = w[pos,1,M-1]
		w[neg,1,0] = w[neg,1,1]

	elif(num[0]==3):
		w[pos,1,M] = 2*w[pos,1,M-1] - w[pos,1,M-2]
		w[neg,1,0] = 2*w[neg,1,1] - w[neg,1,2]

	elif(num[0]==4):
		w[pos,1,M] = w[pos,0,M-1]
		w[neg,1,0] = w[neg,0,1]

	elif(num[0]==5):
		w[pos,1,M] = 2*w[pos,0,M-1] - w[pos,0,M-2]
		w[neg,1,0] = 2*w[neg,0,1] - w[neg,0,2]

	return w[pos,1,M], w[neg,1,0]



def numericalBoundNeg(num, mesh, LAM, w, neg, lam, k, n, XI, c, rho, u0):
	M = mesh-1
	M0 = np.asarray([0])
	# Numerical Boundary Conditions
	if(num[0]==1):
		w[neg,1,0:1] = w[neg,0,0:1] - lam*np.multiply(LAM[neg],(w[neg,0,1:2] - w[neg,0,0:1])) + k*force(num[1], mesh, k*(n+1), M0, neg, XI, c, rho, u0)

	elif(num[0]==2):
		w[neg,1,0] = w[neg,1,1]

	elif(num[0]==3):
		w[neg,1,0] = 2*w[neg,1,1] - w[neg,1,2]

	elif(num[0]==4):
		w[neg,1,0] = w[neg,0,1]

	elif(num[0]==5):
		w[neg,1,0] = 2*w[neg,0,1] - w[neg,0,2]

	return w[neg,1,0]



def numericalBoundPos(num, mesh, LAM, w, pos, lam, k, n, XI, c, rho, u0):
	M = mesh-1
	MM = np.asarray([M])
	# Numerical Boundary Conditions
	if(num[0]==1):
		w[pos,1,M:M+1] = w[pos,0,M:M+1] - lam*np.multiply(LAM[pos],(w[pos,0,M:M+1] - w[pos,0,M-1:M])) + k*force(num[1], mesh, k*(n+1), MM, pos, XI, c, rho, u0)

	elif(num[0]==2):
		w[pos,1,M] = w[pos,1,M-1]

	elif(num[0]==3):
		w[pos,1,M] = 2*w[pos,1,M-1] - w[pos,1,M-2]

	elif(num[0]==4):
		w[pos,1,M] = w[pos,0,M-1]

	elif(num[0]==5):
		w[pos,1,M] = 2*w[pos,0,M-1] - w[pos,0,M-2]

	return w[pos,1,M]



###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################



# This will be the upWind method for a system of linear parabolic PDEs of the form w_t + lam*w_x = 0 finite domain x=0 to x=1
# Notice this is assuming the eigenvalue decomposition has already been performed
def upWind(LAM, X, XI, T, mesh, k, initial, bound, B1, B2, c, rho, u0):
	M = mesh - 1
	h = 1/M
	lam = k/h

	# This if statement is for floating point round-off error purposes. If T/k divides perfectly (perfectly meaning equals an integer, but might not on computer),
			# then we round T/k to the integer it is with-in epsilon about and have N equal that plus 1. Hence we do not need a separate final time step.
			# If not then we floor T/k and set final=1 so that the final time step is applied after the loop. 
			# Notice N is always the amount of steps we can do with just k withouth kFin
	# The 1st dimension is system size (size of vector u), 2nd dimension is time, 3rd dimension is space
			# When you print our array each u_i will be own piece and then time is vertical, space is horizontal
	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		w = np.zeros([ X.shape[0], N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		w = np.zeros([ X.shape[0], N+1, M+1])

	# This calculates the initial condition then does w = X^(-1) f to get initial condition for w
	w[:,0,:] = np.dot(XI, initCond(initial, mesh, LAM, c, rho))

	# This is the main algorithm (slow) only for this system of two PDEs problem
	index = np.asarray([z for z in range(0,LAM.shape[0])])
	pos = np.asarray([z for z in index if LAM[z] > 0])
	neg = np.asarray([z for z in index if LAM[z] < 0])
	rangM = np.asarray([z for z in range(0, M+1)])
	rang = rangM[1:M]

	for n in range(0,N-1):

		if(neg.shape[0] != 0):
			#This gets the middle non-boundary mesh
			w[neg,n+1,1:M] = w[neg,n,1:M] - lam*np.multiply(LAM[neg],(w[neg,n,2:M+1] - w[neg,n,1:M])) + k*force(initial, mesh, k*(n+1), rang, neg, XI, c, rho, u0)

			# Now we use the boundary condtions
			w[neg,n+1,0] = numericalBoundNeg(bound, mesh, LAM, w[:,[n,n+1],:], neg, lam, k, n, XI, c, rho, u0)

		if(pos.shape[0] != 0):
			#This gets the middle non-boundary mesh
			w[pos,n+1,1:M] = w[pos,n,1:M] - lam*np.multiply(LAM[pos],(w[pos,n,1:M] - w[pos,n,0:M-1])) + k*force(initial, mesh, k*(n+1), rang, pos, XI, c, rho, u0)

			# Now we use the boundary condtions
			w[pos,n+1,M] = numericalBoundPos(bound, mesh, LAM, w[:,[n,n+1],:], pos, lam, k, n, XI, c, rho, u0)

		# This is for the boundary conditions
		if(neg.shape[0] == 0):
			w[pos,n+1,0] = boundConditionPos(bound[1], mesh, k*(n+1), B1, X, w[:,n+1,:], pos, c, rho, u0)
		elif(pos.shape[0] == 0):
			w[neg,n+1,M] = boundConditionNeg(bound[1], mesh, k*(n+1), B2, X, w[:,n+1,:], neg, c, rho, u0)
		else:
			w[neg,n+1,M], w[pos,n+1,0] = boundCondition(bound[1], mesh, k*(n+1), B1, B2, X, w[:,n+1,:], pos, neg, c, rho, u0)

	# This is for the final time step if it is needed with a different K
	if(final == 1):
		if(neg.shape[0] != 0):
			w[neg,N,1:M] = w[neg,N-1,1:M] - lam*np.mulitply(LAM[neg],(w[neg,N-1,2:M+1] - w[neg,N-1,1:M])) + kFin*force(initial, T, rang, neg, XI, c, rho, u0)
			w[neg,N,0] = numericalBoundNeg(bound, mesh, LAM, w[:,[N-1,N],:], neg, lam, k, N-1, XI, c, rho, u0)
		if(pos.shape[0] != 0):
			w[pos,N,1:M] = w[pos,N-1,1:M] - lam*np.multiply(LAM[pos],(w[pos,N-1,1:M] - w[pos,N-1,0:M-1])) + kFin*force(initial, T, rang, pos, XI, c, rho, u0)
			w[pos,N,M] = numericalBoundPos(bound, mesh, LAM, w[:,[N-1,N],:], pos, lam, kFin, N-1, XI, c, rho, u0)
		if(neg.shape[0] == 0):
			w[pos,N,0] = boundConditionPos(bound[1], mesh, T, B1, X, w[:,N,:], c, rho, u0)
		elif(pos.shape[0] == 0):
			w[neg,N,M] = boundConditionNeg(bound[1], mesh, T, B2, X, w[:,N,:], c, rho, u0)
		else:
			w[neg,N,M], w[pos,N,0] = boundCondition(bound[1], mesh, T, B1, B2, X, w[:,N,:], pos, neg, c, rho, u0)

	w = inverseTransform(w,X)

	return w



###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################

def laxWendroff(LAM, X, XI, T, mesh, k, initial, bound, B1, B2, c, rho, u0):
	M = mesh - 1
	h = 1/M
	lam = k/h
	lam2 = lam**2
	LAM2 = LAM**2

	# This if statement is for floating point round-off error purposes. If T/k divides perfectly (perfectly meaning equals an integer, but might not on computer),
			# then we round T/k to the integer it is with-in epsilon about and have N equal that plus 1. Hence we do not need a separate final time step.
			# If not then we floor T/k and set final=1 so that the final time step is applied after the loop. 
			# Notice N is always the amount of steps we can do with just k withouth kFin
	# The 1st dimension is system size (size of vector u), 2nd dimension is time, 3rd dimension is space
			# When you print our array each u_i will be own piece and then time is vertical, space is horizontal
	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		w = np.zeros([ X.shape[0], N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		w = np.zeros([ X.shape[0], N+1, M+1])

	# This calculates the initial condition then does w = X^(-1) f to get initial condition for w
	w[:,0,:] = np.dot(XI, initCond(initial, mesh, LAM, c, rho))

	# This makes the list of indices for positive and negative eigenvalues in LAM
	rangU = np.asarray([z for z in range(0, LAM.shape[0])])
	pos = np.asarray([z for z in rangU if LAM[z] > 0])
	neg = np.asarray([z for z in rangU if LAM[z] < 0])
	rangM = np.asarray([z for z in range(0, M+1)])
	rang = rangM[1:M]

	# This will change everytime in the loop and f0 will become f1 
	f0 = force(initial, mesh, 0, rangM, rangU, XI, c, rho, u0)
	f1 = force(initial, mesh, k, rangM, rangU, XI, c, rho, u0)

	for n in range(0,N-1):
		# This gets the middle mesh points
		# np.multiply multiplys each element of LAM by the whole the whole row vector of LAM
		w[:,n+1,rang] = w[:,n,rang] - lam*np.multiply(LAM,(w[:,n,rang+1] - w[:,n,rang-1]))/2 + lam2*np.multiply(LAM2,(w[:,n,rang+1] - 2*w[:,n,rang] + w[:,n,rang-1]))/2

		# Adds the forcing term
		w[:,n+1,rang] = w[:,n+1,rang] + k*(f1[:,rang] + f0[:,rang])/2 - k*lam*np.multiply(LAM, (f0[:,rang+1] - f0[:,rang-1]))/4
		
		# This is for the Numerical Boundary Conditions
		if(neg.shape[0] != 0):
			w[neg,n+1,0] = numericalBoundNeg(bound, mesh, LAM, w[:,[n,n+1],:], neg, lam, k, n, XI, c, rho, u0)
		if(pos.shape[0] != 0):
			w[pos,n+1,M] = numericalBoundPos(bound, mesh, LAM, w[:,[n,n+1],:], pos, lam, k, n, XI, c, rho, u0)

		# This is for the Analytic Boundary Conditions
		if(neg.shape[0] == 0):
			w[pos,n+1,0] = boundConditionPos(bound[1], mesh, k*(n+1), B1, X, w[:,n+1,:], pos, c, rho, u0)
		elif(pos.shape[0] == 0):
			w[neg,n+1,M] = boundConditionNeg(bound[1], mesh, k*(n+1), B2, X, w[:,n+1,:], neg, c, rho, u0)
		else:
			w[neg,n+1,M], w[pos,n+1,0] = boundCondition(bound[1], mesh, k*(n+1), B1, B2, X, w[:,n+1,:], pos, neg, c, rho, u0)

		f0 = f1
		f1 = force(initial, mesh, k*(n+2), rangM, rangU, XI, c, rho, u0)
		
	# This is the final time step to get to T 
	if(final == 1):
		kFin = T - (N-1)*k
		lamFin = kFin/h
		lamFin2 = lamFin**2
		w[:,N,rang] = w[:,N-1,rang] - lam*np.multiply(LAM,(w[:,N-1,rang+1] - w[:,N-1,rang-1]))/2 + lam2*np.multiply(LAM2,(w[:,N-1,rang+1] - 2*w[:,N-1,rang] + w[:,N-1,rang-1]))/2
		w[:,N,rang] = w[:,N,rang] + k*(f1[:,rang] + f0[:,rang])/2 - k*lam*np.multiply(LAM, (f0[:,rang+1] - f0[:,rang-1]))/4

		# This is for the Numerical Boundary Conditions
		if(neg.shape[0] != 0):
			w[neg,N,0] = numericalBoundNeg(bound, mesh, LAM, w[:,[N-1,N],:], neg, lam, kFin, N-1, XI, c, rho, u0)
		if(pos.shape[0] != 0):
			w[pos,N,M] = numericalBoundPos(bound, mesh, LAM, w[:,[N-1,N],:], pos, lam, kFin, N-1, XI, c, rho, u0)

		# This is for the Analytic Boundary Conditions
		if(neg.shape[0] == 0):
			w[pos,N,0] = boundConditionPos(bound[1], mesh, T, B1, X, w[:,N,:], pos, c, rho, u0)
		elif(pos.shape[0] == 0):
			w[neg,N,M] = boundConditionNeg(bound[1], mesh, T, B2, X, w[:,N,:], neg, c, rho, u0)
		else:
			w[neg,N,M], w[pos,N,0] = boundCondition(bound[1], mesh, T, B1, B2, X, w[:,N,:], pos, neg, c, rho, u0)

	w = inverseTransform(w, X)

	return w


###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################


# For full systems we would do u = X * w but for this problem we have just p = c*rho*(w1 - w2) and v = w1 - w2
def inverseTransform(w, X):
	p = X[0,0]*(w[0] - w[1])
	v = w[0] + w[1]
	vv = np.asarray([p,v])

	return vv


###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################
###########################################################################################################################################################


def main():
	# (B1[0,0] + B1[1,0])*c*rho + B1[0,1] + B1[1,1] cannot equal zero
	# (B2[0,0] + B2[1,0])*c*rho + B2[0,1] + B2[1,1] cannot equal zero
	bound = [1,6]		# The first indicy one is for numerical BC and the 2nd is for actual BC
	initial = 6			# This is for the initial condition	
	if(initial in [1,2]):
		u0 = 1
		c = 2
		rho = 1
		B1 = np.asarray([[1,2], [0,3]])
		B2 = np.asarray([[-2,1], [1,1]])
	elif(initial in [3,4,5]):
		u0 = -2
		c = 1
		rho = 1
		B1 = np.asarray([[-2,1], [1,1]])
		B2 = np.asarray([[1,0], [0,1]])
	elif(initial in [6]):
		u0 = 1
		c = 2
		rho = 1
		B1 = np.asarray([[1,0], [0,1]])
		B2 = np.asarray([[1,0], [0,1]])

	A = np.asarray([[u0, c*c*rho], [1/rho, u0]])
	LAM = np.asarray([[u0+c], [u0-c]])
	X = np.asarray([[c*rho, -1*c*rho], [1, 1]])
	XI = np.asarray([[1/(2*c*rho), 1/2], [-1/(2*c*rho), 1/2]])

	mesh = 11
	h = 1.0/(mesh-1.0)
	k = h * 0.2
	T = 5
	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		print("epsilon")
	else:
		N = int(T/k) + 1
		final = 1
		print("non-epsilon")
				
	u = exact(XI, T, mesh, k, initial, bound, B1, B2, c, rho, u0)
	vv = upWind(LAM, X, XI, T, mesh, k, initial, bound, B1, B2, c, rho, u0)
	ll = laxWendroff(LAM, X, XI, T, mesh, k, initial, bound, B1, B2, c, rho, u0)
	
	uu = np.asarray([u, vv, ll])

	# This is for the mesh
	xx = []
	for i in range(0, mesh):
		xx.append(h*i)

	fileName = [["exactP.eps", "upwindP.eps", "laxWenP.eps"], ["exactU.eps", "upwindU.eps", "laxWenU.eps"]]
	title = [["P Exact", "P Upwind", "P LaxWendroff"], ["U Exact", "U Upwind", "U LaxWendroff"]]


	t1 = int(N/100)
	t2 = int(N/33)
	t3 = int(N/10)
	t4 = int(N/3)
	t5 = int(2*N/3)
	t6 = int(5*N/6)
	# i is for u_i,  j is for upwind vs lax vs exact
	for i in range(0,2):
		for j in range(0,3):
			plt.plot(xx, uu[j][i][0], label="t=0")
			plt.plot(xx, uu[j][i][t1], label="t=" + str(k*t1))
			plt.plot(xx, uu[j][i][t2], label="t=" + str(k*t2))
			plt.plot(xx, uu[j][i][t3], label="t=" + str(k*t3))
			plt.plot(xx, uu[j][i][t4], label="t=" + str(k*t4))
			plt.plot(xx, uu[j][i][t5], label="t=" + str(k*t5))
			plt.plot(xx, uu[j][i][t6], label="t=" + str(k*t6))
			if(final==0):
				plt.plot(xx, uu[j][i][N-1], label="Final=" + str(T))
			else:
				plt.plot(xx, uu[j][i][N], label="Final=" + str(T))
			plt.legend()
			plt.title(title[i][j])
			plt.savefig(fileName[i][j], format='eps')
			plt.show()


	finalplotFile = ["finalTimeP.eps", "finalTimeU.eps"]
	finalPlotTitle = ["Pressure", "Velocity"]
	# i is for u_i
	for i in range(0,2):
		if(final==0):
			plt.plot(xx, uu[0][i][N-1], label="Exact")
			plt.plot(xx, uu[1][i][N-1], label="Upwind", linestyle="dashed", dashes=(2,3))
			plt.plot(xx, uu[2][i][N-1], label="Lax-Wendroff", color="red", linestyle="dashed", dashes=(5,7))
		else:
			plt.plot(xx, uu[0][i][N], label="Exact")
			plt.plot(xx, uu[1][i][N], label="Upwind")
			plt.plot(xx, uu[2][i][N], label="Lax-Wendroff", linestyle="dashed")
		plt.legend()
		plt.title("Final T=" + str(T) + " for " + finalPlotTitle[i])
		plt.savefig(finalplotFile[i], format='eps')
		plt.show()




main()
	
