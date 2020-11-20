#!/usr/bin/env python3


import matplotlib.pyplot as plt
import numpy as np

import pandas as pd

fig1 = plt.figure()

testx = pd.read_csv('Measures/measurespc.csv',names=['NB_THREADS','TIME_1','TIME_2','TIME_3','TIME_4','TIME_5'])


T_y = []
T_XX = [0, 0, 0, 0, 0, 0]
for i in range(1, 5, 1):
	data = []
	data_x = []
	for j in range(1, 5, 1):
		data_x.append(testx['TIME_'+str(i)][j])
	T_XX[i] = np.array(data_x).astype(np.float)
	for j in range(1, 6, 1):
		data.append(testx['TIME_'+str(j)][i])
	T_y.append(np.mean(np.array(data).astype(np.float)))
data_x = []
for i in range(1, 5, 1):
	data_x.append(testx['TIME_'+str(5)][i])
T_XX[5] = np.array(data_x).astype(np.float)	

# Les mois correspondant
M = [2, 4, 8, 16]



plt.plot(M, T_XX[1], color="yellow", linewidth=1.0, linestyle="--")

plt.plot(M, T_XX[2], color="orange", linewidth=1.0, linestyle="-.")

plt.plot(M, T_XX[3], color="lime", linewidth=1.0, linestyle=":")

plt.plot(M, T_XX[4], color="blue", linewidth=1.0, linestyle="--")
plt.plot(M, T_XX[5], color="brown", linewidth=1.0, linestyle="dashed")

plt.plot(M, T_y, color="red", linewidth=1.3, linestyle="-")


# Limiter le range de valeurs affichées pour l'axe des x
plt.xlim(0,17)

# Forcer la graduation en y. np.linspace découpe l'intervalle [1,12] en parties égales
# Il renvoie 12 graduations [1,2,3...12]. (peut aussi être fait manuellement)
plt.xticks(np.linspace(1,12,12))

# Donner un label à l'axe x
plt.xlabel('Nombre de threads')

# Limiter le range de valeur affiché pour y
plt.ylim(0,2)

# Forcer la graduation en y. np.linspace découpe l'intervalle [0,30] en parties égales et renvoie 7 graduations (5 graduations + 2 pour '0' et '30')
plt.yticks(np.linspace(0,2,8))
plt.xticks(np.linspace(0,16,9))

# Donner un label à l'axe y
plt.ylabel('Temps de compilation [S]')

# Donner un titre à votre graphe.
plt.title('Measures Producer Consumer')

# Permet d'ajouter une grille au graphe, rendant la lecture de vos données plus facile.
plt.grid(True)

# Ajouter une légende, loc peut prendre différentes valeurs (https://matplotlib.org/3.1.1/api/_as_gen/matplotlib.pyplot.legend.html)
plt.legend(['TEST_1','TEST_2','TEST_3','TEST_4','TEST_5','Moyenne'], loc = 'upper right')

# on enregistre le graphique. L'extension est directement déduite du nom donné en argument (png par défault).
plt.savefig("Exemple.png")
plt.savefig("Exemple.pdf")

# Optionnel : on affiche le graphe à l'écran (note: show est un appel bloquant, tant que le graphe n'est pas fermé, on est bloqué)
plt.show()

# On ferme proprement le plot.
plt.close()
