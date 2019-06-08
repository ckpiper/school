# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning Assignment 4

from math import exp
from math import log
import numpy as np
import matplotlib.pyplot as plt

# gisette_valid_norm.data
filesTrain = [["./dataNorm/gisette/gisette_train_norm_data.npy", "./dataNorm/gisette/gisette_train_norm_labels.npy"], ["./dataNorm/dexter/dexter_train_norm_data.npy", "./dataNorm/dexter/dexter_train_norm_labels.npy"], ["./dataNorm/madelon/madelon_train_norm_data.npy", "./dataNorm/madelon/madelon_train_norm_labels.npy"]]
filesValid = [["./dataNorm/gisette/gisette_valid_norm_data.npy", "./dataNorm/gisette/gisette_valid_norm_labels.npy"], ["./dataNorm/dexter/dexter_valid_norm_data.npy", "./dataNorm/dexter/dexter_valid_norm_labels.npy"], ["./dataNorm/madelon/madelon_valid_norm_data.npy", "./dataNorm/madelon/madelon_valid_norm_labels.npy"]]
fileName = ["Gisette", "Dexter", "Madelon"]

# This puts 2D array of numbers from a file into a 2D list (list of lists)
# The line.split(" ") separates line (which is just one list) by spaces
# The [:-1] removes the last element which is a newline character
# Then turn those strings into floats
def parseData(fileFeat):
	feat = np.load(fileFeat)
	return feat

def parseLabel(fileLab):
	label = np.load(fileLab)
	return label

def theta(weights, x, y, eta, lamb):
	weights = weights + eta*np.dot(x.T, (y - 1/(1+np.exp(np.dot(-x, weights)))))
	w0 = weights[0]
	weights[np.abs(weights) <= lamb] = 0
	weights[0] = w0
	return weights

def predict(weights, data):
	predict = np.dot(data, weights)
	predict[predict >= 0] = 1
	predict[predict < 0] = 0
	return predict

def misclassify(labels, predict):
	predict = predict - labels
	return np.count_nonzero(predict)

lamb = [[0.0025, 0.00876, 0.0297959736432833830616084825], [0.0032, 0.0062, 0.0245], [0.002342, 0.00439, 0.01695], [0.001384, 0.0523, 0.0074]]


for i in range(1,2):			# This is for files
	print("\n" + fileName[i])
	for j in range(3,4):		# This is for the lambdas
		
		trainData = parseData(filesTrain[i][0])
		validData = parseData(filesValid[i][0])
		trainLabel = parseLabel(filesTrain[i][1])
		validLabel = parseLabel(filesValid[i][1])

		N = trainData.shape[0]
		N2 = validData.shape[0]
		M = trainData.shape[1]

		eta = 1/N
		lam = lamb[j][i]
		weights = np.zeros(M+1)

		trainData = np.asarray([ np.append([1], x) for x in trainData]) # Adds a columns of 1s for w0
		validData = np.asarray([ np.append([1], x) for x in validData]) # Adds a columns of 1s for w0

		for itCount in range(0,100):
			weights = theta(weights, trainData, trainLabel, eta, lam)

		print("Weights = " + str(np.count_nonzero(weights)))

		trainPredict = predict(weights, trainData)
		validPredict = predict(weights, validData)

		missTrain = misclassify(trainLabel, trainPredict)
		missValid = misclassify(validLabel, validPredict)

		missTrain = missTrain/N*100
		missValid = missValid/N2*100

		print("    Error Training = " + str(missTrain) + ", Error Valid = " + str(missValid))
