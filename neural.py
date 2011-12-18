import random
import math

random.seed(0)

def randfloat(a, b):
    return (b-a)*random.random() + a

def sigmoid(x):
    return math.tanh(x) #1/(1.0 + math.exp(-x))

def dersigmoid(y):
    return (1.0 - y*y) 
    
class neural:
    def __init__(self,inp,outp,hidden,train_data,trail_data,alpha,run):
        """
        Constrctor class
        input layes = in 
        output layers = out
        hidden layes = hidden 
        """
        
        self.inp = inp+1
        self.outp = outp
        self.hidden = hidden+1
        self.train_data = train_data
        self.trail_data = trail_data
        self.alpha = alpha 
        self.m = len(train_data)
        self.run = run
        print inp+1
        print outp
        print hidden+1
          
        print "Creating weight matrix"
        
        if (self.hidden==1) is True:
            print 'No Hidden layer'
            self.wi = self.create_matrix(self.inp,self.outp)
            print "matrix size" 
            print len(self.wi[0])
            print len(self.wi)
        else:
            self.wi = self.create_matrix(self.inp,self.hidden)
            print len(self.wi)
            self.wout = self.create_matrix(self.hidden,self.outp)
            print len(self.wout)
        
        self.pi = [-1]*self.inp # perceptron
        self.ph = [-1]*self.hidden # perectrons
        self.po = [-1]*self.outp # perceptrons

    def create_matrix(self,I,J):
        mat = []
        for i in range(I):
            mat.append([0.0]*J)
        #print mat
        return mat        

    #forward propogate
    def update(self , index):
        data = self.train_data[index]
        for i in range(len(data)-1):
            self.pi[i] = data[i]
        #print "input " 
        #print self.pi
        
        if (self.hidden ==1):
           #hidden is zero 
            for i in range(self.outp):
                val = 0.0
                for j in range(self.inp):
                    val = val+ self.pi[i]*self.wi[j][i]
                self.po[i] = sigmoid(val)    
        else:
            for i in range(self.hidden):
                val = 0.0
                for j in range(self.inp):
                    val = val+ self.pi[i]*self.wi[j][i]
                self.ph[i] = sigmoid(val)    
            print "Hidden "
            print self.ph 
            for i in range(self.outp):
                val = 0.0
                for j in range(self.hidden):
                    val = val+ self.ph[i]*self.wout[j][i]
                self.po[i] = sigmoid(val)
        print "output"
        print self.po 

    def backpropogate(self,output):
        
        #delta in output
        out_delta = [0.0]*self.outp 
        for i in range(self.outp):
            out_delta[i] = output[i] - self.po[i]
            out_delta[i] = dersigmoid(self.po[i])*out_delta[i]
        print 'out_delta'
        print out_delta 
        #update outputweights
        if (self.hidden==1):
            for i in range(self.inp):   
                for j in range(self.outp):
                    self.wi[i][j] = self.wi[i][j] - (self.alpha*out_delta[j]*self.pi[i])/self.m
        else:
            hid_delta = [0.0] * self.hidden
            for j in range(self.hidden):
                error = 0.0
                for k in range(self.outp):
                    error += out_delta[k]*self.wout[j][k]
                hid_delta[j] = dersigmoid(self.ph[j]) * error
    
            # update output weights
            for j in range(self.hidden):
                for k in range(self.outp):
                    self.wout[j][k] = self.wout[j][k] - (self.alpha* out_delta[k]*self.ph[j])/self.m
    
            # update input weights
            for i in range(self.inp):
                for j in range(self.hidden):
                    temp = hid_delta[j]*self.pi[i]
                    self.wi[i][j] = self.wi[i][j] - (self.alpha*temp)/self.m

        error = 0.0
        for k in range(len(output)):
            error = error+ .5*((output[k] - self.po[k])**2)    
        return error

       
    def train(self):
        for i in range(1):#self.run):
            error = 0.0
            for i in range(len(self.train_data)):
                output = [0]*self.outp
                print "actula output"
                data = self.train_data[i]
                res = data[len(self.train_data[i])-1]
                output[res] = 1
                print output
                self.update(i)
                error += self.backpropogate(output)
            print error    



         


