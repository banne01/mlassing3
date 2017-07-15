start = 'John,Smith,john.smith@gmail.com,Los Angeles,1 \n\
Jane,Roberts,janer@msn.com,"San Francisco, CA",0 \n\
"Alexandra ""Alex""",Menendez,alex.menendez@gmail.com,Miami,1 \n\
"""Alexandra Alex"""'

final = 'John|Smith|john.smith@gmail.com|Los Angeles|1 \n\
Jane|Roberts|janer@msn.com|San Francisco, CA|0 \n\
Alexandra "Alex"|Menendez|alex.menendez@gmail.com|Miami|1 \n\
"Alexandra Alex"'
def parseCSV(strs):
	res= []
	for s in strs.splitlines():
		cur = ""
		inCom = False
		for i,c in enumerate(s):
			if inCom:
				if c == '"' :
					if i < len(s) -1 and s[i+1] =='"' :
						cur += '"'
					else:
						inCom = False
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
	return res

print start
print "\n\n"
res = parseCSV(start)
print "\n\n"
print res
#res = "\n".join(res)	
print "\n\n"
final = final.splitlines()
for  i, f in enumerate(final):
	print final[i]
	print res[i]
	print res[i]==f		
