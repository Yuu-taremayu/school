import numpy as np

def func(x):
   return (1/np.sqrt(2*np.pi)) * np.exp(-(x**2)/2)

def generate_random(a, b, maxY, t):
    dataX = []
    dataY = []
    dataX = np.random.rand(t) * (b - a) + a
    dataY = np.random.rand(t) * maxY
    return dataX, dataY

def montecarlo(t, dataX, dataY):
    cnt = 0
    for i in range(len(dataX)):
        if func(dataX[i]) >= dataY[i]:
            cnt += 1
    p = float(cnt) / float(t)
    return p

if __name__ == '__main__':
    t = 1000000
    a = -5
    b = 5
    maxY = 2
    cnt = 0

    dataX, dataY = generate_random(a, b, maxY, t)
    p = montecarlo(t, dataX, dataY)
    print('S =', (b-a) * maxY * p)
