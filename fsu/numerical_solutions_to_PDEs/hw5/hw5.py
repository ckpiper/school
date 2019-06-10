	# This is Project 5 for Numerical Solutions for Partial Differential Equations
import math
import matplotlib.pyplot as plt
import numpy as np

pi = math.pi

def exact(a, b, k, mesh, example, T):
	M = mesh - 1
	h = 1/M
	lam = k/h
	mu = k/(h*h)
	rang = np.asarray([z for z in range(0,M+1)])

	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		u = np.zeros([N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		u = np.zeros([N+1, M+1])

	if (example==1):							# Quadratic
		for n in range(0, N):
			u[n,:] =  (rang/M)**2 + k*n
		if(final==1):
			u[N,:] = (rang/M)**2 + T
	elif (example==2):
		for n in range(0, N):					# Linear
			u[n,:] =  (rang/M) + k*n
		if(final==1):
			u[N,:] = (rang/M) + T
	elif (example==3):
		for n in range(0, N):					# Linear
			u[n,:] =  (rang/M) - (a-1)*k*n
		if(final==1):
			u[N,:] = (rang/M) - (a-1)*T
	elif (example==4):
		for n in range(0, N):					# Linear
			u[n,:] =  (rang/M) - a*k*n
		if(final==1):
			u[N,:] = (rang/M) - a*T
	elif (example==5):
		for n in range(0, N):					# Sine Time Dependent
			u[n,:] =  np.sin(rang/M+k*n)
		if(final==1):
			u[N,:] = np.sin(rang/M+T)
	elif (example==6):
		for n in range(0, N):					# Sine Time Independent
			u[n,:] =  np.sin(2*pi*rang/M)
		if(final==1):
			u[N,:] = np.sin(2*pi*rang/M)
	elif (example==7):
		for n in range(0, N):					# Exponential
			u[n,:] =  np.exp(-1*(rang/M-n*k))
		if(final==1):
			u[N,:] = np.exp(-1*(rang/M-T))
	return u

############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################

def initial(a, mesh, example):
	M = mesh - 1
	rang = np.asarray([z for z in range(0,M+1)])

	if(example==1):
		u = (rang/M)**2	
	elif(example==2):
		u = (rang/M)
	elif(example==3):
		u = (rang/M)
	elif(example==4):
		u = (rang/M)
	elif(example==5):
		u = np.sin(rang/M)
	elif(example==6):
		u = np.sin(2*pi*rang/M)
	elif(example==7):
		u = np.exp(-1*(rang/M))

	return u

############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################

def bound1(a, b, t, example):
	if(example==1):
		u = t	
	elif(example==2):
		u = t 
	elif(example==3):
		u = (1-a)*t
	elif(example==4):
		u = a*t
	elif(example==5):
		u = np.sin(t)
	elif(example==6):
		u = 0
	elif(example==7):
		u = np.exp(t)

	return u

############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################

def bound2(a, b, t, example):
	if(example==1):
		u = t + 1
	elif(example==2):
		u = t + 1
	elif(example==3):
		u = 1 + (1-a)*t
	elif(example==4):
		u = 1 - a*t
	elif(example==5):
		u = np.sin(1+t)
	elif(example==6):
		u = 0
	elif(example==7):
		u = np.exp(t - 1)

	return u

############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################

def force(a, b, t, mesh, example):
	M = mesh - 1
	rang = np.asarray([z for z in range(1,M)])
	u = np.zeros([mesh-2])

	if(example==1):
		u = 2*a*rang/M - 2*b + 1
	elif(example==2):
		u = a*rang/M + 1
	elif(example==3):
		u[:] = 1
	elif(example==4):
		u[:] = 0
	elif(example==5):
		u[:] = (1+a)*np.cos(rang/M+t) + b*np.sin(rang/M+t)
	elif(example==6):
		u[:] = 2*pi*a*np.cos(2*pi*rang/M) + 4*pi*pi*b*np.sin(2*pi*rang/M)
	elif(example==7):
		u[:] = (1-a-b)*np.exp(t-rang/M)

	return u


############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################


def strange(a, b, k, mesh, example, T):
	M = mesh - 1
	h = 1/M
	lam = k/h
	mu = k/(h*h)
	rang = np.asarray([z for z in range(0,M+1)])

	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		v = np.zeros([N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		v = np.zeros([N+1, M+1])

	v[0] = initial(a, mesh, example)
	for n in range(0,N-1):
		temp = np.zeros([M+1])	
			
		#### The next few lines are for stage 1 (Advection Bacwards Time Backward Space, thus easy bacwards substitution solve)
		v[n+1,0] = bound1(a, b, k*(n+0.5), example)
		for m in rang[1:]:
			v[n+1, m] = 1/(1+a*lam/2) * ( v[n,m] + a*lam*v[n+1, m-1]/2 )

		#### The next few lines are for stage 2 (Diffusion Forward Time Center Space, thus explicit solve)
		# temp[0] = v[n+1,0]
		# temp[1:M] = v[n+1,1:M] + b*mu*( v[n+1,2:M+1] - 2*v[n+1, 1:M] + v[n+1, 0:M-1] ) / 2 + k*force(a, b, k*n, mesh, example)/2
		# temp[M] = bound2(a, b, k*(n+0.5), example)
		v[n+1,1:M] = v[n+1,1:M] + b*mu*( v[n+1,2:M+1] - 2*v[n+1, 1:M] + v[n+1, 0:M-1] ) / 2 + k*force(a, b, k*(n+0.5), mesh, example)/2
		v[n+1, M] = bound2(a, b, k*(n+0.5), example)	# No need for v[n+1, 0] as it will be the same as above

		#### The next few lines are for stage 3 (Diffusion Forward Time Center Space, thus explicit solve)
		# v[n+1,1:M] = temp[1:M] + b*mu*( temp[2:M+1] - 2*temp[1:M] + temp[0:M-1] ) / 2 + k*force(a, b, k*(n+0.5), mesh, example)/2
		# v[n+1, M] = temp[M]
		v[n+1,1:M] = v[n+1,1:M] + b*mu*( v[n+1,2:M+1] - 2*v[n+1, 1:M] + v[n+1, 0:M-1] ) / 2 + k*force(a, b, k*(n+1), mesh, example)/2
		v[n+1,0] = bound1(a, b, k*(n+1), example)
		v[n+1, M] = bound2(a, b, k*(n+1), example)

		#### The next few lines are for stage 4 (Advection Backwards Time Bacward Space, thus easy bacwards substitution solve)
		for m in rang[1:]:
			v[n+1, m] = 1/(1+a*lam/2) * ( v[n,m] + a*lam*v[n+1, m-1]/2 )
			# temp[m] = 1/(1+a*lam/2) * ( v[n,m] + a*lam*v[n+1, m-1]/2 )

		# v[n+1] = np.copy(temp)

	if(final == 1):
		kFin = T - (N-1)*k
		lam = kFin/h
		mu = kFin/(h*h)
		#### The next few lines are for stage 1 (Advection Bacwards Time Backward Space, thus easy bacwards substitution solve)
		v[N,0] = bound1(a, b, T - kFin/2, example)
		for m in rang[1:]:
			v[N, m] = 1/(1+a*lam/2) * ( v[N-1,m] + a*lam*v[N, m-1]/2 )

		#### The next few lines are for stage 2 (Diffusion Forward Time Center Space, thus explicit solve)
		v[N,1:M] = v[N,1:M] + b*mu*( v[N,2:M+1] - 2*v[N, 1:M] + v[N, 0:M-1] ) / 2 + kFin*force(a, b, k*(N-1), mesh, example)/2
		v[N, M] = bound2(a, b, T - kFin/2, example)		# No need for v[n+1, 0] as it will be the same as above

		#### The next few lines are for stage 3 (Diffusion Forward Time Center Space, thus explicit solve)
		v[N,1:M] = v[N,1:M] + b*mu*( v[N,2:M+1] - 2*v[N, 1:M] + v[N, 0:M-1] ) / 2 + kFin*force(a, b, T - kFin/2, mesh, example)/2
		v[N, 0] = bound1(a, b, T, example)
		v[N, M] = bound2(a, b, T, example)

		#### The next few lines are for stage 4 (Advection Backwards Time Bacward Space, thus easy bacwards substitution solve)
		for m in rang[1:]:
			v[N, m] = 1/(1+a*lam/2) * ( v[N,m] + a*lam*v[N, m-1]/2 )

	return v


############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################

def thomasAlg(a,b,c,d):
	M = b.shape[0] - 1
	w = np.zeros([a.shape[0]])
	x = np.zeros([M+1])

	for i in range(1,M+1):
		b[i] = b[i] - a[i-1]*c[i-1]/b[i-1]
		d[i] = d[i] - a[i-1]*d[i-1]/b[i-1]

	x[M] = d[M]/b[M]
	for i in range(M-1, -1, -1):
		x[i] = (d[i] - c[i]*x[i+1])/b[i]

	return x

############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################

def peacemanRachford(a, b ,k ,mesh , example, T):
	M = mesh - 1
	h = 1/M
	lam = k/h
	mu = k/(h*h)
	rang = np.asarray([z for z in range(0,M+1)])

	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		v = np.zeros([N, M+1])
	else:
		N = int(T/k) + 1
		final = 1
		v = np.zeros([N+1, M+1])

	v[0] = initial(a, mesh, example)

	for n in range(0,N-1):
		#### The next few lines are for stage 1 (Diffusion Forward Time Center Space, thus explicit solve)
		v[n+1,1:M] = v[n,1:M] + b*mu*( v[n,2:M+1] - 2*v[n, 1:M] + v[n, 0:M-1] ) / 2 + k*force(a, b, k*n, mesh, example)/2
		v[n+1, 0] = bound1(a, b, k*(n+0.5), example)
		v[n+1, M] = bound2(a, b, k*(n+0.5), example)

		#### The next few lines are for stage 2 (Advection Backward Time Backward Space, thus easy bacwards substitution solve)
		for m in rang[1:]:
			v[n+1, m] = 1/(1+a*lam/2) * ( v[n,m] + a*lam*v[n+1, m-1]/2 )

		#### The next few lines are for stage 3 (Advection Forward Time Bacward Space, thus explicit solve)
		v[n+1, 1:M+1] = v[n+1, 1:M+1] - a*lam*(v[n+1, 1:M+1] - v[n+1, 0:M])/2
		v[n+1, 0] = bound1(a, b, k*(n+1), example)

		#### The next few lines are for stage 4 (Diffusion Backward Time Center Space, thus implicit tridiagonal linear system)
		v[n+1, M] = bound2(a, b, k*(n+1), example)					# No need for v[n+1, 0] as it will be the same as above
		d = v[n+1,1:M] + k*force(a, b, k*(n+1), mesh, example)/2
		d[0] = d[0] + b*mu*v[n+1,0]/2
		d[M-2] = d[M-2] + b*mu*v[n+1,M]/2
		# c = np.asarray([-b*mu/2 for z in range(0,M-2)])
		# f = np.asarray([1+b*mu for z in range(0,M-1)])			# These are for my failed attempt at thomas algorithm
		# v[n+1, 1:M] = thomasAlg(c, f, c, d)
		W = np.zeros([M-1, M-1])
		for i in range(0,M-1):
			W[i][i] = 1 + b*mu
		for i in range(0,M-2):
			W[i+1][i] = -1*b*mu/2
			W[i][i+1] = W[i+1][i]

		v[n+1, 1:M] = np.linalg.solve(W,d)

	if(final == 1):
		kFin = T - (N-1)*k
		lam = kFin/h
		mu = kFin/(h*h)
		#### The next few lines are for stage 1 (Diffusion Forward Time Center Space, thus explicit solve)
		v[N,1:M] = v[N,1:M] + b*mu*( v[N-1,2:M+1] - 2*v[N-1, 1:M] + v[N-1, 0:M-1] ) / 2 + kFin*force(a, b, k*(N-1), mesh, example)/2
		v[N, 0] = bound1(a, b, T-kFin/2, example)
		v[N, M] = bound2(a, b, T-kFin/2, example)

		#### The next few lines are for stage 2 (Advection Backward Time Backward Space, thus easy bacwards substitution solve)
		for m in rang[1:]:
			v[N, m] = 1/(1+a*lam/2) * ( v[N-1,m] + a*lam*v[N, m-1]/2 )

		#### The next few lines are for stage 3 (Advection Forward Time Bacward Space, thus explicit solve)
		v[N, 1:M+1] = v[N, 1:M+1] - a*lam*(v[N, 1:M+1] - v[N, 0:M])/2
		v[N, 0] = bound1(a, b, T, example)

		#### The next few lines are for stage 4 (Diffusion Backward Time Center Space, thus implicit tridiagonal linear system)
		v[N, M] = bound2(a, b, T, example)			# No need for v[n+1, 0] as it will be the same as above
		d = v[N,1:M] + k*force(a, b, T, mesh, example)/2
		d[0] = d[0] + b*mu*v[N,0]/2
		d[M-2] = d[M-2] + b*mu*v[N,M]/2
		# c = np.asarray([-b*mu/2 for z in range(0,M-2)])
		# f = np.asarray([1+b*mu for z in range(0,M-1)])			# These are for my failed attempt at thomas algorithm
		# v[N, 1:M] = thomasAlg(c, f, c, d)
		W = np.zeros([M-1, M-1])
		for i in range(0,M-1):
			W[i][i] = 1 + b*mu
		for i in range(0,M-2):
			W[i+1][i] = -1*b*mu/2
			W[i][i+1] = W[i+1][i]

		v[N, 1:M] = np.linalg.solve(W,d)


	return v

############################################################################################################################################
############################################################################################################################################
############################################################################################################################################
############################################################################################################################################

def main():
	# a = np.asarray([1,1,1,1])
	# b = np.asarray([4,4,4,4,4])
	# c = np.asarray([1,1,1,1])
	# d = np.asarray([-1,2,2,-1,1])
	# M = np.asarray([[4,1,0,0,0],[1,4,1,0,0],[0,1,4,1,0],[0,0,1,4,1],[0,0,0,1,4]])
	# print(thomasAlg(a,b,c,d))
	# print(np.linalg.solve(M,d))

	example = 7
	a = 0
	b = 1
	mesh = 51
	h = 1.0/(mesh-1.0)
	k = h*h/4 
	T = 0.5

	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		print("epsilon")
	else:
		N = int(T/k) + 1
		final = 1
		print("non-epsilon")

	u = exact(a, b, k, mesh, example, T)
	ss = strange(a, b, k, mesh, example, T)
	pr = peacemanRachford(a, b, k, mesh, example, T)
	
	uu = np.asarray([u,ss,pr])

	# This is for the mesh
	xx = []
	for i in range(0, mesh):
		xx.append(h*i)

	fileName = ["exact.eps", "strang.eps", "peaceRach.eps", "finalTimePlot.eps"]
	title = ["Exact", "Strang Splitting", "Peaceman-Rachford"]


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
		plt.plot(xx, uu[j][t4], label="t=" + str(k*t4))
		plt.plot(xx, uu[j][t5], label="t=" + str(k*t5))
		plt.plot(xx, uu[j][t6], label="t=" + str(k*t6))
		if(final==0):
			plt.plot(xx, uu[j][N-1], label="Final=" + str(T))
		else:
			plt.plot(xx, uu[j][N], label="Final=" + str(T))
		plt.legend()
		plt.title(title[j])
		plt.savefig(fileName[j], format='eps')
		plt.show()

	# i is for u_i
	if(final==0):
		plt.plot(xx, uu[0][N-1], label="Exact")
		plt.plot(xx, uu[1][N-1], label="Strang", linestyle="dashed", dashes=(2,3))
		plt.plot(xx, uu[2][N-1], label="Peace-Rach", linestyle="dashed", dashes=(5,7))
	else:
		plt.plot(xx, uu[0][N], label="Exact")
		plt.plot(xx, uu[1][N], label="Strang", linestyle="dashed", dashes=(2,3))
		plt.plot(xx, uu[2][N], label="Peace-Rach", linestyle="dashed", dashes=(5,7))
	plt.legend()
	plt.title("Final T=" + str(T))
	plt.savefig(fileName[3], format='eps')
	plt.show()


	# mesh = 16
	# multiply = 4
	# errLogss = []
	# errLogpr = []
	# meshSize = []
	# count=0
	# for m in range(0,multiply):
	# 	print(count)
	# 	meshSize.append(mesh)
	# 	M = mesh - 1
	# 	h = 1/M
	# 	k = h*h/4

	# 	u = exact(a, b, k, mesh, example, T)
	# 	ss = strange(a, b, k, mesh, example, T)
	# 	pr = peacemanRachford(a, b, k, mesh, example, T)

	# 	if(abs(round(T/k) - T/k) < 0.00000001):
	# 		N = round(T/k) + 1
	# 		final = 0
	# 	else:
	# 		N = int(T/k) + 1
	# 		final = 1
	
	# 	ssNorm = math.sqrt(np.sum(h*np.square(ss[N-1] - u[N-1])))
	# 	prNorm = math.sqrt(np.sum(h*np.square(pr[N-1] - u[N-1])))
	# 	errLogss.append(ssNorm)
	# 	errLogpr.append(prNorm)

	# 	mesh = mesh*2
	# 	count = count + 1

	# print(meshSize)
	# print(errLogss)
	# print(errLogpr)

	# errLogss = np.log2(errLogss)
	# errLogpr = np.log2(errLogpr)
	# meshSize = np.log2(meshSize)

	# errTitle = [["Strang Splitting Error Sine", "Peaceman-Rashford Error Sine"], ["Strang Splitting Error Exponential", "Peaceman-Rashford Error Exponential"]]
	# errFile = [["strangErrSine.eps", "peaceErrSine.eps"], ["strangErrExp.eps", "peaceErrExp.eps"]]
	# err = [errLogss, errLogpr]
	# print(meshSize)
	# print(errLogss)
	# print(errLogpr)

	# for i in range(0,2):
	# 	plt.plot(meshSize, err[i])
	# 	plt.title(errTitle[1][i])
	# 	plt.xlabel("Log2 of Mesh")
	# 	plt.ylabel("Log2 of L2-Norm of the Errors")
	# 	plt.savefig(errFile[1][i], format='eps')
	# 	plt.show()




main()
