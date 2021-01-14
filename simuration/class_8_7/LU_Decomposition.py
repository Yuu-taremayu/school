import numpy as np
import pandas as pd

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

    print(L)
    print(U)
    print()

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

if __name__ == '__main__':

    A = np.array([[2, 4, 6], [1, 5, 15], [4, 10, 21]], dtype=float)
    b = np.array([20, 28, 53], dtype=float)

    # read csv files
    #A = pd.read_csv('A100.csv', header=None)
    #b = pd.read_csv('b100.csv', header=None)
    #A = pd.read_csv('A1000.csv', header=None)
    #b = pd.read_csv('b1000.csv', header=None)

    # convert to ndarray from dataframe
    A = np.array(A)
    b = np.array(b)
    print(A)
    print(b)

    L, U = LU_Decomposition(A)
    x = calc_matrix(L, U, b)

    print(x)
    print(A*x)
