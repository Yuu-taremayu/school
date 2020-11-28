def func(x):
    return 4*(x**3) - 10*(x**2) + 4*x + 5

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
    xa = 0.0
    xb = 2.0

    S = simpsons_rule(xa, xb, N)
    print('S =', S)
