import numpy as np
import matplotlib.pyplot as plt

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
    dataX = np.array([1.0, 3.0, 4.0])
    dataY = np.array([1.0, 2.0, 5.0])

    x = np.arange(-1, 5, 0.01)
    y = lagrange(x, dataX, dataY)

    plt.plot(x, y)
    plt.show()

if __name__ == '__main__':
    main()
