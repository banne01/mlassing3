import math

def alphaweight(x):
    alpha = -5*math.log(((1-x)/x))
    return alpha

def Identity(x,y): #check the inequality
    if x==y:
        return 0 
    else:
            return 1   


class AdaBoost:

    def __init__(self,test_data,train_data,rounds,classes):
        
        self.train_data  = train_data
        self.test_data   = test_data

        self.rounds = rounds
        
        self.classes = classes 
        
        print "classes",self.classes 
        
        self.m = len(test_data) # total no of samples 
        print "m samples",self.m

        self.datalen = len(test_data[0])-1 # no of pixel
        print "datalen",self.datalen

        #paramters for algorithsm
        self.time  = 0
        self.alphaT = [] # alptha at timeT
        self.errT = [] #err at time T
        self.hT = [] # ht for time t
        self.weightT = []
        self.weightT.append([1.0/self.m]*self.m) #distribution at t=0

        #print "weight",self.weightT
    
    

    # array for multiclass
    # check pix value 
    def hypothesis(self,x):
        h = 2*x -1
        return h
    
 
    def chooseBestH(self,time):
        # we use a binary classfier to create 
        #Multiclass classifier
        # hypthosis is tre
        # Hx = 2*x -1 and  1 - 2x
        bestH = 0,0 # class and pixel 
        errmin = 1.0
        for hclass in range(self.classes): # all classes
        #set i as truue class and rest as false 
            for j in range(self.datalen): # all pixels
                err = 0.0
                for k in range(self.m): # all examples
                    tclass = self.test_data[j][self.datalen] # True Class
                    # check the true class with hypothesis calss
                    # we are working on hclass now so idealy 
                    # check if hclass is true class
                    # then give +1 or -1
                    #print  "classes ",hclass,tclass
                    
                    predict = self.hypothesis(self.test_data[k][j])
                    if hclass == tclass:
                        y = -1
                    else:
                        y = 1
                    err = err + self.weightT[time][k]*Identity(predict,y)
                    #print "err",err
                if (err < errmin):
                    bestH = hclass,j
                    errmin = err
        
        print "errormin",errmin
        print "hypothese",bestH 
        self.hT.append(bestH)
        return errmin
   
    def run(self):
        for t in range(1):#(self.rounds):
            #chhose best hypothesis
            err = self.chooseBestH(t) # choose best H at time t 
            #append err
            self.errT.append(err) #err at time T
            #new alpha
            alp = alphaweight(err)
            #append alpha
            self.alphaT.append(alp)
            
            
            wnew = [0.0]*self.m
            normalize = 0.0
            
            # calculate new weights
            for l in range(self.m):
                y = self.test_data[l][datalen]
                if(self.hT[t][0]==y):
                    wnew[l] = self.weightT[t][l]*.5*(1/err)
                else:
                    wnew[l] = self.weightT[t][l]*.5*(1/(1-err))
                normalize += wnew[l]
            #normalize
            for l in range(self.m):
                wnew[l] = wnew[l]/normalize
            #append
            self.weightT.append(wnew)

           
          
            



                






            


                






