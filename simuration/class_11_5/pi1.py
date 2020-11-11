import math

def leibniz():
    n = 1000000
    print('n =', n)
    s = 0.0
    for i in range(n+1):
        s += (-1)**i / ((2*i) + 1)
    pi = s * 4
    return pi

def machin():
    n = 10
    print('n =', n)
    num_1 = 0.0
    for i in range(3*n+2+1):
        num_1 += ((-1)**i / (2*i+1)) * ((1/5)**(2*i+1))
    num_1 = num_1 * 16
    num_2 = 0.0
    for i in range(n+1):
        num_2 += ((-1)**i / (2*i+1)) * ((1/239)**(2*i+1))
    num_2 = num_2 * 4
    pi = num_1 - num_2
    return pi

def ramanujan():
    n = 1
    print('n =', n)
    s = 0.0
    for i in range(n+1):
        temp1 = 1
        for j in reversed(range(1, 4*i+1)):
            temp1 *= j
        temp2 = 1
        for j in reversed(range(1, i+1)):
            temp2 *= j
        s += (temp1 * (1103+26390*i)) / (((4**i) * (99**i) * temp2))**4
    s = s * 2 * math.sqrt(2) / (99**2)
    pi = 1 / s
    return pi

if __name__ == '__main__':
    pi_1 = leibniz()
    print('leibniz:', pi_1)
    pi_2 = machin()
    print('machin:', pi_2)
    pi_3 = ramanujan()
    print('ramanujan:', pi_3)
