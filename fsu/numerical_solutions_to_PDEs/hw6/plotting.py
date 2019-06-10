# This plots the algorithms run in hw1.cpp 

import math
import matplotlib.pyplot as plt
import numpy as np

def main():

	fileName = ["data/exact.txt", "data/constant.txt", "data/linear.txt", "data/minmod.txt"]

	a = 1;
	cells =25;
	L = 1.0;
	h = L/cells;
	k = h/a * 0.25
	T = 100*k
	n = 4

	# Round it to nearest integer as it should be an exact division add 1 for initial
	# int = floor function brings N down then add 1 for initial then add one in  setZeros function for final
	if(abs(round(T/k) - T/k) < 0.00000001):
		N = round(T/k) + 1
		final = 0
		vv = np.zeros([4, N, cells])
		print("Epsilon")
	else:
		N = int(T/k) + 1
		final = 1
		vv = np.zeros([4, N+1, cells])
		print("Not-Epsilon")


	for m in range(0,n):
		f = open(fileName[m], "r")
		i = 0
		for line in f:
			row = np.asarray(line.split(" "))
			row = np.delete(row, -1)					# Gets rid of the newline character
			vv[m, i] = row
			i = i + 1


	title = ["Exact Solution", "Constant Approx", "Linear Approx", "Minmod Linear Approx"]
	plotFile = ["plots/exact.eps", "plots/constant.eps", "plots/linear.eps", "plots/minmod.eps", ]

	xx = np.zeros([cells])
	for j in range(0,cells):
		xx[j] = h/2.0 + j*h

	if(final==0):
		plt.plot(xx, vv[0][N-1], label="Exact")
		plt.plot(xx, vv[1][N-1], label="Constant")
		plt.plot(xx, vv[2][N-1], label="Linear")
		plt.plot(xx, vv[3][N-1], label="Minmod")
	else:
		plt.plot(xx, vv[0][N], label="Exact")
		plt.plot(xx, vv[1][N], label="Constant")
		plt.plot(xx, vv[2][N], label="Linear")
		plt.plot(xx, vv[3][N], label="Minmod")

	plt.legend()
	plt.tick_params(labelbottom=True, labeltop=False, labelleft=True, labelright=True, bottom=True, top=True, left=True, right=True)
	plt.title("Final Time = " + str(T) + " for Solutions")
	plt.savefig("plots/finalTime.eps", format='eps')
	plt.show()


	# mult = 1
	# plt.plot(xx, vv[0][0], label="Exact")
	# plt.plot(xx, vv[0][mult], label="Exact")
	# plt.plot(xx, vv[1][mult], label="Constant")
	# plt.plot(xx, vv[2][mult], label="Linear")
	# plt.plot(xx, vv[3][mult], label="Minmod")

	# plt.legend()
	# plt.tick_params(labelbottom=True, labeltop=False, labelleft=True, labelright=True, bottom=True, top=True, left=True, right=True)
	# plt.title("Time = " + str(k*mult) + " for Solutions")
	# plt.savefig("plots/fTime" + str(mult) + ".eps", format='eps')
	# plt.show()

	t1 = int(N/100)
	t2 = int(N/33)
	t3 = int(N/10)
	t4 = int(N/3)
	t5 = int(2*N/3)
	t6 = int(5*N/6)


	for j in range(0,n):
		plt.plot(xx, vv[j][0], label="t=0")
		# plt.plot(xx, vv[j][1], label="t=" + str(k*1))
		# plt.plot(xx, vv[j][2], label="t=" + str(k*2))
		# plt.plot(xx, vv[j][t1], label="t=" + str(k*t1))
		plt.plot(xx, vv[j][t2], label="t=" + str(k*t2))
		plt.plot(xx, vv[j][t3], label="t=" + str(k*t3))
		plt.plot(xx, vv[j][t4], label="t=" + str(k*t4))
		plt.plot(xx, vv[j][t5], label="t=" + str(k*t5))
		plt.plot(xx, vv[j][t6], label="t=" + str(k*t6))
		if(final==0):
			plt.plot(xx, vv[j][N-1], label="Final=" + str(T))
		else:
			plt.plot(xx, vv[j][N], label="Final=" + str(T))
		plt.legend()
		plt.tick_params(labelbottom=True, labeltop=False, labelleft=True, labelright=True, bottom=True, top=True, left=True, right=True)
		plt.title(title[j])
		plt.savefig(plotFile[j], format='eps')
		plt.show()









main()
