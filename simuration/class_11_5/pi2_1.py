def generate_point(times):
    dataX = LCGs(times, 1)
    dataX = [i / 2**32 for i in dataX]
    dataY = LCGs(times, 2)
    dataY = [i / 2**32 for i in dataY]
    return dataX, dataY

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

def count_point(dataX, dataY):
    cnt = 0
    for x, y in zip(dataX, dataY):
        if x**2 + y**2 < 1:
            cnt += 1
    return cnt

def main():
    times = 100000

    dataX, dataY = generate_point(times)
    cnt = count_point(dataX, dataY)
    print('pi =', 4 * cnt / times)

if __name__ == '__main__':
    main()
