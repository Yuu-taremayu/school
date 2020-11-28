def func(x):
    return 4*(x**3) - 10*(x**2) + 4*x + 5

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
    xa = 0.0
    xb = 2.0

    S = trapezoidal_rule(xa, xb, N)
    print('S =', S)
