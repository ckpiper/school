# This is Project 2 for Numerical Solutions for Partial Differential Equations
import math
import matplotlib.pyplot as plt
import numpy as np

pi = math.pi

def initCond(x):

	################## Init 1 ###################
	x = math.sin(2*pi*x)

	################## Init 2 ###################
	# if x >= 0.25 and x <=0.75:
	# 	x = 1
	# else:
	# 	x = 0

	################## Init 3 ###################

	return x


def bndCond(t):

	# ################## Bound 1 ###################
	t = math.sin(-2*pi*t)

	################## Bound 2 ###################
	# if t >= 0.25 and t <=0.75:
	# 	t = 1
	# else:
	# 	t = 0

	# t = 0 

	return t


def exact(M, T, a, h, k, N, kFin, lamb, lambFin):
	u= np.zeros((N+1, M+1))

	# Initial Value
	for m in range(0, M+1):
		u[0][m] = initCond(m*h)

	# This is for all the middle time steps
	for n in range(1,N):
		for m in range(0, M+1):
			if (m*h - a*n*k < 0):
				u[n][m] = bndCond(n*k - m*h/a)
			else:
				u[n][m] = initCond(m*h - a*n*k)

	# This for the final time step 
	for m in range(0,M+1):
		if (m*h - a*T < 0):
			u[N][m] = bndCond(T - m*h/a)
		else:
			u[N][m] = initCond(m*h - a*T)

	return u


def implicitUpwind(M, T, a, h, k, N, kFin, lamb, lambFin):
	impSoln = np.zeros((N+1, M+1))

	# Iniitial Value
	for m in range(0, M+1):
		impSoln[0][m] = initCond(m*h)

	# This is for all the middle time steps
	for n in range(1, N):
		impSoln[n][0] = bndCond(k*n)
		for m in range(1, M+1):
			impSoln[n][m] = (impSoln[n-1][m] + a*lamb*impSoln[n][m-1])/(1+a*lamb)

	# This is for the last time step
	impSoln[N][0] = bndCond(T)
	for m in range(1, M+1):
		impSoln[N][m] = (impSoln[N-1][m] + a*lambFin*impSoln[N][m-1])/(1+a*lambFin)

	return impSoln


def explicitUpwind(M, T, a, h, k, N, kFin, lamb, lambFin):
	expSoln = np.zeros((N+1, M+1))

	# Initial Value
	for m in range(0, M+1):
		expSoln[0][m] = initCond(m*h)

	# This is for all the middle time steps
	for n in range(1, N):
		expSoln[n][0] = bndCond(k*n)
		for m in range(1,M+1):
			expSoln[n][m] = (1-a*lamb)*expSoln[n-1][m] + a*lamb*expSoln[n-1][m-1]

	# This is for the last time step
	expSoln[N][0] = bndCond(T)
	for m in range(1,M+1):
		expSoln[N][m] = (1-a*lambFin)*expSoln[N-1][m] + a*lambFin*expSoln[N-1][m-1]

	return expSoln


mesh = 32
M = mesh - 1
T = 1.5
a = 1
h = 1/M
k = h/a *0.8		# alam < 1 ak <h
N = int(T/k)
kFin = T - N*k
lamb = k/h
lambFin = kFin/h

uu = exact(M, T, a, h, k, N, kFin, lamb, lambFin)
impSoln = implicitUpwind(M, T, a, h, k, N, kFin, lamb, lambFin)
expSoln = explicitUpwind(M, T, a, h, k, N, kFin, lamb, lambFin)

M2 = 2*M
h2 = 1/M2
lamb2 = k/h2
lambFin2 = kFin/h2

impSoln2 = implicitUpwind(M2, T, a, h2, k, N, kFin, lamb2, lambFin2)
expSoln2 = explicitUpwind(M2, T, a, h2, k, N, kFin, lamb2, lambFin2)



# This is for the mesh
xx = []
for i in range(0, M+1):
	xx.append(h*i)

xx2 = []
for i in range(0, M2+1):
	xx2.append(h2*i)

xxx = [xx, xx2]

title = [["Exact Solution Step", "Upwind Implicit Method Step", "Upwind Explicit Method Step", "Upwind Implicit Method Step Half", "Upwind Explicit Method Step Half"], ["Exact Solution Sine", "Upwind Implicit Method Sine", "Upwind Explicit Method Sine", "Upwind Implicit Method Sine Half", "Upwind Explicit Method Sine Half"]]
fileName = [["exactSolnStep.eps", "UpwindImpSolnStep.eps", "UpwindExpSolnStep.eps", "UpwindImpSolnStepHalf.eps", "UpwindExpSolnStepHalf.eps"], ["exactSolnSine.eps", "UpwindImpSolnSine.eps", "UpwindExpSolnSine.eps", "UpwindImpSolnSineHalf.eps", "UpwindExpSolnSineHalf.eps"]]
u = [uu, impSoln, expSoln, impSoln2, expSoln2]


t1 = int(N/100)
t2 = int(N/50)
t3 = int(N/10)
t4 = int(N/3)
t5 = int(2*N/3)
for i in range(0,3):
	if (i < 3):
		j = 0
	else:
		j = 1
	plt.plot(xxx[j], u[i][0], label="t=0")
	plt.plot(xxx[j], u[i][t1], label="t=" + str(k*t1))
	plt.plot(xxx[j], u[i][t2], label="t=" + str(k*t2))
	plt.plot(xxx[j], u[i][t3], label="t=" + str(k*t3))
	plt.plot(xxx[j], u[i][t4], label="t=" + str(k*t4))
	plt.plot(xxx[j], u[i][t5], label="t=" + str(k*t5))
	plt.plot(xxx[j], u[i][N], label="Final=" + str(T))
	plt.legend()
	plt.title(title[1][i])
	plt.savefig(fileName[1][i], format='eps')
	plt.show()



###################### Errors ############################
T = 1.5
a = 1
mesh = 16
errLogImp = []
errLogExp = []
meshSize = []

count = 0
for m in range(0,8):
	print(count)
	meshSize.append(mesh)
	M = mesh - 1
	h = 1/M
	k = h/a * 0.8
	N = int(T/k)
	kFin = T - N*k
	lamb = k/h
	lambFin = kFin/h

	uu = exact(M, T, a, h, k, N, kFin, lamb, lambFin)
	impSoln = implicitUpwind(M, T, a, h, k, N, kFin, lamb, lambFin)
	expSoln = explicitUpwind(M, T, a, h, k, N, kFin, lamb, lambFin)

	imp = math.sqrt(h*np.sum(np.square(impSoln[t4] - uu[t4])))
	exp = math.sqrt(h*np.sum(np.square(impSoln[t4] - uu[t4])))
	errLogImp.append(imp)
	errLogExp.append(exp)

	# errLogImp.append(np.linalg.norm(impSoln[t4] - uu[t4]))
	# errLogExp.append(np.linalg.norm(expSoln[t4] - uu[t4]))
	mesh = mesh*2
	count = count + 1

errLogImp = np.log2(errLogImp)
errLogExp = np.log2(errLogExp)
meshSize = np.log2(meshSize)

errTitle = [["Implicit Error Step", "Expicit Error Step"], ["Implicit Error Sine", "Explicit Error Sine"]]
errFile = [["impErrStep.eps", "expErrStep.eps"], ["impErrSine.eps", "expErrSine.eps"]]
err = [errLogImp, errLogExp]

for i in range(0,2):
	plt.plot(meshSize, err[i])
	plt.title(errTitle[1][i])
	plt.xlabel("Log2 of Mesh")
	plt.ylabel("Log2 of L2-Norm of the Errors")
	plt.savefig(errFile[1][i], format='eps')
	plt.show()
