# Occam Kelly Graves
# 2019-09-15
import math
import numpy
import random

ARRAY_SEPARATION = 0.01 # distance between centers of sensors (m)
NUM_SENSORS = 4

def calc_distance(sensor_num, side1, angle):
    side2 = abs(1.5 - sensor_num) * ARRAY_SEPARATION
    if(sensor_num < 1.5):
        angle = math.pi - angle
    return math.sqrt(side1**2 + side2**2 - 2 * side1 * side2 * math.cos(angle))

def calc_sine(distance, time, frequency, sound_speed, amplitude):
    tot_time = distance / sound_speed + time
    return amplitude * math.sin(2 * math.pi * frequency * tot_time)

def add_noise(noise, signal):
    noise_array = numpy.random.normal(0, noise, len(signal))
    noise_signal = []
    for i in range(len(signal)):
        noise_signal.append(signal[i] + noise_array[i])
    return noise_signal

class Signal:
    #                        source
    #                         /
    #              distance /
    #                     /
    #                   /
    #                 / angle
    # sensors  *   *   *   *
    #   index: 0   1   2   3
    def __init__(self, distance, angle, frequency, sound_speed, sample_rate, read_time, noise):
        self.distance = distance #m
        self.angle = angle #rad between 0 and pi
        self.frequency = frequency #kHz
        self.sound_speed = sound_speed #m/ms
        self.sample_rate = sample_rate #kHz
        self.read_time = read_time #ms
        self.noise = noise #standard deviation

        self.signals = self.generate_signals()

    def generate_signals(self):
        signals = []
        for i in range(4):
            signal = []
            distance = calc_distance(i, self.distance, self.angle)
            echo_length = random.random() * 100
            echo_amp = random.uniform(0.7, 0.9)
            for j in range(math.floor(self.sample_rate * self.read_time)):
                sig = calc_sine(distance, j / self.sample_rate, self.frequency,
                  self.sound_speed, 1)
                echo_sig = calc_sine(distance + echo_length, j / self.sample_rate,
                  self.frequency, self.sound_speed, echo_amp)
                signal.append(sig) #+ echo_sig)
            signals.append(add_noise(self.noise, signal))
        return signals
