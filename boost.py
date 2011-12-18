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
        self.alphaT = [] # alptha at timeT*classes
        self.errT = [] #err at time T*classes
        self.hT = [] # ht for time t*classes 
        self.weightT = [] #T*classes
        weight0 = []
        for i in range(classes):
            vect_m = [1.0/self.m]*self.m
            weight0.append(vect_m)
        self.weightT.append(weight0) #distribution at t=0
        
        print "weight",len(self.weightT)

    # array for multiclass
    # check pix value 
    def hypothesis(self,x):
        h = 2*x -1
        return h
    
 
    def chooseBestH(self,time):
        # we use a binary classfier to create 
        #Multiclass classifier
        # hypthosis is tre
        # Hx = 2*x -1 
        
        err_vect = []
        h_vect = []
        for hclass in range(self.classes): # all classes
            errmin = 1.0
            bestH = 0 # pixel
        #set i as truue class and rest as false 
            for j in range(self.datalen): # all pixels
                err = 0.0
                for k in range(self.m): # all examples
                    tclass = self.test_data[k][self.datalen] # True Class
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
                    err = err + self.weightT[time][hclass][k]*Identity(predict,y)
                    #print "err",err
                if (err < errmin and err != 0.0):
                    bestH = hclass,j
                    errmin = err
            print "class and err_min,bestH",errmin,hclass,bestH
            h_vect.append(bestH)
            err_vect.append(errmin)
        #print "errormin",err_vect
        #print "hypothese",h_vect
        self.hT.append(h_vect)
        return err_vect
   
    def run(self):
        for t in range(3):#(self.rounds):
            #chhose best hypothesis
            err_vect = self.chooseBestH(t) # choose best H at time t 
            #append err
            self.errT.append(err_vect) #err at time T
            #new alpha
            alp_vect = []
            for err in err_vect:
                alp = alphaweight(err)
                alp_vect.append(alp)
            #append alpha
            self.alphaT.append(alp_vect)
            wnew = []
            for i in range(self.classes):
                vect_m = [1.0/self.m]*self.m
                wnew.append(vect_m)
            #wnew = [[[0.0]*self.m]*classes]
            # calculate new weights
            for cl in range(self.classes): 
                normalize = 0.0
                for l in range(self.m):
                    y = self.test_data[l][self.datalen]
                    if(self.hT[t][cl][0]==y):
                        wnew[cl][l] = self.weightT[t][cl][l]*.5*(1/self.errT[t][cl])
                    else:
                        wnew[cl][l] = self.weightT[t][cl][l]*.5*(1/(1-self.errT[t][cl]))
                    normalize += wnew[cl][l]
                for l in range(self.m):
                    wnew[cl][l] = wnew[cl][l]/normalize
            #append
            self.weightT.append(wnew)
            #print self.weightT[t]
            print len(self.weightT)
            print "herror HT",self.hT[t]
            print "error errT",self.errT[t]
            print "alpha",self.alphaT[t]
        self.test()    
    def test(self):
        
        test_data = self.test_data[0] 
        f_vetor = []
        for  cl in range(self.classes):
            for t in range(3):
                val = self.alphaT[t][cl]*self.hypothesis(self.hT[t][cl][1])
            f_vetor.append[val] 
        print "Actual",self.test_data[self.datalen]
        print "Feature",f_vetor     





            


                






