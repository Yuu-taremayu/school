from JacobiMethod import Jacobi_method
from GaussSeidelMethod import GaussSeidel_method
import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':
    x0 = 0
    y0 = 0
    z0 = 0

    A = np.array([[7, 1, 2],
                [1, 8, 3],
                [2, 3, 9]], dtype=float)
    b = np.array([10, 8, 6], dtype=float)

    X1, Y1, Z1, cnt1 = Jacobi_method(x0, y0, z0, A, b)
    X2, Y2, Z2, cnt2 = GaussSeidel_method(x0, y0, z0, A, b)

    plt.plot(range(len(X1)), X1, label='Jacobi')
    plt.plot(range(len(X2)), X2, label='Gauss-Seidel')
    plt.legend()
    plt.show()
