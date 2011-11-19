import os, sys
import math
from collections import defaultdict
import png 
f_train_path = "optdigits_tra_trans.dat"
f_tra_path = "optdigits_trial_trans.dat"
f_orig_train = "optdigits_tra.dat"
f_oring_test = "optdigits_trial.dat"
tr_len = 65
or_len = 1025
image_path = "./images"

class knn:
	def __init__(self):		
 		try:
			self.ftrain = open(f_train_path)
			self.ftrail = open(f_tra_path)
			self.forgtrain = open(f_orig_train)
			self.forgtest  = open(f_oring_test)
			self.train_data = []
			self.test_data = []
			self.train_org = []
			self.test_org = []
			self.dist = defaultdict(list)
			self.dist_index = defaultdict(list)
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
		for line in self.forgtrain:
			intval = map(int,line.strip().split(" "))
			self.train_org.append(intval[0:len(intval)-1])
		print len(self.train_org)
		for line in self.forgtest:
			intval = map(int,line.strip().split(" "))
			self.test_org.append(intval[0:len(intval)-1])
		print len(self.test_org)
	
	def dist_row(self,p,t):
		vdist = 0
		for j in range(len(p) -2):
			var = (p[j]-t[j])*(p[j]-t[j])
			vdist = vdist +var
		#last element is sample
		return vdist,p[len(p)-1]

	def major_3nn(self):
		for i in range(len(self.test_data)):
			x = sorted(self.dist[i])
			self.dist_index[i].append(self.dist[i].index(x[0]))
			self.dist_index[i].append(self.dist[i].index(x[1]))
			self.dist_index[i].append(self.dist[i].index(x[2]))
			print self.dist_index[i]	   

	def create_image(self):
		for i in range(len(self.test_org)):
			index = self.dist_index[i]	
			image = imageclass.vector2image(self.test_org[i])
			imageclass.printimages(str(i)+str(0),image);
			for j in range(len(index)):
				image = imageclass.vector2image(self.train_org[index[j]])
				imageclass.printimages(str(i)+str(j+1),image);


	def image_3nn(self):
		pass
		
	def major_dist(self):
		for i in range(len(self.test_data)):
			#for each test
			for p in self.train_data:
				#distance from all train
				self.dist[i].append(self.dist_row(p,self.test_data[i]))
		#print len(self.distance)

class imageclass:
	def __init__(self):
		self.image = defaultdict(list)
		try:
			self.fimage = open(f_orig_test)
		except:
			print "Orignial File for digits not open"
			raise		
	def makeimage(self):
		for line in self.fimage:
			intval = map(int,line.strip().split(" "))
			index = intval[len(intval) -1]
			splitsize = 32
			for i in range(splitsize):
				self.image[index].append(intval[i*splitsize:(i+1)*splitsize])
		#print self.image[0]
		#print len(self.image[0])
	
	@staticmethod
	def printimages(name,v):
		d = os.path.dirname(image_path)
		if not os.path.exists(d):
			os.makedirs(d)
		file_path = os.path.join(image_path,name)
		f = open(file_path+'.png', 'wb')
		w = png.Writer(len(v[0]), len(v), greyscale=True, bitdepth=1)
		w.write(f, v)
		f.close()
	
	@staticmethod
	def vector2image(v):
			index = v[len(v) -1]
			splitsize = 32
			image = []
			for i in range(splitsize):
				image.append(v[i*splitsize:(i+1)*splitsize])
			return image

'Main routine'
if __name__ ==  "__main__":
	knnobj = knn()
	knnobj.fill_data()
	knnobj.major_dist()
	knnobj.major_3nn()
	knnobj.create_image()	
	
	
	#imageobj = imageclass()
	#imageobj.makeimage()
	#imageobj.printimages()
