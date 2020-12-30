import numpy as np
import matplotlib.pyplot as plt

def func(_x):
    return 1 / (1 + 25 * (_x ** 2))

def lagrange(_x, _dataX, _dataY):
    l = 0
    L = 0
    for i in range(len(_dataX)):
        l = base(i, _x, _dataX) / base(i, _dataX[i], _dataX)
        L += _dataY[i] * l
    return L

def base(_i, _x, _dataX):
    l = 1
    for k in range(len(_dataX)):
        if _i != k:
            l *= _x - _dataX[k]
    return l

def main():
    xa = -1.0
    xb = 1.0

    step = (xb - xa) / 1000
    x = np.arange(xa, xb + step, step)
    y = func(x)

    step = (xb - xa) / 4
    dataX1 = np.arange(xa, xb + step, step)
    dataY1 = func(dataX1)
    L1 = lagrange(x, dataX1, dataY1)

    step = (xb - xa) / 10
    dataX2 = np.arange(xa, xb + step, step)
    dataY2 = func(dataX2)
    L2 = lagrange(x, dataX2, dataY2)
    
    step = (xb - xa) / 20
    dataX3 = np.arange(xa, xb + step, step)
    dataY3 = func(dataX3)
    L3 = lagrange(x, dataX3, dataY3)

    plt.subplot(411)
    plt.plot(x, y, label="orig")
    plt.legend()
    plt.subplot(412)
    plt.plot(x, L1, label='data = 5')
    plt.legend()
    plt.subplot(413)
    plt.plot(x, L2, label='data = 10')
    plt.legend()
    plt.subplot(414)
    plt.plot(x, L3, label='data = 20')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    main()
