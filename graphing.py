#!/usr/bin/env python3


import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#returns [[average], [lowerError], [higherError]] []
def analyse_data (filename):
	out = pd.read_csv('Measures/'+filename+'.csv', header = None, skiprows = 1).T
	out.columns = out.iloc[0]
	out.drop(0,inplace=True)
	average = out.mean()
	lowerError = average - out.min()
	higherError = out.max() - average
	return [average, lowerError, higherError]

pc = analyse_data('MeasuresPC')

fig1 = plt.figure()
plt.errorbar(np.arange(1,9,1),pc[0], yerr = [pc[1],pc[2]], fmt = '-b', ecolor = 'r', capthick = 3, barsabove = True, label = 'Producer-Consumer')
plt.ylim(0,4)
plt.title('Producer-Consumer')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("PC.pdf")
plt.show()
plt.close()
