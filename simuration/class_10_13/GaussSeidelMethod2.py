import numpy as np

def GaussSeidel_method(A, b, x_init):
    EPSILON = 1.0e-7
    x_t = x_init
    size = len(x_t)
    flag = 0
    cnt = 0

    x = np.zeros(size, dtype=float)
    
    '''
    for time in range(10):
        for i in range(size):
            s = 0
            for j in range(size):
                if i != j:
                    s += A[i][j] * x[j]
            x[i] = (b[i] - s) / A[i][i]
        for i in range(size):
            x_t[i] = x[i]
    '''

    while True:
        cnt += 1
        #
        # calculation
        #
        for i in range(size):
            s = 0
            for j in range(size):
                if i != j:
                    s += A[i][j] * x[j]
            x[i] = (b[i] - s) / A[i][i]
        #
        # Exit conditions
        #
        flag = 0
        for i in range(size):
            if np.abs(x[i] - x_t[i]) < EPSILON:
                flag += 1
        if flag == size:
            break
        #
        # update value
        #
        for i in range(size):
            x_t[i] = x[i]
    print(f'calc {cnt} times.')

    return x

if __name__ == '__main__':
    A = np.array([[7, 1, 2],
                [1, 8, 3],
                [2, 3, 9]], dtype=float)
    b = np.array([10, 8, 6], dtype=float)
    x_init = np.array([0, 0, 0], dtype=float)

    x = GaussSeidel_method(A, b, x_init)

    for i in range(len(x)):
        print(f'x[{i}] = {x[i]}')
