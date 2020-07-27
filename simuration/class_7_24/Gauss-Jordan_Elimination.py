import numpy as np
import pandas as pd

def Gauss_Jordan_Elimination(X, N):
    cnt = 0
    # k repeats to row direction
    for k in range(N):

        # j repeats to column direction
        for j in range(k + 1, N + 1):
            X[k][j] = X[k][j] / X[k][k]

            # i repeats to row direction
            # become 0 except [k][k]element
            for i in range(N):
                if i != k:
                    X[i][j] = X[i][j] - X[k][j] * X[i][k]
                    cnt += 1
    return X, cnt

if __name__ == '__main__':

    #A = np.array([[2, 3, 4], [3, 5, 2], [4, 3, 30]], dtype=float)
    #B = np.array([[6], [5], [32]], dtype=float)

    #A = pd.read_csv('A100.csv', header=None)
    #B = pd.read_csv('b100.csv', header=None)
    A = pd.read_csv('A1000.csv', header=None)
    B = pd.read_csv('b1000.csv', header=None)

    # prepare matrix for calculation
    A = np.array(A)
    B = np.array(B)
    X = np.hstack([A, B])
    N = len(X)

    X, cnt = Gauss_Jordan_Elimination(X, N)

    for i in range(N):
        print(f'x_{i + 1} = {X[i][N]}')
    print(f'count = {cnt}')
