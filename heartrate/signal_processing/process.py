# -*- coding: utf-8 -*-
"""
Created on Wed Mar 11 12:48:09 2020

@author: 2489492w
"""

import numpy as np
import scipy.signal as ss
import matplotlib.pyplot as plt
from FIR_filter import myFIR_filter

fs = 1600
f1 = 95
f2 = 105

b = ss.firwin(1599,[f1/fs*2,f2/fs*2], pass_zero = False);



plt.close("all")
A = np.loadtxt('ads_data.txt')

plt.figure(11)
plt.plot (A)
plt.title('V')
plt.xlabel('Time (s)')
plt.show(block = True)

input_array = A
#by examining the three plots of the input values, X was chosen as having the best signal pre-filtering

plt.figure(22)
plt.plot(np.linspace(0,1600,len(input_array)),np.abs(np.fft.fft(input_array)))
plt.title('Original ECG in Frequency Domain')
plt.xlabel('Frequency (Hz)')
plt.show(block = True)

#Fs = 1600 #sampling frequency of ecg
#M = 3201 #number of taps (2*Fs+1)
##f1 = int ((95/Fs)*M) #lower limit to filter 50 Hz
##f2 = int ((105/Fs)*M) #upper limit to filter 50 Hz
#f3 = int((0/Fs)*M) #lower limit to filter DC
#f4 = int((1/Fs)*M) #upper limit to filter DC
#
##to filter, use a bandpass filter where value is one except within limits found above
#H = np.ones(M)
##H[f1:f2+1] = 0
##H[M-f2:M-f1+1] = 0 #impulse function must be symmetrical
#H[f3:f4+1] = 0
#H[M-f4:M] = 0 #impulse function must be symmetrical
#
##plt.figure()
##plt.scatter(np.linspace(0,len(H),len(H)),H)
#
##to find the coefficients, take ifft of bandpass (bandpass in frequency domain, needs to be in time domain)
#h = np.fft.ifft(H)
#h = np.real(h)
#
##finally, the coefficients must be mirrored
#hh = np.zeros(len(h))
#hh[0:1601] = h[1600:3201]
#hh[1601:3201] = h[0:1600]

#plt.figure()
#plt.scatter(np.linspace(0,len(hh),len(hh)), hh)

fir = myFIR_filter(b)
output_array = np.zeros(len(input_array))
for i in range (len(input_array)):
    output_array[i] = fir.dofilter(input_array[i])

plt.figure(111)
plt.plot(output_array)
plt.title('Filtered ECG in Time Domain')
plt.xlabel('Time (s)')
plt.show(block = True)

plt.figure(222)
plt.plot(np.linspace(0,1600,len(output_array)),np.abs(np.fft.fft(output_array)))
plt.title('Filtered ECG in Frequency Domain')
plt.xlabel('Frequency (Hz)')
plt.show(block = True)