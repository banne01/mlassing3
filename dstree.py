import sys, os
import math
from collections import defaultdict
from copy import deepcopy
DATA_FILE =  "shuttle_ext_unique.dat"
attributes  = "auto stability error sing wind magnitude visibility"
attrlist = attributes.split()
targetname = "auto"
decision_values = ("noauto auto").split()
class dstree:
	def __init__(self):
		self.attrname = attributes.split()
		self.data = []
		fd = open(DATA_FILE)
		for line in fd:
			intval = map(int,line.strip().split(" "))
			self.data.append(intval)
		self.attrindex = range(len(self.data[0]))
		self.targetindex = attributes.index(targetname)
		self.attrindex.remove(self.targetindex)
		# check sanity for data 
		#if (len(self.attrindex) != len(self.attrname)):
		#	raise
		print self.attrindex
		print self.targetindex
		#print self.data
	def default_value(self):
		attr_fre_map = defaultdict(int)
		for record in self.data:
			if(attr_freq_map.has_key(record[t])):
				attr_freq_map[record[t]] += 1.0	
			else:
				attr_freq_map[record[t]] = 1.0
	@staticmethod
	def divide_data(data,index):
		print 'devide data'
		print len(data)
		print index
		attr_freq_map = defaultdict(int)
		new_data = {}
		for record in data:
			if(attr_freq_map.has_key(record[index])):
					attr_freq_map[record[index]] += 1.0	
			else:
				attr_freq_map[record[index]] = 1.0
		print attr_freq_map
		for attr_val in attr_freq_map.keys():
			new_data[attr_val]= [record for record in data if record[index]==attr_val]
		return new_data	

	@staticmethod
	def choose_best_attr(data,attr,target):
		print attr
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
		#print sort_gain
		gain,best_attr = sort_gain[0]
		print 'best attr' + str(best_attr)
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
	def information_gain(attr_fre_map):			
		pass
	@staticmethod	
	def create_decision_tree(data,attridx_list,targetidx):
		# Algo is to branch on the best attribute
		# recursive create branch for each value of the attribute 
		# to end recursion
		# 	 test1 if all examples of same category
		#	 test2 If not attrbute left to branch upon
		# no data left
		print 'new decision tree'
		if len(data) == 0 : 
			print "No data or attribute left"
			return treenode(None,None,None)
		# same class all means entory 0.0		
		elif (dstree.entrory_calculate(data,targetidx) == 0.0):
			print 'All same data no more branches for len ',(len(data)),decision_values[data[0][targetidx]-1]
			return treenode(None,None,decision_values[data[0][targetidx]-1]) 
 		else:
			best_attr_index =dstree.choose_best_attr(data,attridx_list,targetidx)
			new_attr_list = deepcopy(attridx_list)
			new_attr_list.remove(best_attr_index)
			print new_attr_list
			tnode = treenode(best_attr_index,attrlist[best_attr_index])
			new_data_map = dstree.divide_data(data,best_attr_index)
			print new_data_map.keys()
			for  att_value in new_data_map.keys():
				childnode = dstree.create_decision_tree(new_data_map[att_value],new_attr_list,targetidx)
				tnode.addchild(att_value, childnode)
		return tnode
		
class treenode:
	def __init__(self,attrindex=None,attrname=None,decision=None):
		#attribute name
		self.attrname = attrname
		self.attrindex = attrindex
		self.decision = decision
		# branch dictionary
		self.branches = {}

	def addchild(self,attrval,child):
		self.branches[attrval]= child
	
	def printtree(self,tab):
		if(self.attrname == None and  self.attrindex == None):
			if (self.decision != None):
				print self.decision
			return
		print '\n'+' '*4*tab,'Atrribute ',self.attrname
		#if( self.attrindex):
			#print  self.attrname
		#if( self.attrname):
			#print self.attrindex
		for v,child in self.branches.items():
			print  ' '*4*tab, self.attrname, '=', v, '====>', 
			child.printtree(tab+1)

'''start here Main'''
if __name__ == "__main__":
	print "Hello"	
	dtobj = dstree()	
	#dstree.choose_best_attr(dtobj.data,dtobj.attrindex,dtobj.targetindex)
	tree = dstree.create_decision_tree(dtobj.data,dtobj.attrindex,dtobj.targetindex)
	print "=======Decision tree======"
	tree.printtree(1)
