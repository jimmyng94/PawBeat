import numpy as np
import scipy.signal as ss

file = open("hr_coeff.txt","w+")

fs = 1600
f1 = 95
f2 = 105

b = ss.firwin(1599,[f1/fs*2,f2/fs*2]);

np.savetxt("hr_coeff.txt",b,newline = '\n')
