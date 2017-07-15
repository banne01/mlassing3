def parseCSV(strs):
	res= []
	for s in strs.splitlines():
		cur = ""
		inCom = False
		st = 0
		for i,c in enumerate(s):
			if inCom:
				if c == '"' :
					if i < len(s) -1 and s[i+1] =='"' :
						cur += '"'
					else:
						inCom = False
					continue
				continue
			else:
				if c =='"':
					inCom = True
					continue	
				elif c==",":
					cur += "|"
					continue
			cur += c	
		print cur
		res.append(cur)

print start
print "\n\n"
parseCSV(start)	
