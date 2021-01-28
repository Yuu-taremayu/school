import numpy as np
import matplotlib.pyplot as plt

def func(_x):
    return 1 / (1 + 25 * (_x ** 2))

def spline(_dataX, _dataY):
    N = len(_dataX)
    h = np.zeros(N - 1)
    for i in range(N - 1):
        h[i] = _dataX[i + 1] - _dataX[i]

    A = np.zeros((N - 2, N - 2))
    for i in range(N - 2):
        for j in range(N - 2):
            if i == j:
                A[i][j] = 2 * (h[j - 1] + h[j])
            elif i == j - 1 or i == j + 1:
                A[i][j] = h[j]

    u = np.zeros(N - 2)
    v = np.zeros(N - 2)
    for i in range(1, N - 1):
        v[i - 1] = 6 * (((_dataY[i + 1] - _dataY[i]) / h[i]) - ((_dataY[i] - _dataY[i - 1]) / h[i - 1]))

    L, U = LU_Decomposition(A)
    u = calc_matrix(L, U, v)

    a = np.zeros(N - 1)
    b = np.zeros(N - 1)
    c = np.zeros(N - 1)
    d = np.zeros(N - 1)

    u = np.append(0, u)
    u = np.append(u, 0)

    for i in range(N - 1):
        a[i] = (u[i + 1] - u[i]) / (6 * (_dataX[i + 1] - _dataX[i]))
        b[i] = u[i] / 2
        c[i] = ((_dataY[i + 1] - _dataY[i]) / (_dataX[i + 1] - _dataX[i])) - (((_dataX[i + 1] - _dataX[i]) * (2 * u[i] + u[i + 1])) / 6)
        d[i] = _dataY[i]

    return a, b, c, d

def LU_Decomposition(A):
    N = len(A)

    L = np.eye(N, N, 0, dtype=float)
    U = np.zeros((N, N), dtype=float)

    # LU Decomposition
    # A = LU
    # variable i processes to row direction
    for i in range(N):
        # variable j processes to column direction
        # process for Lower triangular matrix
        for j in range(i):
            if j == 0:
                L[i][j] = A[i][j] / U[j][j]
            else:
                temp = 0.0
                for k in range(j):
                    temp += L[i][k] * U[k][j]
                L[i][j] = (A[i][j] - temp) / U[j][j]
        # process for Upper triangular matrix
        for j in range(i, N):
            if i == 0:
                U[i][j] = A[i][j]
            else:
                temp = 0.0
                for k in range(i):
                    temp += L[i][k] * U[k][j]
                U[i][j] = A[i][j] - temp

    return L, U

def calc_matrix(L, U, b):
    N = len(L)
    
    x = np.zeros(N, dtype=float)
    y = np.zeros(N, dtype=float)

    # Ly = b
    # process for y vector
    for i in range(N):
        temp = 0.0
        for j in range(i):
            temp += L[i][j] * y[j]
        y[i] = b[i] - temp
    
    # Ux = y
    # process for x vector(solution)
    for i in reversed(range(N)):
        temp = 0.0
        for j in reversed(range(N - i)):
            temp += U[i][N - 1 - j] * x[N - 1 - j]
        x[i] = (y[i] - temp) / U[i][i]

    return x

def sampling(_a, _b, _c, _d, _sampleX, _dataX):
    y = np.zeros(len(_sampleX))
    index = 0
    for i in range(len(_sampleX)):
        x = _sampleX[i]
        if x >= _dataX[index + 1] and index < len(_dataX) - 2:
            index += 1
        y[i] = _a[index] * (x - _dataX[index]) ** 3 + _b[index] * (x - _dataX[index]) ** 2 + _c[index] * (x - _dataX[index]) + _d[index]

    return y

def main():
    xa = -1.0
    xb = 1.0

    step = (xb - xa) / 1000
    sampleX = np.arange(xa, xb + step, step)
    y = func(sampleX)

    step = (xb - xa) / 4
    dataX1 = np.arange(xa, xb + step, step)
    dataY1 = func(dataX1)
    a1, b1, c1, d1 = spline(dataX1, dataY1)
    y1 = sampling(a1, b1, c1, d1, sampleX, dataX1)

    step = (xb - xa) / 10
    dataX2 = np.arange(xa, xb + step, step)
    dataY2 = func(dataX2)
    a2, b2, c2, d2 = spline(dataX2, dataY2)
    y2 = sampling(a2, b2, c2, d2, sampleX, dataX2)
    
    step = (xb - xa) / 20
    dataX3 = np.arange(xa, xb + step, step)
    dataY3 = func(dataX3)
    a, b, c, d = spline(dataX3, dataY3)
    y3 = sampling(a, b, c, d, sampleX, dataX3)

    plt.subplot(411)
    plt.plot(sampleX, y, label="orig")
    plt.legend()
    plt.subplot(412)
    plt.scatter(dataX1, dataY1)
    plt.plot(sampleX, y1, label='data = 5')
    plt.legend()
    plt.subplot(413)
    plt.scatter(dataX2, dataY2)
    plt.plot(sampleX, y2, label='data = 11')
    plt.legend()
    plt.subplot(414)
    plt.scatter(dataX3, dataY3)
    plt.plot(sampleX, y3, label='data = 21')
    plt.legend()
    plt.show()
    
if __name__ == '__main__':
    main()
