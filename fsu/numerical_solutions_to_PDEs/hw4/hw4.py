	# This is Project 4 for Numerical Solutions for Partial Differential Equations
import math
import matplotlib.pyplot as plt
import numpy as np

pi = math.pi

def initialMod(example, rangM, t, a):
	mesh = rangM.shape[0]
	M = mesh-1 
	h = 1/M
	x = rangM*h
	x = (x-a*t)%1

	if (example == 1):
		y = np.logical_and(x>=0.25, x<=0.75)
		x[y] = 1
		y = np.logical_not(y)
		x[y] = 0
	elif(example == 2):
		x = np.sin(2*pi*x)
	elif(example == 3):
		x = 0.5 - np.absolute(x - 0.5)
	# elif(exmaple == 4):
	# 	# THis is holder for another example
	# elif(exmaple == 5):
	# 	# THis is holder for another example
	# elif(exmaple == 6):
	# 	# THis is holder for another example

	return x



def exact(speed, k, mesh, example, T):
	M = mesh - 1
	h  = 1/M
	if(T == 0):
		N = 1
		final = 0
		u = np.zeros([1,M+1])
	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		u = np.zeros([N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		u = np.zeros([N+1, M+1])

	rangM = np.asarray([z for z in range(0, M+1)])

	for n in range(0, N):
		u[n] = initialMod(example, rangM, n*k, speed)

	if(final == 1):
		u[N] = initialMod(example, rangM, T, speed)

	return u





##############################################################################################
##############################################################################################
##############################################################################################
##############################################################################################

# This is for solving the almost tridiagonal solver
def nearTriMatrix(a, b, c, d0, e0, s):
	n = b.shape[0]-1
	d = np.zeros([n+1])
	d[0] = d0

	##### Forward Sweep #####

	# Rows 1 to n-2
	for i in range(1,n-1):
		b[i] = b[i] - a[i-1]*c[i-1]/b[i-1]
		s[i] = s[i] - a[i-1]*s[i-1]/b[i-1]
		d[i] = -1*a[i-1]*d[i-1]/b[i-1]

	# Row n-1
	b[n-1] = b[n-1] - a[n-2]*c[n-2]/b[n-2]
	s[n-1] = s[n-1] - a[n-2]*s[n-2]/b[n-2]
	c[n-1] = c[n-1] - a[n-2]*d[n-2]/b[n-2]
	
	# Row n
	b[n] = b[n] - a[n-1]*c[n-1]/b[n-1]
	s[n] = s[n] - a[n-1]*s[n-1]/b[n-1]

	##### Backward Sweep #####

	# Row n-1
	s[n-1] = s[n-1] - c[n-1]*s[n]/b[n]
	c[n-1] = c[n-1]*e0/b[n]

	# Row n-2 to 1
	for i in range(n-2,0,-1):
		s[i] = s[i] - c[i]*s[i+1]/b[i+1] - d[i]*s[n]/b[n]
		c[i] = d[i]*e0/b[n] - c[i]*c[i+1]/b[i+1]

	x = np.zeros([s.shape[0]])

	# Row 0
	x[0] = (s[0] - c[0]*s[1]/b[1] - d[0]*s[n]/b[n]) / (b[0] - d[0]*e0/b[n] + c[0]*c[1]/b[1])

	##### Forward Sweep Again #####

	for i in range(1, n):
		x[i] = (s[i] + c[i]*x[0]) / b[i]

	x[n] = (s[n] - e0*x[0]) / b[n]

	return x


##############################################################################################
##############################################################################################
##############################################################################################
##############################################################################################


def modLeapFrog(speed, k, eps, mesh, example, T):
	M = mesh - 1
	h  = 1/M
	a = np.zeros([M-1])
	b = np.zeros([M])
	c = np.zeros([M-1])

	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		w = np.zeros([N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		w = np.zeros([N+1, M+1])

	rangM = np.asarray([z for z in range(2, M-1)])

	# First step of this method needs to be something that is one 
	a[:] = -1*speed*k/(4*h)
	b[:] = 1
	c[:] = speed*k/(4*h)
	s = np.zeros([M])

	rangMf = np.asarray([z for z in range(0, M)])
	w[0] = exact(speed, k, mesh, example, 0)

	s[0] = w[0, 0] + a[0] * (w[0, 1] - w[0, M-1]) - eps*(w[0,2] - 4*w[0,1] + 6*w[0,0] - 4*w[0,M-1] + w[0,M-2])/16
	s[1] = w[0, 1] + a[0] * (w[0, 2] - w[0, 0]) - eps*(w[0,3] - 4*w[0,2] + 6*w[0,1] - 4*w[0,0] + w[0,M-1])/16
	s[M-1] = w[0, M-1] + a[0] * (w[0,0] - w[0,M-2]) - eps*(w[0,1] - 4*w[0,0] + 6*w[0,M-1] - 4*w[0,M-2] + w[0,M-3])/16
	s[rangM] = w[0, rangM] + a[0] * (w[0, rangM+1] - w[0, rangM-1]) - eps*(w[0,rangM+2] - 4*w[0,rangM+1] + 6*w[0,rangM] - 4*w[0,rangM-1] + w[0,rangM-2])/16

	# We only have an MxM matrix as we do not use the last w[n, M] because w[n+1, M] equation is the same as w[n+1,0] equation
	W = np.zeros([M,M])
	for i in range(0, M):
		W[i][i] = 1
	for i in range(0, M-1):
		W[i+1][i] = a[0]
	for i in range(0, M-1):
		W[i][i+1] = c[0]
	W[0][M-1] = W[1][0]
	W[M-1][0] = W[0][1]

	w[1, rangMf] = np.linalg.solve(W, s)
	w[1, M] = w[1, 0]

	# THis is the actual modified leap frog
	const = -1*speed*k/h
	for n in range(1,N-1):
		w[n+1, 0] = w[n-1, 0] + const*(w[n, 1] - w[n, M-1]) - eps*(w[n-1,2] - 4*w[n-1,1] + 6*w[n-1,0] - 4*w[n-1,M-1] + w[n-1,M-2])/16
		w[n+1, 1] = w[n-1, 1] + const*(w[n, 2] - w[n, 0]) - eps*(w[n-1,3] - 4*w[n-1,2] + 6*w[n-1,1] - 4*w[n-1,0] + w[n-1,M-1])/16
		w[n+1, M-1] = w[n-1, M-1] + const*(w[n, 0] - w[n, M-2])  - eps*(w[n-1,1] - 4*w[n-1,0] + 6*w[n-1,M-1] - 4*w[n-1,M-2] + w[n-1,M-3])/16
		w[n+1, M] = w[n+1, 0]
		w[n+1, rangM] = w[n-1, rangM] + const*(w[n, rangM+1] - w[n, rangM-1]) - eps*(w[n-1,rangM+2] - 4*w[n-1,rangM+1] + 6*w[n-1,rangM] - 4*w[n-1,rangM-1] + w[n-1,rangM-2])/16

	if(final == 1):
		kFin = T - (N-1)*k
		const = -1*speed*kFin/h
		w[N, 0] = w[N-2, 0] + const*(w[N-1, 1] - w[N-1, M-1]) - eps*(w[N-2,2] - 4*w[N-2,1] + 6*w[N-2,0] - 4*w[N-2,M-1] + w[N-2,M-2])/16
		w[N, 1] = w[N-2, 1] + const*(w[N-1, 2] - w[N-1, 0]) - eps*(w[N-2,3] - 4*w[N-2,2] + 6*w[N-2,1] - 4*w[N-2,0] + w[N-2,M-1])/16
		w[N, M-1] = w[N-2, M-1] + const*(w[N-1, 0] - w[N-1, M-2]) - eps*(w[N-2,1] - 4*w[N-2,0] + 6*w[N-2,M-1] - 4*w[N-2,M-2] + w[N-2,M-3])/16
		w[N, M] = w[N, 0]
		w[N, rangM] = w[N-2, rangM] + const*(w[N-1, rangM+1] - w[N-1, rangM-1]) - eps*(w[N-2,rangM+2] - 4*w[N-2,rangM+1] + 6*w[N-2,rangM] - 4*w[N-2,rangM-1] + w[N-2,rangM-2])/16

	return w


##############################################################################################
##############################################################################################
##############################################################################################
##############################################################################################

# For this we need a matrix solver to actually compute the next iteration
# Thus using the boundary conditions we just ignore the existance of v_M and whenever we need it replace it with v_0
# This is the reason we most of our arrays like s is of length M and not M+1 as we do not need that extra element
def modCrankNic(speed, k, eps, mesh, example, T):
	M = mesh - 1
	h  = 1/M
	a = np.zeros([M-1])
	b = np.zeros([M-1])
	c = np.zeros([M-1])

	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		w = np.zeros([N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		w = np.zeros([N+1, M+1])

	a[:] = -1*speed*k/(4*h)
	b[:] = 1
	c[:] = speed*k/(4*h)
	s = np.zeros([M])
	rangMs = np.asarray([z for z in range(2, M-1)])
	rangM = np.asarray([z for z in range(0, M)])

	w[0] = exact(speed, k, mesh, example, 0)

	for n in range(0,N-1):

		s[0] = w[n, 0] + a[0] * (w[n, 1] - w[n, M-1]) - eps*(w[n,2] - 4*w[n,1] + 6*w[n,0] - 4*w[n,M-1] + w[n,M-2])/16
		s[1] = w[n, 1] + a[0] * (w[n, 2] - w[n, 0]) - eps*(w[n,3] - 4*w[n,2] + 6*w[n,1] - 4*w[n,0] + w[n,M-1])/16
		s[M-1] = w[n, M-1] + a[0] * (w[n, 0] - w[n, M-2]) - eps*(w[n,1] - 4*w[n,0] + 6*w[n,M-1] - 4*w[n,M-2] + w[n,M-3])/16
		# s[M-2] = w[n, M-2] + a[0] * (w[n, M-1] - w[n, M-3]) - eps*(w[n,0] - 4*w[n,M-1] + 6*w[n,M-2] - 4*w[n,M-3] + w[n,M-4])/16
		s[rangMs] = w[n, rangMs] + a[0] * (w[n, rangMs+1] - w[n, rangMs-1]) - eps*(w[n,rangMs+2] - 4*w[n,rangMs+1] + 6*w[n,rangMs] - 4*w[n,rangMs-1] + w[n,rangMs-2])/16

		# We only have an MxM matrix as we do not use the last w[n, M] because w[n+1, M] equation is the same as w[n+1,0] equation
		W = np.zeros([M,M])
		for i in range(0, M):
			W[i][i] = 1
		for i in range(0, M-1):
			W[i+1][i] = a[0]
		for i in range(0, M-1):
			W[i][i+1] = c[0]
		W[0][M-1] = W[1][0]
		W[M-1][0] = W[0][1]

		w[n+1, rangM] = np.linalg.solve(W, s)
		w[n+1, M] = w[n+1, 0]


	if(final == 1):
		kFin = T - (N-1)*k
		const = -1*speed*kFin/(4*h)
		s[0] = w[N-1, 0] + const * (w[N-1, 1] - w[N-1, M-1]) - eps*(w[N-1,2] - 4*w[N-1,1] + 6*w[N-1,0] - 4*w[N-1,M-1] + w[N-1,M-2])/16
		s[1] = w[N-1, 1] + const * (w[N-1, 2] - w[N-1, 0]) - eps*(w[N-1,3] - 4*w[N-1,2] + 6*w[N-1,1] - 4*w[N-1,0] + w[N-1,M-1])/16
		s[M-1] = w[N-1, M-1] + const * (w[N-1, 0] - w[N-1, M-2]) - eps*(w[N-1,1] - 4*w[N-1,0] + 6*w[N-1,M-1] - 4*w[N-1,M-2] + w[N-1,M-3])/16
		s[rangMs] = w[N-1, rangMs] + const * (w[N-1, rangMs+1] - w[N-1, rangMs-1]) - eps*(w[N-1,rangMs+2] - 4*w[N-1,rangMs+1] + 6*w[N-1,rangMs] - 4*w[N-1,rangMs-1] + w[N-1,rangMs-2])/16

		W = np.zeros([M,M])
		for i in range(0, M):
			W[i][i] = 1
		for i in range(0, M-1):
			W[i+1][i] = -1*const
		for i in range(0, M-1):
			W[i][i+1] = const
		W[0][M-1] = W[1][0]
		W[M-1][0] = W[0][1]

		w[N, rangM] = np.linalg.solve(W, s)
		w[N, M] = w[N, 0]

	return w


##############################################################################################
##############################################################################################
##############################################################################################
##############################################################################################


def main():
	# m = 7
	# M = np.zeros([m,m])
	# a = np.zeros([m])
	# b = np.zeros([m])
	# c = np.zeros([m])

	# a[:] = -1
	# b[:] = 5
	# c[:] = 1

	# s = np.random.randint(3, size=m)
	# s = np.asarray([2.0,3.0,1.0,-5.0,-1.0,3.0,2.0])
	# for i in range(0, m):
	# 	M[i][i] = 5
	# for i in range(0, m-1):
	# 	M[i+1][i] = -1
	# for i in range(0, m-1):
	# 	M[i][i+1] = 1
	# M[0][m-1] = M[1][0]
	# M[m-1][0] = M[0][1]

	# print(np.linalg.solve(M, s))

	# print(nearTriMatrix(a[1:m], b, c[0:m-1], a[0], c[m-1], s))
	example = 3
	speed = 1
	mesh = 129
	h = 1.0/(mesh-1.0)
	k = h/speed * 0.1
	T = 5
	eps = 0.8

	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		print("epsilon")
	else:
		N = int(T/k) + 1
		final = 1
		print("non-epsilon")

	u = exact(speed, k, mesh, example, T)
	lF = modLeapFrog(speed, k, eps, mesh, example, T)
	cN = modCrankNic(speed, k, eps, mesh, example, T)
	
	uu = np.asarray([u,lF,cN])

	# This is for the mesh
	xx = []
	for i in range(0, mesh):
		xx.append(h*i)

	fileName = ["exact.eps", "modLeapFrog.eps", "modCrankNic.eps", "finalTimePlot.eps"]
	title = ["Exact", "Modified Leap Frog", "Modified Crank-Nicolson"]


	t1 = int(N/100)
	t2 = int(N/33)
	t3 = int(N/10)
	t4 = int(N/3)
	t5 = int(2*N/3)
	t6 = int(5*N/6)

	# i is for u_i,  j is for upwind vs lax vs exact
	for j in range(0,3):
		plt.plot(xx, uu[j][0], label="t=0")
		plt.plot(xx, uu[j][t1], label="t=" + str(k*t1))
		plt.plot(xx, uu[j][t2], label="t=" + str(k*t2))
		plt.plot(xx, uu[j][t3], label="t=" + str(k*t3))
		# plt.plot(xx, uu[j][t4], label="t=" + str(k*t4))
		# plt.plot(xx, uu[j][t5], label="t=" + str(k*t5))
		# plt.plot(xx, uu[j][t6], label="t=" + str(k*t6))
		# if(final==0):
		# 	plt.plot(xx, uu[j][N-1], label="Final=" + str(T))
		# else:
		# 	plt.plot(xx, uu[j][N], label="Final=" + str(T))
		plt.legend()
		plt.title(title[j])
		# plt.savefig(fileName[j], format='eps')
		plt.show()

	# i is for u_i
	if(final==0):
		plt.plot(xx, uu[0][N-1], label="Exact")
		plt.plot(xx, uu[1][N-1], label="Leap", linestyle="dashed", dashes=(2,3))
		plt.plot(xx, uu[2][N-1], label="Crank-Nic", linestyle="dashed", dashes=(5,7))
	else:
		plt.plot(xx, uu[0][i][N], label="Exact")
		plt.plot(xx, uu[1][i][N], label="Leap", linestyle="dashed", dashes=(2,3))
		plt.plot(xx, uu[2][i][N], label="Crank-Nic", linestyle="dashed", dashes=(5,7))
	plt.legend()
	plt.title("Final T=" + str(T))
	plt.savefig(fileName[3], format='eps')
	plt.show()


	# mesh = 16
	# errLoglF = []
	# errLogcN = []
	# meshSize = []
	# count=0
	# for m in range(0,5):
	# 	print(count)
	# 	meshSize.append(mesh)
	# 	M = mesh - 1
	# 	h = 1/M
	# 	k = h/speed * 0.8
	# 	N = int(T/k)
	# 	kFin = T - N*k
	# 	lamb = k/h

	# 	u = exact(speed, k, mesh, example, T)
	# 	lF = modLeapFrog(speed, k, eps, mesh, example, T)
	# 	cN = modCrankNic(speed, k, eps, mesh, example, T)

	# 	lFNorm = math.sqrt(np.sum(h*np.square(lF[N-1] - u[N-1])))
	# 	cNNorm = math.sqrt(np.sum(h*np.square(cN[N-1] - u[N-1])))
	# 	errLoglF.append(lFNorm)
	# 	errLogcN.append(cNNorm)

	# 	mesh = mesh*2
	# 	count = count + 1

	# errLoglF = np.log2(errLoglF)
	# errLogcN = np.log2(errLogcN)
	# meshSize = np.log2(meshSize)

	# errTitle = [["Leap Error Step", "Crank-Nic Error Step"], ["Leap Error Sine", "Crank-Nic Error Sine"]]
	# errFile = [["leapErrStep.eps", "crankErrStep.eps"], ["leapErrSine.eps", "crankErrSine.eps"]]
	# err = [errLoglF, errLogcN]

	# for i in range(0,2):
	# 	plt.plot(meshSize, err[i])
	# 	plt.title(errTitle[1][i])
	# 	plt.xlabel("Log2 of Mesh")
	# 	plt.ylabel("Log2 of L2-Norm of the Errors")
	# 	# plt.savefig(errFile[1][i], format='eps')
	# 	plt.show()



main()
