#!/usr/bin/env python3


import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#returns [[average], [standard deviation]]
def analyse_data (filename):
	out = pd.read_csv('Measures/'+filename+'.csv', header = None, skiprows = 1).T
	out.columns = out.iloc[0]
	out.drop(0,inplace=True)
	average = out.mean()
	std = np.std(out)
	return [average, std]

pc = analyse_data('MeasuresPC')
pc2 = analyse_data('MeasuresPC2')
rw = analyse_data('MeasuresRW')
rw2 = analyse_data('MeasuresRW2')
ph = analyse_data('MeasuresPH')
ph2 = analyse_data('MeasuresPH2')
ts = analyse_data('MeasuresTS')
tts = analyse_data('MeasuresTTS')

plt.style.use('ggplot')

fig1 = plt.figure()
plt.errorbar(np.arange(1,9,1),pc[0], yerr = pc[1], capsize = 3, barsabove = True, label = 'Stock Implementation')
plt.errorbar(np.arange(1,9,1),pc2[0], yerr = pc2[1], capsize = 3, barsabove = True, label = 'ASM Code')
plt.ylim(0,4)
plt.title('Producer-Consumer')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/PC.pdf")
plt.show()
plt.close()

fig2 = plt.figure()
plt.errorbar(np.arange(1,9,1),rw[0], yerr = rw[1], capsize = 3, barsabove = True, label = 'Stock Implementation')
plt.errorbar(np.arange(1,9,1),rw2[0], yerr = rw2[1], capsize = 3, barsabove = True, label = 'ASM Code')
plt.ylim(0,4)
plt.title('Reader-Writer')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/RW.pdf")
plt.show()
plt.close()

fig3 = plt.figure()
plt.errorbar(np.arange(1,9,1),ph[0], yerr = ph[1], capsize = 3, barsabove = True, label = 'Stock Implementation')
plt.errorbar(np.arange(1,9,1),ph2[0], yerr = ph2[1], capsize = 3, barsabove = True, label = 'ASM Code')
plt.ylim(0,3)
plt.title('Philosophe')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/PH.pdf")
plt.show()
plt.close()


fig4 = plt.figure()
plt.errorbar(np.arange(1,9,1),ts[0], yerr = ts[1], capsize = 3, barsabove = True, label = 'Test and Set')
plt.errorbar(np.arange(1,9,1),tts[0], yerr = tts[1], capsize = 3, barsabove = True, label = 'Test and Test and Set')
plt.ylim(0,4.5)
plt.title('Mutexes Analysis')
plt.ylabel('Temps de compilation [S]')
plt.xlabel('Nombre de threads')
plt.legend(loc = 'upper right')
plt.savefig("Measures/TS&TTS.pdf")
plt.show()
plt.close()
