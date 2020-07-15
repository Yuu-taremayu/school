import numpy as np

def define_matrix(A, B):
    N = int(input('Input dimension number of coefficient matrix:'))

    temp = 0
    temp_mat = np.empty(0)
    for i in range(N):
        for j in range(N):
            temp = float(input(f'Input [{i + 1}][{j + 1}]element:'))
            np.hstack(temp_mat, temp)
        np.vstack(A, temp_mat)
        temp_mat = np.array()

    print(A)

    for i in range(N):
        pass


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

    A = np.empty(0)
    B = np.empty(0)

    '''
    A = np.array([[2, 3, 4], [3, 5, 2], [4, 3, 30]], dtype=float)
    B = np.array([[6], [5], [32]], dtype=float)
    '''

    define_matrix(A, B)
    # prepare matrix for calculation
    X = np.hstack([A, B])
    print(X)

    X = Gauss_Jordan_Elimination(X)

    print(f'x1 = {X[0][3]}, x2 = {X[1][3]}, x3 = {X[2][3]}')
    print(X)
