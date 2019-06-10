# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Feature Selection with Annealing (FSA) Lorenz Loss function

from math import exp
from math import log
import numpy as np
import matplotlib.pyplot as plt


filesTrain = [["./dataNorm/gisette/gisette_train_norm_data.npy", "./dataNorm/gisette/gisette_train_norm_labels.npy"], ["./dataNorm/dexter/dexter_train_norm_data.npy", "./dataNorm/dexter/dexter_train_norm_labels.npy"], ["./dataNorm/madelon/madelon_train_norm_data.npy", "./dataNorm/madelon/madelon_train_norm_labels.npy"]]
filesValid = [["./dataNorm/gisette/gisette_valid_norm_data.npy", "./dataNorm/gisette/gisette_valid_norm_labels.npy"], ["./dataNorm/dexter/dexter_valid_norm_data.npy", "./dataNorm/dexter/dexter_valid_norm_labels.npy"], ["./dataNorm/madelon/madelon_valid_norm_data.npy", "./dataNorm/madelon/madelon_valid_norm_labels.npy"]]
fileName = ["Gisette", "Dexter", "Madelon"]


def parseData(fileFeat):
	feat = np.load(fileFeat)
	return feat

def parseLabel(fileLab):
	label = np.load(fileLab)
	return label

def logitBoost(X, Y, k):
	N = X.shape[0]
	M = X.shape[1]
	beta = np.zeros(M)
	loss = np.zeros(k)

	for i in range(0,k):
		H = np.dot(X, beta)
		p = 1/(1 + np.exp(-2*H))
		w = p*(1-p)
		z =	0.5*(Y + 1)- p
		z[w==0] = 0
		z[w!=0] = z[w!=0]/w[w!=0]
		# z = np.divide(z, w, out=np.zeros(N), where=(w!=0))

		coef = np.zeros((2, M-1))
		newloss = np.zeros(M-1)
		for j in range(0,M-1):
			xj = X[:,j+1]
			a = np.sum(w)
			b = np.sum(w*xj)
			c = np.sum(w*xj**2)
			d = np.sum(w*z)
			e = np.sum(w*xj*z)
			temp = a*c-b**2
			if(temp !=0):
				bj = np.asarray([(c*d-b*e)/temp, (a*e-b*d)/temp])
			else:
				bj = np.asarray([d/a, 0])

			Hj = H + 0.5*(bj[0] + bj[1] * xj)
			lossj = np.sum(np.log(1 + np.exp(-2*Y*Hj)))
			coef[:,j] = bj
			newloss[j] = lossj

		minLossIndex = np.argmin(newloss)
		beta[0] = beta[0] + 0.5*coef[0,minLossIndex]
		beta[minLossIndex+1] = beta[minLossIndex+1] + 0.5*coef[1][minLossIndex]


	return beta, H



def predict(beta, data, H):	
	predict = np.sign(np.dot(data,beta))
	return predict

def misclassify(labels, predict):
	predict = predict - labels
	return np.count_nonzero(predict)



k = [10, 30, 100, 300]			# Amount of featurs to select

for i in range(1,3):			# i is for the data sets 
	print("\n" + fileName[i])
	for j in range(0,4):		# j is to iterate through the k list

		trainData = parseData(filesTrain[i][0])
		validData = parseData(filesValid[i][0])
		trainLabel = parseLabel(filesTrain[i][1])
		validLabel = parseLabel(filesValid[i][1])

		N = trainData.shape[0]
		N2 = validData.shape[0]
		M = trainData.shape[1]

		# Now weights is an array holding 2 arrays. 1st being weights, 2nd being correspoding indices of weights
		beta, H = logitBoost(trainData, trainLabel, k[j])

		print("Beta = " + str(np.count_nonzero(beta)) + ",  Beta Shape = " + str(beta.shape))

		trainPredict = predict(beta, trainData, H)
		validPredict = predict(beta, validData, H)

		missTrain = misclassify(trainLabel, trainPredict)
		missValid = misclassify(validLabel, validPredict)

		missTrain = missTrain/N*100
		missValid = missValid/N2*100

		# print(" Loss = " + str(weights[2]))
		print("    Error Training = " + str(missTrain) + ", Error Valid = " + str(missValid) + "\n")
