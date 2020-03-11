import numpy as np

class myFIR_filter: 
    #constructor
    def __init__(self,_coefficients):
        self.impulse = _coefficients
        #print(self.impulse)
        self.N = len(self.impulse)
        self.buffer = np.zeros(self.N)
        #print(self.buffer)
        self.offset = 0
       
    
    #filter method
    def dofilter(self,v):
        self.offset -= 1
        result = 0
        if (self.offset < 0):
            self.offset = self.N - 1
        self.buffer[self.offset] = v
        
            
        result += np.dot(self.buffer[self.offset:self.N],self.impulse[0:self.N-self.offset])
        result += np.dot(self.buffer[0:self.offset],self.impulse[self.N-self.offset:self.N])
            
        return result