
import math
import matplotlib.pyplot as plt
import numpy as np

pi = math.pi

a = 1.0;
cells = 25;
L = 1.0;
h = L/cells;
k = h/a * 0.25;

# lam = np.asarray([0.2, 0.4, 0.5, 0.6, 0.8])
lam = np.asarray([0.25, 0.5, 0.75])
i = lam.size

MPlot = 300
theta = np.asarray([(2*z/MPlot - 1)*pi for z in range(0,MPlot+1)])
gUpwind = np.zeros([i,301])
gOther = np.zeros([i,301])
alphaUpwind = np.zeros([i,301])
alphaOther = np.zeros([i,301])


for n in range(0,i):
	gUpwind[n] = np.sqrt(1 - 2*a*lam[n]*(1-a*lam[n])*(1 - np.cos(theta)))
	gOther[n] = np.sqrt(    ( 1-a*lam[n]*(1-np.cos(theta)-0.5*(1-a*lam[n])*(np.sin(theta))**2) )**2   +   ( a*lam[n]*np.sin(theta)*(-1-0.5*(1-a*lam[n])*(1-np.cos(theta))) )**2     )
	alphaUpwind[n] = -1*np.arctan( (-1*a*lam[n]*np.sin(theta)) / (1 - a*lam[n]*(1-np.cos(theta)))) / (a*theta*lam[n])
	alphaOther[n] = -1*np.arctan(    ( a*lam[n]*np.sin(theta)*(-1-0.5*(1-a*lam[n])*(1-np.cos(theta))) ) / ( 1-a*lam[n]*(1-np.cos(theta)-0.5*(1-a*lam[n])*(np.sin(theta))**2) )     )  / (a*lam[n]*theta)

	
# plt.plot(theta, gUpwind[0], label="Upwind " + str(lam[0]))
# plt.plot(theta, gUpwind[1], label="Upwind " + str(lam[1]))
# plt.plot(theta, gUpwind[2], label="Upwind " + str(lam[2]))
# plt.plot(theta, gUpwind[3], label="Upwind " + str(lam[3]))
# plt.plot(theta, gUpwind[4], label="Upwind " + str(lam[4]))
# # plt.legend()
# # plt.show()

# plt.plot(theta, gOther[0], label="Other " + str(lam[0]))
# plt.plot(theta, gOther[1], label="Other " + str(lam[1]))
# plt.plot(theta, gOther[2], label="Other " + str(lam[2]))
# plt.plot(theta, gOther[3], label="Other " + str(lam[3]))
# plt.plot(theta, gOther[4], label="Other " + str(lam[4]))

# plt.title("|G(Theta)|" + ", a*lam = " + str(lam))
# plt.legend()
# plt.savefig("plots/gTheta.eps", format='eps')
# plt.show()

# plt.plot(theta, alphaUpwind[0], label="Upwind " + str(lam[0]))
# plt.plot(theta, alphaUpwind[1], label="Upwind " + str(lam[1]))
# plt.plot(theta, alphaUpwind[2], label="Upwind " + str(lam[2]))
# plt.plot(theta, alphaUpwind[3], label="Upwind " + str(lam[3]))
# plt.plot(theta, alphaUpwind[4], label="Upwind " + str(lam[4]))
# # plt.legend()
# # plt.show()

# plt.plot(theta, alphaOther[0], label="Other " + str(lam[0]))
# plt.plot(theta, alphaOther[1], label="Other " + str(lam[1]))
# plt.plot(theta, alphaOther[2], label="Other " + str(lam[2]))
# plt.plot(theta, alphaOther[3], label="Other " + str(lam[3]))
# plt.plot(theta, alphaOther[4], label="Other " + str(lam[4]))

# plt.title("Alpha/a" + ", a*lam = " + str(a*lam))
# plt.legend()
# plt.savefig("plots/alpha.eps", format='eps')
# plt.show()

################333333333######33333333333333333333333333333333333333333333333333############3

plt.plot(theta, gUpwind[0], label="Upwind " + str(lam[0]))
plt.plot(theta, gUpwind[1], label="Upwind " + str(lam[1]))
plt.plot(theta, gUpwind[2], label="Upwind " + str(lam[2]))
# plt.legend()
# plt.show()

plt.plot(theta, gOther[0], label="Other " + str(lam[0]))
plt.plot(theta, gOther[1], label="Other " + str(lam[1]))
plt.plot(theta, gOther[2], label="Other " + str(lam[2]))

plt.title("|G(Theta)|" + ", a*lam = " + str(lam))
plt.legend()
plt.savefig("plots/gTheta.eps", format='eps')
plt.show()

plt.plot(theta, alphaUpwind[0], label="Upwind " + str(lam[0]))
plt.plot(theta, alphaUpwind[1], label="Upwind " + str(lam[1]))
plt.plot(theta, alphaUpwind[2], label="Upwind " + str(lam[2]))
# plt.legend()
# plt.show()

plt.plot(theta, alphaOther[0], label="Other " + str(lam[0]))
plt.plot(theta, alphaOther[1], label="Other " + str(lam[1]))
plt.plot(theta, alphaOther[2], label="Other " + str(lam[2]))

plt.title("Alpha/a" + ", a*lam = " + str(a*lam))
plt.legend()
plt.savefig("plots/alpha.eps", format='eps')
plt.show()

