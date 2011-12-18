import os, sys
import math
from collections import defaultdict
import png 
import neural
f_train_path = "optdigits_tra_trans.dat"
f_tra_path = "optdigits_trial_trans.dat"
f_orig_train = "optdigits_tra.dat"
f_oring_test = "optdigits_trial.dat"
tr_len = 65
or_len = 1025
image_path = "./images"

class Data:
    def __init__(self):
        try:
            self.ftrain = open(f_train_path)
            self.ftrail = open(f_tra_path)
            self.forgtrain = open(f_orig_train)
            self.forgtrail  = open(f_oring_test)
            self.train_data = []
            self.test_data = []
            self.train_org = []
            self.test_org = []
            self.dist = defaultdict(list)
            self.dist_index = defaultdict(list)
        except:
            print "file read error"
            raise
    
    def fill_data(self):
        for line in self.ftrain:
            intval = map(int,line.strip().split(" "))
            self.train_data.append(intval)
        #print intval
        for line in self.ftrail:
            intval = map(int,line.strip().split(" "))
            self.test_data.append(intval)
        for line in self.forgtrain:
			intval = map(int,line.strip().split(" "))
			self.train_org.append(intval)
        print len(self.train_org)
        for line in self.forgtrail:
			intval = map(int,line.strip().split(" "))
			self.test_org.append(intval)
        #print intval
        print len(self.test_org)

        

if __name__ == "__main__":
    data = Data()
    data.fill_data()
    #nn = neural.neural(len(data.train_data[0])-1,10,0,data.train_data,data.test_data,11,1000)
    #nn.train()
    nn = neural.neural(len(data.train_org[0])-1,10,64,data.train_org,data.test_org,21,100)
    nn.train()
