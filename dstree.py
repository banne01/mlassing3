import sys, os
import math
from collections import defaultdict
DATA_FILE =  "shuttle_ext_unique.dat"
attributes = "auto stability error sing wind magnitude visibility"
resultname = "auto"

class dstree:
	def __init__(self):
		self.attrname = attributes.split()
		self.data = []
		fd = open(DATA_FILE)
		for line in fd:
			intval = map(int,line.strip().split(" "))
			self.data.append(intval)
		self.attrindex = range(len(self.data[0]))
		self.targetindex = attributes.index(resultname)
		self.attrindex.remove(self.targetindex)
		# check sanity for data 
		#if (len(self.attrindex) != len(self.attrname)):
		#	raise
		print self.attrindex
		print self.targetindex
		#print self.data
	def Information_gain(self):
		pass
	@staticmethod
	def choose_best_attr(data,attr,target):
		attr_gain = []
		#data entropy
		f_entropy = dstree.entrory_calculate(data,target)
		for t in attr: 
			s_entropy = 0.0
			attr_freq_map = defaultdict(int)
			for record in data:
				if(attr_freq_map.has_key(record[t])):
					attr_freq_map[record[t]] += 1.0	
				else:
					attr_freq_map[record[t]] = 1.0
			#print attr_freq_map
			for attr_val in attr_freq_map.keys():
				ratio = attr_freq_map[attr_val] / sum(attr_freq_map.values())
				new_data = [record for record in data if record[t]==attr_val]
				s_entropy += ratio*dstree.entrory_calculate(new_data,target)
			attr_gain.append((f_entropy - s_entropy,	t))
		sort_gain = sorted(attr_gain,reverse=True)	
		print sort_gain
		gain,best_attr = sort_gain[0]
		print best_attr
		return best_attr
		#print f_entropy
	@staticmethod	
	def entrory_calculate(data,target):
		target_freq = {}
		data_len = len(data) 
		entropy = 0.0
		for record in data:
			if (target_freq.has_key(record[target])):
				target_freq[record[target]] += 1.0
			else:
				target_freq[record[target]] = 1.0
		#print 'freq' 
		#print target_freq
		for freq in target_freq.values():
			#print freq,data_len
			entropy += ((-freq)/data_len)*math.log((freq/data_len),2)
		#print entropy
		return entropy
	@staticmethod
	def if_same_class(data,target)
		

	@staticmethod	
	def information_gain(attr_fre_map):			
		pass
	def create_decision_tree(self,data,attr,target):
		# Algo is to branch on the best attribute
		# recursive create branch for each value of the attribute 
		# to end recursion
		# 	 test1 if all examples of same category
		#	 test2 If not attrbute left to branch upon
		# no data left
		if len(data) == 0 :
				return default
		elif all_same_class(data):
				return first_value_in_data 
# 		else
#			best_atrr_index =	choose_best_atrribute(data,attr,target)
#	        tnode = treenode(best_atrr,self.attrname[best_attr_index])
#			for  valus in each_value_in_best_attr :
#				new_data = split by attribute values from_data to new_data
#				childnode = create_decision_tree(new_data,new_atrr,target)
#				tnode.addchild(valu , childnode)
#		return tnode
		
class treenode:
	
	def __init_(self,attrname,attrindex):
		#attribute name
		self.attrname = attrname
		self.attrindex = attrindex
		# branch dictionary
		self.branches = {}

	def addchild(self,attrval,child):
		self.brnach[attrval]= child
	
	def printtree(self):
		print  self.atrrname
		for v,child in self.brnach.item():
			print "\n \t " + v
			child.printtree()

'''start here Main'''
if __name__ == "__main__":
	print "Hello"	
	dtobj = dstree()	
	dstree.choose_best_attr(dtobj.data,dtobj.attrindex,dtobj.targetindex)
