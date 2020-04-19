import numpy as np
import scipy.signal as ss

file = open("hr_coeff.dat","w+")

fs = 120
f1 = 15


B = [f1/fs*2]

b = ss.firwin((fs*2+1),B,pass_zero = False)

np.savetxt("hr_coeff.dat",b,newline = '\n')
