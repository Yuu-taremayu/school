import numpy as np

def GaussSeidel_method(x0, y0, z0, A, b):
    EPSILON = 1.0e-7
    x_t = x0
    y_t = y0
    z_t = z0
    cnt = 0
    
    x = 0
    y = 0
    z = 0
    
    X = [x]
    Y = [y]
    Z = [z]

    '''
    for i in range(20):
        x = (b[0] - (A[0][1] * y + A[0][2] * z)) / A[0][0]
        y = (b[1] - (A[1][0] * x + A[1][2] * z)) / A[1][1]
        z = (b[2] - (A[2][0] * x + A[2][1] * y)) / A[2][2]
        X.append(x)
        Y.append(y)
        Z.append(z)
        x_t = x
        y_t = y
        z_t = z
    '''

    while True:
        cnt += 1
        x = (b[0] - (A[0][1] * y + A[0][2] * z)) / A[0][0]
        y = (b[1] - (A[1][0] * x + A[1][2] * z)) / A[1][1]
        z = (b[2] - (A[2][0] * x + A[2][1] * y)) / A[2][2]
        X.append(x)
        Y.append(y)
        Z.append(z)
        print(f'x={x}, y={y}, z={z} / count={cnt}')
        if np.abs(x - x_t) < EPSILON and np.abs(y - y_t) < EPSILON and np.abs(z - z_t) < EPSILON:
            break
        x_t = x
        y_t = y
        z_t = z
    print(f'calc {cnt} times.')

    return X, Y, Z, cnt

if __name__ == '__main__':
    
    A = np.array([[7, 1, 2],
                [1, 8, 3],
                [2, 3, 9]], dtype=float)
    b = np.array([10, 8, 6], dtype=float)

    x0 = 0
    y0 = 0
    z0 = 0

    X, Y, Z, cnt = GaussSeidel_method(x0, y0, z0, A, b)
