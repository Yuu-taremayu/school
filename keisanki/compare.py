import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

mypc_size = pd.read_csv('mypc.csv', sep='\t', usecols=['size(KB)'])
mypc_time = pd.read_csv('mypc.csv', sep='\t', usecols=['time(s)'])
jes_size = pd.read_csv('jes.csv', sep='\t', usecols=['size(KB)'])
jes_time = pd.read_csv('jes.csv', sep='\t', usecols=['time(s)'])

mypc_size = np.array(mypc_size)
mypc_time = np.array(mypc_time)
jes_size = np.array(jes_size)
jes_time = np.array(jes_time)

plt.plot(mypc_size, mypc_time, label='myPC')
plt.plot(jes_size, jes_time, label='jes')
plt.xscale('log')

plt.legend()
plt.show()
