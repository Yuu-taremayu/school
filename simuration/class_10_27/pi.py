import random

def generate_point(times):
    dataX = []
    dataY = []
    for i in range(times):
        dataX.append(random.random())
        dataY.append(random.random())
    return dataX, dataY

def count_point(dataX, dataY):
    cnt = 0
    for x, y in zip(dataX, dataY):
        if x ** 2 + y ** 2 < 1:
            cnt += 1
    return cnt

def main():
    random.seed(0)
    times = 1000000000

    dataX, dataY = generate_point(times)
    cnt = count_point(dataX, dataY)
    print(4 * (cnt / times))

if __name__ == '__main__':
    main()
