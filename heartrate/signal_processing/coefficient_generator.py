import numpy as np
import scipy.signal as ss

file = open("hr_coeff.dat","w+")

fs = 50
f1 = 10
#f2 = 105

B = [f1/fs*2]#,f2/fs*2]

b = ss.firwin((fs*2+1),B, pass_zero = False)#,f2/fs*2]);

np.savetxt("hr_coeff.dat",b,newline = '\n')
