import os, sys
import math
from collections import defaultdict
f_train_path = "optdigits_tra_trans.dat"
f_tra_path = "optdigits_trial_trans.dat"
tr_len = 65
or_len = 1025
class knn:
	def __init__(self):		
 		try:
			self.ftrain = open(f_train_path)
			self.ftrail = open(f_tra_path)
			self.train_data = []
			self.test_data = []
			self.dist = defaultdict(list)
		except:
			print "File not open"
 			raise
	def fill_data(self):
		for line in self.ftrain:
			intval = map(int,line.strip().split(" "))
			self.train_data.append(intval)
			#print intval	
		for line in self.ftrail:
			intval = map(int,line.strip().split(" "))
			self.test_data.append(intval)
	  	#print self.test_data

	def dist_row(self,p,t):
		vdist = 0
		for j in range(len(p) -2):
			var = (p[j]-t[j])*(p[j]-t[j])
			vdist = vdist +var
		#last element is sample
		return vdist,p[len(p)-1]

	def major_3nn(self):
		x = []
		x = sorted(self.dist[1])
		print x
		print self.test_data[1]

	def major_dist(self):
		for i in range(len(self.test_data)):
			#for each test
			for p in self.train_data:
				#distance from all train
				self.dist[i].append(self.dist_row(p,self.test_data[i]))
		#print len(self.distance)

if __name__ ==  "__main__":
	knnobj = knn()
	knnobj.fill_data()
	knnobj.major_dist()
	knnobj.major_3nn()
