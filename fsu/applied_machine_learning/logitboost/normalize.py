# Daniel Gonzalez, FSU Mathematics PhD
# Colton Piper, FSU Mathematics PhD
# Applied Machine Learning normalize data

from math import exp
from math import log
import numpy as np
import matplotlib.pyplot as plt

# Elements are pairs (data, labels)
filesTrain = [["../data/gisette/gisette_train.data", "../data/gisette/gisette_train.labels"], ["../data/dexter/dexter_train.csv", "../data/dexter/dexter_train.labels"], ["../data/madelon/madelon_train.data", "../data/madelon/madelon_train.labels"]]
filesValid = [["../data/gisette/gisette_valid.data", "../data/gisette/gisette_valid.labels"], ["../data/dexter/dexter_valid.csv", "../data/dexter/dexter_valid.labels"], ["../data/madelon/madelon_valid.data", "../data/madelon/madelon_valid.labels"]]

writeTrainFiles = [["./dataNorm/gisette/gisette_train_norm_data", "./dataNorm/gisette/gisette_train_norm_labels"], ["./dataNorm/dexter/dexter_train_norm_data", "./dataNorm/dexter/dexter_train_norm_labels"], ["./dataNorm/madelon/madelon_train_norm_data", "./dataNorm/madelon/madelon_train_norm_labels"]]
writeValidFiles = [["./dataNorm/gisette/gisette_valid_norm_data", "./dataNorm/gisette/gisette_valid_norm_labels"], ["./dataNorm/dexter/dexter_valid_norm_data", "./dataNorm/dexter/dexter_valid_norm_labels"], ["./dataNorm/madelon/madelon_valid_norm_data", "./dataNorm/madelon/madelon_valid_norm_labels"]]

fileName = ["Gisette", "Dexter", "Madelon"]

# This puts 2D array of numbers from a file into a 2D list (list of lists)
# The line.split(" ") separates line (which is just one list) by spaces
# The [:-1] removes the last element which is a newline character
# Then turn those strings into floats
def parseData(fileFeat):
	feat = []
	file = open(fileFeat, "r")
	f = fileFeat[-3:]

	for line in file:			# The first strip gets rid of white space then next gets rid of newline character
		if(f == "csv"):
			line = [float(element) for element in line.strip("\n").split(",") ]
		else:	
			line = [float(element) for element in line.strip().strip("\n").split(" ") ]
		feat.append(line)

	feat = np.asarray(feat)
	file.close()
	return feat

def parseLabel(fileLab):
	label = []
	file = open(fileLab, "r")
	for line in file:
		label.append(float(line))
	feat = np.asarray(label)
	file.close()
	return label

# First find Mean of each feature
# Second find the standard deviation (std) by sqrt[sum (xi - mean)^2]
# Third subtract the mean then divide by the std
# Last we need to normalize the other data we want to test using the training normalization
# data is a 2D lisy containing all the samples with features
def normalize(trainData, otherData):
	N = len(trainData)
	M = len(trainData[0])

	# Mean - sums the rows all together then divide by N
	# avg = trainData.sum(axis=0)/N
	avg = np.mean(trainData, axis=0)

	# Standard Deviation - data - avg (it knows to make a matrix of same rows for avg)
	# std = np.sqrt((np.square(trainData - avg)).sum(axis=0)/N)
	std = np.std(trainData, axis=0)

	# Subtract The mean then divide by the std (Again it knows to tile up rows for avg and std)
	trainData = (trainData - avg)/std
	mask = (np.isfinite(trainData)).any(axis=0)
	trainData = trainData[:,mask]

	# Normalize the other data
	otherData = (otherData - avg)/std
	mask = (np.isfinite(otherData)).any(axis=0)
	otherData = otherData[:, mask]

	return (trainData, otherData)

def transformData(data):
	data = np.insert(data, 0, 1, axis=1)
	return data

def transformLabel(labelSet):
	for i in range(len(labelSet)):
		if (labelSet[i] != 1):
			labelSet[i] = -1
	return labelSet

def writeData(filePath, data):
	np.save(filePath, data)

def writeLabel(filePath, labels):
	np.save(filePath, labels)


for i in range(0,3):

	print("\n" + fileName[i])

	trainData = parseData(filesTrain[i][0])
	validData = parseData(filesValid[i][0])
	trainLabel = parseLabel(filesTrain[i][1])
	validLabel = parseLabel(filesValid[i][1])

	# print("Normalizing")
	print("Transforming ")

	# (trainData, validData) = normalize(trainData, validData)
	trainData = transformData(trainData)
	validData = transformData(validData)
	trainLabel = transformLabel(trainLabel)
	validLabel = transformLabel(validLabel)

	print("Writng")

	writeData(writeTrainFiles[i][0], trainData)
	writeData(writeValidFiles[i][0], validData)
	writeLabel(writeTrainFiles[i][1], trainLabel)
	writeLabel(writeValidFiles[i][1], validLabel)

	print("Done" + "\n")
