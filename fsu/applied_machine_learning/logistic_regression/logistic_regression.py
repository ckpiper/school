# This is the Logistic Regression hw3 for Applied Machine learning
import math
import operator
pi = math.pi


# This puts 2D array of numbers from a file into a 2D list (list of lists)
# The line.split(" ") separates line (which is just one list) by spaces
# The [:-1] removes the last element which is a newline character
# Then turn those strings into floats
def parseData(fileFeat):
	feat = []
	for line in fileFeat:			# The first strip gets rid of white space then next gets rid of newline character
		line = [float(element) for element in line.strip().strip("\n").split(" ") ]
		feat.append(line)
	return feat


def parseLabel(fileLab):
	label = []
	for line in fileLab:
		label.append(float(line))
	return label


# w = vector of weights corresponding to each feature
# x[j][i] = training data where j is sample and i is feature of j sample
# y[j] = labels of training data
# mu = Step size of direction
# lam = Lambda is the constant for Max A Posteriori
# N = The amount of training data
# M = The amount of features + 1
def gradAscent(w,x,y,mu,lam):
	N = len(x)
	M = len(w)
	for k in range(0, M):
		if(k%100==0):
			print(k)
		c = 0						# The partial derivative of wk
		for j in range(0,N):
			temp = w[0]
			for i in range(1,M):
				temp = temp + w[i]*x[j][i-1]  # As w[1] corresponds to x[j][0] because w[0] is constant
			temp = math.exp(temp)
			temp = y[j]-temp/(1+temp)
			if (k!=0):
				temp = x[j][k-1]*temp
			c = c + temp

		w[k] = (1-mu*lam)*w[k] + mu*c/N
	return w


# First find Mean of each feature
# Second find the standard deviation (std) by sqrt[sum (xi - mean)^2]
# Third subtract the mean then divide by the std
# Last we need to normalize the other data we want to test using the training normalization
# data is a 2D lisy containing all the samples with features
def normalizeData(trainData, otherData):
	avg = trainData[0]
	N = len(trainData)
	M = len(avg)
	# Mean
	for i in range(1, N):
		avg = [a+d for (a,d) in zip(avg,trainData[i])]
	# avg = [[a+d for (a,d) in zip(avg,data[i])] for i in range(1,N)]
	avg = [a/N for a in avg]
	
	# Standard Deviation
	std = [(d-a)**2 for (a,d) in zip(avg,trainData[0])]
	for i in range(1,N):
		std = [s + (d-a)**2 for (s,a,d) in zip(std,avg,trainData[i])]
	std = [math.sqrt(s) for s in std]

	# Third Step
	for i in range(N):
		trainData[i] = [(d-a)/s for (s,a,d) in zip(std,avg,trainData[i]) if s!=0]

	# Last Step
	for i in range(len(otherData)):
		otherData[i] = [(d-a)/s for (s,a,d) in zip(std,avg,otherData[i]) if s!=0]

	return (trainData, otherData)


def transformLabel(labelSet):
	for i in range(len(labelSet)):
		if (labelSet[i] == -1):
			labelSet[i] = 0
	return labelSet

def writeData(file, data):
	for sample in trainData:
		for element in sample:
			file.write(str(element) + " ")
		file.write("\n")

def writeLabel(file, labels):
	for element in labels:
		file.write(str(element) + "\n")



strTrainData = ["../data/gisette/gisette_train.data", "../data/MADELON/madelon_train.data", "../data/hillValley/X.dat"]
strTrainLabel = ["../data/gisette/gisette_train.labels", "../data/MADELON/madelon_train.labels", "../data/hillValley/Y.dat"]
strValidData = ["../data/gisette/gisette_valid.data", "../data/MADELON/madelon_valid.data", "../data/hillValley/Xtest.dat"]
strValidLabel = ["../data/gisette/gisette_valid.labels", "../data/MADELON/madelon_valid.labels", "../data/hillValley/Ytest.dat"]
strTrainPercents = ["./gisetteTrain.percents", "./madelonTrain.percents", "./hillTrain.percents"]
strValidPercents = ["./gisetteValid.percents", "./madelonValid.percents", "./hillTalid.percents"]
strNormTrainData = ["./gisetteTrainNorm.data", "./madelonTrainNorm.data", "./hillTrainNorm.data"]
strTransTrainLabel = ["./gisetteTrainTrans.labels", "./madelonTrainTras.labels", "./hillTrainTrans.labels"]
strNormValidData = ["./gisetteValidNorm.data", "./madelonValidNorm.data", "./hillValidNorm.data"]
strTransValidLabel = ["./gisetteValidTrans.labels", "./madelonValidTras.labels", "./hillValidTrans.labels"]


lam = 0.001
mu = 1


for d in range(2,3):

	fileTrainData = open(strTrainData[d], "r")
	fileTrainLabel = open(strTrainLabel[d], "r")
	fileValidData = open(strValidData[d], "r")
	fileValidLabel = open(strValidLabel[d], "r")
	fileTrainPercents = open(strTrainPercents[d], "w")
	fileValidPercents = open(strValidPercents[d], "w")
	fileNormTrainData = open(strNormTrainData[d], "w")
	fileTransTrainLabel = open(strTransTrainLabel[d], "w")
	fileNormValidData = open(strNormValidData[d], "w")
	fileTransValidLabel = open(strTransValidLabel[d], "w")

	trainData = parseData(fileTrainData)
	trainLabel = parseLabel(fileTrainLabel)
	validData = parseData(fileValidData)
	validLabel = parseLabel(fileValidLabel)

	(trainData, validData) = normalizeData(trainData, validData)
	# writeData(fileNormTrainData, trainData)
	# writeData(fileNormValidData, validData)
	M = len(trainData[0])

	trainLabel = transformLabel(trainLabel)
	validLabel = transformLabel(validLabel)
	# writeLabel(fileTransTrainLabel, trainLabel)
	# writeLabel(fileTransValidLabel, validData)


	w = [0 for x in range(M+1)]
	for t in range(0, 20):
		w = gradAscent(w,trainData,trainLabel,mu,lam)

	print(w)

	for x in validData:
		predict

