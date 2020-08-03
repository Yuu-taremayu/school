import numpy as np
import pandas as pd

def Gaussian_Elimination(X, N):

    cnt = 0

    for k in range(N):

        for j in range(k + 1, N + 1):
            X[k][j] = X[k][j] / X[k][k]
            cnt += 1

            for i in range(k + 1, N):
                X[i][j] = X[i][j] - X[k][j] * X[i][k]
                cnt += 1

    x = np.zeros((1, N), dtype=float)
    for k in reversed(range(N)):
        x[0][k] = X[k][N]
        cnt += 1

        for j in range(k + 1, N):
            x[0][k] = x[0][k] - X[k][j] * x[0][j]
            cnt += 1

    return x, cnt

if __name__ == '__main__':
    # read csv file
    A = pd.read_csv('A100.csv', header=None)
    B = pd.read_csv('b100.csv', header=None)
    #A = pd.read_csv('A1000.csv', header=None)
    #B = pd.read_csv('b1000.csv', header=None)

    # convert to ndarray from dataframe
    A = np.array(A)
    B = np.array(B)

    X = np.hstack([A, B])
    N = len(X)

    x, cnt = Gaussian_Elimination(X, N)

    for i in range(N):
        print(f'x_{i + 1} = {x[0][i]}')
    print(f'count = {cnt}')
