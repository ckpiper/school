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


# We are going to start with all features and then gradually get rid of less important ones 
# To do this we will need to get rid of columns in the data corresponding to the weights we deem not useful
def gradDescent(labels, data, its, eta, s, k, mu, M):
	beta = np.zeros(data[0].shape)
	betaIndex = np.asarray([x for x in range (0, data[0].shape[0])])		# This is for the indices which we keep
	for i in range(0, 500):
		deleteIndex = np.asarray([])						# This is a temp of indeces to delete
		Mi = int(k + (M - k)*max(0.0, (its - 2*i)/(2*i*mu + its)))
		z = labels * np.dot(data, beta)
		z[z>1] = 0
		# print("Mi = " + str(Mi))

		# The Gradient Descent Iteration
		beta = beta - 2*eta*(np.dot(data.T, (z-1)/(1+(z-1)**2)*labels)/N + s*beta)
		# print("Shape before selection = " + str(beta.shape))


		########### The Feature Selection Step ############
		# We will check for ties for smallest beta
		# Then we will how many elements after small are equal to small true = 1 so the sum is how many trues there are
		beta2 = beta**2
		betaSort = np.flip(np.sort(beta2, axis=None, kind='mergesort'), 0);
		small = betaSort[Mi-1];
		betaBool = (betaSort == small)[: Mi] 
		count = np.sum(betaBool)
		
		# This takes care of ties if there are ties for the smallest weight (when count > 1)
		# If There is a tie then we will just use count because it holds how many of the weights equal to small we can keep
		# We also need to keep track of the indices of the weights we decide to keep
		index = 0
		if(count > 1):
			for i in range(0, beta.shape[0]):
				if (beta2[i] < small):						
					beta[i] = 0
					deleteIndex = np.append(deleteIndex, index)		
				elif (beta2[i] == small and count != 0):
					count = count - 1
				elif (beta2[i] == small and count == 0):		
					beta[i] = 0
					deleteIndex = np.append(deleteIndex, index)
				index = index + 1
		else:
			for i in range(0, beta.shape[0]):
				if(beta2[i] < small):
					beta[i] = 0
					deleteIndex = np.append(deleteIndex, index)	
				index = index + 1

		# This changes the dimensions of beta and the data by getting rid of the zeroed out data and weights
		# The delete function deletes all the rows axis=0 or columns axis=1 of array given by the row/columns given as 2nd input
		betaIndex = np.delete(betaIndex, deleteIndex)
		beta = np.delete(beta, deleteIndex)
		data = np.delete(data, deleteIndex, 1)
		# print("Shape after selection = " + str(beta.shape) + "\n")

	# Now have beta be an array of 2 arrays the 1st being the weights and the 2nd being the corresponding indices
	beta = np.asarray([beta, betaIndex])

	return beta;


def predict(weights, data):
	predict = 1/(1 + np.exp(-1*np.dot(data, weights)))
	predict[predict >= 0.5] = 1
	predict[predict < 0.5] = -1
	return predict

def misclassify(labels, predict):
	predict = predict - labels
	return np.count_nonzero(predict)


eta = [5, 10, 0.01]				# Learning rate
k = [10, 30, 100, 300]			# Amount of featurs to select
its = 500						# Number of iterations
s = 0.001						# Shrinkage
mu = 100						# Annealing Parameter


for i in range(0,3):			# i is for the data sets 
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
		weights = gradDescent(trainLabel, trainData, its, eta[i], s, k[j], mu, M)

		print("Weights = " + str(np.count_nonzero(weights[0])))

		# This extracts the certain columns for which our weights correspond to 
		trainData = trainData[:, weights[1].astype(int)]
		validData = validData[:, weights[1].astype(int)]

		trainPredict = predict(weights[0], trainData)
		validPredict = predict(weights[0], validData)

		missTrain = misclassify(trainLabel, trainPredict)
		missValid = misclassify(validLabel, validPredict)

		missTrain = missTrain/N*100
		missValid = missValid/N2*100

		print("    Error Training = " + str(missTrain) + ", Error Valid = " + str(missValid) + "\n")
