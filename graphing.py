#!/usr/bin/env python3


import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

#def analyse_data (filename):

MeasuresPC = pd.read_csv('Measures/MeasuresPC.csv',header=None).T

print (MeasuresPC)