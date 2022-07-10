import numpy as np #rename the numpy library
import matplotlib.pyplot as plt #rename matplotlib


filename = 'C:/Users/jovan/OneDrive/Desktop/period.txt' #name of some file with results, in tihis case excel file

results = np.loadtxt(filename, skiprows=1) #variabla results load this file and remove unnecessary rows, make useful matrix

print (results.shape)

cols = results.shape[1]

x = results[:, 0]
y = results[:, 1:cols]


for curve in range(y.shape[1]):
    plt.plot (x, y[:, curve])

plt.show()



