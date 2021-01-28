import numpy as np
import matplotlib.pyplot as plt

def spline1(_dataX, _dataY):
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

def main():
    dataX = np.array([1, 2, 3, 4])
    dataY = np.array([9, 4, 6, 3])

    a, b, c, d = spline1(dataX, dataY)

    sampleX = np.arange(1, 4.1, 0.1)

    y = np.zeros(len(sampleX))
    index = 0
    for i in range(len(sampleX)):
        x = sampleX[i]
        if x >= dataX[index + 1] and index < len(dataX) - 2:
            index += 1
        y[i] = a[index] * (x - dataX[index]) ** 3 + b[index] * (x - dataX[index]) ** 2 + c[index] * (x - dataX[index]) + d[index]

    plt.scatter(dataX, dataY)
    plt.plot(sampleX, y)
    plt.show()
    
if __name__ == '__main__':
    main()
