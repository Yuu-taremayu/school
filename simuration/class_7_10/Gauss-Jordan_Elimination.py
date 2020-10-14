import numpy as np

def Gauss_Jordan_Elimination(X):
    # declare dimension
    N = 3

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
    return X

if __name__ == '__main__':

    #A = np.array([[2, 3, 4], [3, 5, 2], [4, 3, 30]], dtype=float)
    #B = np.array([[6], [5], [32]], dtype=float)
    A = np.array([[7, 1, 2], [1, 8, 3], [2, 3, 9]], dtype=float)
    B = np.array([[10], [8], [6]], dtype=float)

    # prepare matrix for calculation
    X = np.hstack([A, B])
    print(X)

    X = Gauss_Jordan_Elimination(X)

    print(f'x1 = {X[0][3]}, x2 = {X[1][3]}, x3 = {X[2][3]}')
    print(X)
