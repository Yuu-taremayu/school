import numpy as np
import matplotlib.pyplot as plt

def generate_bit(N):
    bit = []
    for i in range(N):
        r = np.random.randint(0, 2)
        bit.append(r)
    return bit

def generate_signal(bit, N):
    signal = []
    for i in bit:
        if i == 0:
            signal.extend([1] * N)
        else:
            signal.extend([-1] * N)
    return signal

def psk_mod(bit, t, N, freq_c):
    psk_signal = []
    wave_1 = np.cos(2*np.pi*t*freq_c/N)
    wave_minus1 = np.cos((2*np.pi*t*freq_c/N)+np.pi)
    for i in bit:
        if i == 0:
            psk_signal.extend(wave_minus1)
        else:
            psk_signal.extend(wave_1)
    psk_signal = np.array(psk_signal)
    return psk_signal


def psk_demod(psk_signal, demo_wave, t, N, freq_c):
    demod_signal = []
    demo_signal = demo_wave * psk_signal
    demo_signal = highpass_filter(demo_signal, bit, freq_c)
    return demo_signal

def generate_demo_wave(bit):
    sample = np.cos(2*np.pi*t*freq_c/N)
    demo_wave = []
    for i in bit:
        demo_wave.extend(sample)
    demo_wave = np.array(demo_wave)
    return demo_wave

def highpass_filter(demo_signal, bit, freq_c):
    length = len(demo_signal)
    length_2 = int(length / 2)
    F = np.fft.fftshift(demo_signal)
    F = np.fft.fft(F)
    F = np.fft.fftshift(F)
    filtering_freq = freq_c
    spectrum = filtering_freq * len(bit)
    F[0:length_2 - spectrum] = 0
    F[length_2 + spectrum:-1] = 0
    demo_signal = np.fft.fftshift(F)
    demo_signal = np.fft.ifft(demo_signal)
    demo_signal = np.fft.fftshift(demo_signal)
    return demo_signal

def pn_mod(psk_signal):
    pn = []
    for i in range(len(psk_signal)):
        r = np.random.randint(0, 2)
        if r == 0:
            pn.append(-1)
        else:
            pn.append(r)
    pn = np.array(pn)
    psk_pn_signal = psk_signal * pn
    psk_pn_signal = np.array(psk_pn_signal)
    return pn, psk_pn_signal

def pn_demod(pn, psk_pn_signal):
    psk_signal_demod = pn * psk_pn_signal
    psk_signal_demod = np.array(psk_signal_demod)
    return psk_signal_demod

if __name__ == '__main__':
    N = 64
    t = np.arange(0, N, 1)
    freq_c = 5

    bit = generate_bit(N)
    signal = generate_signal(bit, N)
    psk_signal = psk_mod(bit, t, N, freq_c)

    pn, psk_pn_signal = pn_mod(psk_signal)
    psk_signal_demod = pn_demod(pn, psk_pn_signal)

    demo_wave = generate_demo_wave(bit)
    demo_signal = psk_demod(psk_signal, demo_wave, t, N, freq_c)

    F1 = np.fft.fftshift(psk_signal)
    F1 = np.fft.fft(F1)
    F1 = np.fft.fftshift(F1)
    F2 = np.fft.fftshift(psk_pn_signal)
    F2 = np.fft.fft(F2)
    F2 = np.fft.fftshift(F2)
    F3 = np.fft.fftshift(psk_signal_demod)
    F3 = np.fft.fft(F3)
    F3 = np.fft.fftshift(F3)

    plt.subplot(311)
    plt.plot(range(len(F1)), F1)
    plt.subplot(312)
    plt.plot(range(len(F2)), F2)
    plt.subplot(313)
    plt.plot(range(len(F3)), F3)
    plt.show()
