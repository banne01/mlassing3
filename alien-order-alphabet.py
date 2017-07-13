import collections 
words = ["baa", "abcd", "abca", "cab", "cad"]
d = collections.defaultdict(set) # gragh as a dictonary

for i in range(len(words)-1):
    w1 = words[i]
    w2 = words[i+1]
    j = 0
    while(j < len(w1) and j < len(w2)):
        if w1[j] != w2[j]:
            d[w1[j]].add(w2[j])
            break
        j+=1     
def toposortUtil(alpha, d, visited, stack):
    visited.add(alpha)
    for neigh in d[alpha]:
        if neigh not in visited:
            toposortUtil(neigh, d, visited, stack)
    stack.append(alpha)        

def topoSort(d):
    visited = set()   
    stack = []
    for alpha in d.keys():
        if alpha not in visited:
            toposortUtil(alpha, d, visited, stack)
    print " ".join(stack[::-1])



print words
print d
topoSort(d)

