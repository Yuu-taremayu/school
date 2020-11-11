def LCGs(num, seed):
    A = 1664525
    C = 1103515245
    M = 2**32
    x = seed
    r_list = []
    for i in range(num):
        x = (A * x + C) % M
        r_list.append(x)
    return r_list

if __name__ == '__main__':
    r_list = LCGs(10, 1)
    r_float_list = [i / 2**32 for i in r_list]
    print(r_list)
    print(r_float_list)
