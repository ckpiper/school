import math
import matplotlib.pyplot as plt

pi = math.pi

def v0a(mesh):
	h = 1/(mesh-1)
	v0 = []
	x = 0
	for i in range(0,mesh):
		v0.append(math.sin(4*pi*x))
		x = x + h

	return v0

def v0b(mesh):
	h = 1/(mesh-1)
	v0 = []
	x=0
	for i in range(0,mesh):
		if x >= 0.25 and x <=0.75:
			v0.append(1)
		else:
			v0.append(0)
		x = x + h
	return v0


mesh = 201
M = mesh - 1
T = 0.8
a = 2
h = 1/M
k = 0.0001
N = int(T/k)
kFin = T - N*k

# This is the Leap Frog method
###############################################################################################
vLF = []
vLF.append(v0a(mesh))

# This will be the Lax-Wendroff Method as the first step of the
v0 = [0]
for m in range(1, M):
	vm = vLF[0][m] - a*k*(vLF[0][m+1]-vLF[0][m-1])/(2*h) + a*a*k*k*(vLF[0][m+1]-2*vLF[0][m]+vLF[0][m-1])/(2*h*h)
	v0.append(vm)
vm = vLF[0][M] - a*k*(vLF[0][1]-vLF[0][M-1])/(2*h) - a*a*k*k*(vLF[0][1]-2*vLF[0][M]+vLF[0][M-1])/(2*h*h)
v0.append(vm)
v0[0] = v0[M]
vLF.append(v0)

# Leap frog Method
for n in range(2,N):
	vn = [0]

	for m in range(1, M):
		vm = vLF[n-2][m] - a*k*(vLF[n-1][m+1]-vLF[n-1][m-1])/h
		vn.append(vm)
	vm = vLF[n-2][M] - a*k*(vLF[n-1][1]-vLF[n-1][M-1])/h
	vn.append(vm)
	vn[0] = vn[M]
	vLF.append(vn)





# This is the Lax Wendroff Mehtod Full method
###############################################################################################
vLW = []
vLW.append(v0a(mesh))

for n in range(1,N):
	vn = [0]

	for m in range(1, M):
		vm = vLW[n-1][m] - a*k*(vLW[n-1][m+1]-vLW[n-1][m-1])/(2*h) + a*a*k*k*(vLW[n-1][m+1]-2*vLW[n-1][m]+vLW[n-1][m-1])/(2*h*h)
		vn.append(vm)
	vm = vLW[n-1][M] - a*k*(vLW[n-1][1]-vLW[n-1][M-1])/(2*h) + a*a*k*k*(vLW[n-1][1]-2*vLW[n-1][M]+vLW[n-1][M-1])/(2*h*h)
	vn.append(vm)
	vn[0] = vn[M]
	vLW.append(vn)




# Exact Solution
##############################################################################################
u = []
u.append(v0a(mesh))
t = 0
for n in range(0,N):
	un = [];
	x=0
	for m in range(0,mesh):
		un.append(math.sin(4*pi*((x-a*t)%1)))
		x = x + h
	t = t + k
	u.append(un)








mesh2 = 2*mesh-1
M2 = mesh2-1
T = 0.8
h = 1/M2


vLF2 = []
vLF2.append(v0a(mesh2))
# This will be the Lax-Wendroff Method as the first step of the
v0 = [0]
for m in range(1, M2):
	vm = vLF2[0][m] - a*k*(vLF2[0][m+1]-vLF2[0][m-1])/(2*h) + a*a*k*k*(vLF2[0][m+1]-2*vLF2[0][m]+vLF2[0][m-1])/(2*h*h)
	v0.append(vm)
vm = vLF2[0][M2] - a*k*(vLF2[0][1]-vLF2[0][M2-1])/(2*h) - a*a*k*k*(vLF2[0][1]-2*vLF2[0][M2]+vLF2[0][M2-1])/(2*h*h)
v0.append(vm)
v0[0] = v0[M2]
vLF2.append(v0)

# Leap frog Method
for n in range(2,N):
	vn = [0]

	for m in range(1, M2):
		vm = vLF2[n-2][m] - a*k*(vLF2[n-1][m+1]-vLF2[n-1][m-1])/h
		vn.append(vm)
	vm = vLF2[n-2][M2] - a*k*(vLF2[n-1][1]-vLF2[n-1][M2-1])/h
	vn.append(vm)
	vn[0] = vn[M2]
	vLF2.append(vn)

# Lax-Wendroff Method
vLW2 = []
vLW2.append(v0a(mesh2))
for n in range(1,N):
	vn = [0]

	for m in range(1, M2):
		vm = vLW2[n-1][m] - a*k*(vLW2[n-1][m+1]-vLW2[n-1][m-1])/(2*h) + a*a*k*k*(vLW2[n-1][m+1]-2*vLW2[n-1][m]+vLW2[n-1][m-1])/(2*h*h)
		vn.append(vm)
	vm = vLW2[n-1][M2] - a*k*(vLW2[n-1][1]-vLW2[n-1][M2-1])/(2*h) + a*a*k*k*(vLW2[n-1][1]-2*vLW2[n-1][M2]+vLW2[n-1][M2-1])/(2*h*h)
	vn.append(vm)
	vn[0] = vn[M2]
	vLW2.append(vn)

errLogLF = []
for m in range(0,mesh):
	e = abs((vLF[N-1][m]-u[N-1][m])/(vLF2[N-1][m*2]-u[N-1][m]))
	errLogLF.append(math.log(e)/math.log(2))

errLogLW = []
for m in range(0,mesh):
	e = abs((vLW[N-1][m]-u[N-1][m])/(vLW2[N-1][m*2]-u[N-1][m]))
	errLogLW.append(math.log(e)/math.log(2))



xx = [0]
for x in range(1, mesh):
	xx.append(0 + h*x)

plt.plot(xx, u[0], label="init")
plt.plot(xx, u[N-3], label="t1")
plt.plot(xx, u[N-2], label="t2")
plt.plot(xx, u[N-1], label="t3")
plt.legend()
plt.title("Exact Solution")
# plt.savefig("exactSoln.eps'", format="eps")
plt.show()

plt1.plot(xx, vLF[0], label="init")
plt1.plot(xx, vLF[N-3], label="t1")
plt1.plot(xx, vLF[N-2], label="t2")
plt1.plot(xx, vLF[N-1], label="t3")
plt1.legend()
plt1.title("Leap Frog Method")
# plt1.savefig("leapFSoln.eps'", format="eps")
plt1.show()

plt2.plot(xx, vLW[0], label="init")
plt2.plot(xx, vLW[N-3], label="t1")
plt2.plot(xx, vLW[N-2], label="t2")
plt2.plot(xx, vLW[N-1], label="t3")
plt2.legend()
plt2.title("Vax-Wendroff Method")
# plt2.savefig("vaxWSoln.eps'", format="eps")
plt2.show()

plt3.plot(xx, errLogLF)
plt3.title("Leap Frog Method Cnvergence")
# plt3.savefig("convLFSoln.eps'", format="eps")
plt3.show()

plt4.plot(xx, errLogLW)
plt4.title("Vax-Wendroff Method Convergence")
# plt4.savefig("convLWSoln.eps'", format="eps")
plt4.show()



