import Signal

import matplotlib.pyplot as plt
import math
import numpy

def graph_signals(time, array):
    plt.plot(time, array[0], 'r-', time, array[1], 'g-', time, array[2], 'b-', time, array[3], 'k-')

    plt.xlabel('Time (ms)')
    plt.ylabel('Charge (arbitrary)')
    plt.show()

def main():
    d = 20 #m
    angle = 1.8 #rad
    freq = 30 #kHz
    sos = 1.5 #m/ms
    sr = 1000 #kHz
    read = 0.1 #ms
    noise = 1 #standard deviation
    signals = Signal.Signal(d, angle, freq, sos, sr, read, noise).signals
    times = numpy.arange(0, read, 1/sr)

    for sig in signals:
        print(sig)

    graph_signals(times, signals)

main()
