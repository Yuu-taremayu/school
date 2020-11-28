import numpy as np
import matplotlib.pyplot as plt

def generate_bit(N):
    bit = []
    for i in range(N):
        r = np.random.randint(10000) % 2
        bit.append(r)
    return bit

def bit_to_signal(bit):
    signal = []
    for i in bit:
        signal.extend([i]*len(bit))
    return signal

def manchester_code(bit):
    mc = []
    for i in bit:
        if i == 0:
            mc.extend([1, 0])
        else:
            mc.extend([0, 1])
    return mc

def mlt_3_4b5b(bit):
    conv_bit = []
    for i in range(0, len(bit), 4):
        t = bit[i]*8 + bit[i+1]*4 + bit[i+2]*2 + bit[i+3]
        if t == 0b0000:
            conv_bit.extend([1, 1, 1, 1, 0])
        elif t == 0b0001:
            conv_bit.extend([0, 1, 0, 0, 1])
        elif t == 0b0010:
            conv_bit.extend([1, 0, 1, 0, 0])
        elif t == 0b0011:
            conv_bit.extend([1, 0, 1, 0, 1])
        elif t == 0b0100:
            conv_bit.extend([0, 1, 0, 1, 0])
        elif t == 0b0101:
            conv_bit.extend([0, 1, 0, 1, 1])
        elif t == 0b0110:
            conv_bit.extend([0, 1, 1, 1, 0])
        elif t == 0b0111:
            conv_bit.extend([0, 1, 1, 1, 1])
        elif t == 0b1000:
            conv_bit.extend([1, 0, 0, 1, 0])
        elif t == 0b1001:
            conv_bit.extend([1, 0, 0, 1, 1])
        elif t == 0b1010:
            conv_bit.extend([1, 0, 1, 1, 0])
        elif t == 0b1011:
            conv_bit.extend([1, 0, 1, 1, 1])
        elif t == 0b1100:
            conv_bit.extend([1, 1, 0, 1, 0])
        elif t == 0b1101:
            conv_bit.extend([1, 1, 0, 1, 1])
        elif t == 0b1110:
            conv_bit.extend([1, 1, 1, 0, 0])
        elif t == 0b1111:
            conv_bit.extend([1, 1, 1, 0, 1])

    conv_signal = []
    level = 1
    level_prev = 0
    for i in range(len(conv_bit)):
        if conv_bit[i] == 1:
            if level == 1:
                level = 0
                level_prev = 1
                conv_signal.append(1)
            elif level == 0:
                if level_prev == -1:
                    level = 1
                    level_prev = 0
                elif level_prev == 1:
                    level = -1
                    level_prev = 0
                conv_signal.append(0)
            elif level == -1:
                level = 0
                level_prev = -1
                conv_signal.append(-1)
        else:
            if i == 0:
                conv_signal.append(0)
            else:
                conv_signal.append(conv_signal[i-1])
    return conv_signal

if __name__ == '__main__':
    N = 4*16

    bit = generate_bit(N)
    mc = manchester_code(bit)
    mlt = mlt_3_4b5b(bit)

    '''
    bit = bit_to_signal(bit)
    mc = bit_to_signal(mc)
    mlt = bit_to_signal(mlt)

    plt.subplot(311)
    plt.plot(range(len(bit)), bit)
    plt.subplot(312)
    plt.plot(range(len(mc)), mc)
    plt.subplot(313)
    plt.plot(range(len(mlt)), mlt)
    plt.show()
    '''

    F_mc = np.fft.fftshift(mc)
    F_mc = np.fft.fft(F_mc)
    F_mc = np.fft.fftshift(F_mc)
    F_mlt = np.fft.fftshift(mlt)
    F_mlt = np.fft.fft(F_mlt)
    F_mlt = np.fft.fftshift(F_mlt)

    plt.subplot(211)
    plt.plot(range(len(F_mc)), F_mc)
    plt.subplot(212)
    plt.plot(range(len(F_mlt)), F_mlt)
    plt.show()
