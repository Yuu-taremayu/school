import numpy as np
import random
import matplotlib.pyplot as plt

N = 51200
x = np.arange(N)
y1 = np.zeros(N)
y2 = np.zeros(N)

for i in range(N):
    y1[i] = random.uniform(-2, 0)

for i in range(N):
    y2[i] = random.uniform(-2, 0)

y1_ave = np.mean(y1)
y1_ave = np.ones(N) * y1_ave
y_ave = np.mean(y1 + y2)
y_ave = np.ones(N) * y_ave

plt.subplot(211)
plt.plot(x, y1)
plt.plot(x, y1_ave, label="y1 average")
plt.legend()
plt.subplot(212)
plt.plot(x, y1)
plt.plot(x, y2)
plt.plot(x, y_ave, label="y1+y2 average")
plt.legend()
plt.show()
