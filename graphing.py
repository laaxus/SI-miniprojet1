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
rw = analyse_data('MeasuresRW')
ph = analyse_data('MeasuresPH')
ts = analyse_data('MeasuresTS')
tts = analyse_data('MeasuresTTS')

fig1 = plt.figure()
plt.errorbar(np.arange(1,9,1),pc[0], yerr = [pc[1],pc[2]], fmt = '-b', ecolor = 'r', capthick = 3, barsabove = True, label = 'Producer-Consumer')
plt.ylim(0,4)
plt.title('Producer-Consumer')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/PC.pdf")
plt.show()
plt.close()

fig2 = plt.figure()
plt.errorbar(np.arange(1,9,1),rw[0], yerr = [rw[1],rw[2]], fmt = '-b', ecolor = 'r', capthick = 3, barsabove = True, label = 'Reader-Writer')
plt.ylim(0,0.5)
plt.title('Reader-Writer')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/RW.pdf")
plt.show()
plt.close()

fig3 = plt.figure()
plt.errorbar(np.arange(1,9,1),ph[0], yerr = [ph[1],ph[2]], fmt = '-b', ecolor = 'r', capthick = 3, barsabove = True, label = 'Philosophe')
plt.ylim(0,1)
plt.title('Philosophe')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/PH.pdf")
plt.show()
plt.close()


fig4 = plt.figure()
plt.errorbar(np.arange(1,9,1),ts[0], yerr = [ts[1],ts[2]], fmt = '-b', ecolor = 'm', capthick = 3, barsabove = True, label = 'Test and Set')
plt.errorbar(np.arange(1,9,1),tts[0], yerr = [tts[1],tts[2]], fmt = '-g', ecolor = 'r', capthick = 3, barsabove = True, label = 'Test and Test and Set')
plt.ylim(0,4.5)
plt.title('Mutexes Analysis')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/TS&TTS.pdf")
plt.show()
plt.close()
