import numpy as np

def func(x):
    return (1/np.sqrt(2*np.pi)) * np.exp(-(x**2)/2)

def simpsons_rule(xa, xb, N):
    h = (xb-xa) / N
    y = [0.0 for i in range(N+1)]
    for i in range(N+1):
        x = xa + h * i
        y[i] = func(x)
    temp = 0.0
    for i in range(1, N):
        if i % 2 == 1:
            temp += 4 * y[i]
        else:
            temp += 2 * y[i]
    S = (y[0] + temp + y[N]) * h / 3
    return S

if __name__ == '__main__':
    N = 100
    xa = -5.0
    xb = 5.0

    S = simpsons_rule(xa, xb, N)
    print('S =', S)
