import numpy as np

def func(x):
    return (1/np.sqrt(2*np.pi)) * np.exp(-(x**2)/2)

def trapezoidal_rule(xa, xb, N):
    h = (xb - xa) / N
    y = [0.0 for i in range(N+1)]
    for i in range(N+1):
        x = xa + h * i
        y[i] = func(x)
    temp = 0.0
    for i in range(1, N):
        temp += 2 * y[i]
    S = (y[0] + temp + y[N]) * h / 2.0
    return S

if __name__ == '__main__':
    N = 100
    xa = -5.0
    xb = 5.0

    S = trapezoidal_rule(xa, xb, N)
    print('S =', S)
