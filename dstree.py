import sys, os

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
		self.resindex = attributes.index(resultname)
		# check sanity for data 
		if (len(self.attrindex) != len(self.attrname)):
			raise
		print self.attrindex
		#print self.data
	def select_best_attribute(self):
		pass
	def Information_gain(self):
		pass
	@staticmethod
	def choose_best_attr(data,attr,target):
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
		else if all_same_class(data):
				return first_value_in_data 
 		else
			best_atrr_index =	choose_best_atrribute(data,attr,target)
	        tnode = treenode(best_atrr,self.attrname[best_attr_index])
			for  valus in each_value_in_best_attr :
				
				new_data = split by attribute values from_data to new_data
				
				childnode = create_decision_tree(new_data,new_atrr,target)
				tnode.addchild(valu , childnode)
		return tnode
			
class treenode:
	
	def __init_(self,attrname,attrindex):
		#attribute name
		self.attrname = attrname
		self.attrindex = attrindex
		# branch dictionary
		self.branches = {}

	def addchild(self,attrval,child):
		self.brnach[attrval]= child
	
	def print(self):
		print  self.atrrname
		for v,child in self.brnach.item():
			print "\n \t " + v
			child.print()

'''start here Main'''
if __name__ == "__main__":
	print "Hello"	
	dtobj = dstree()	

