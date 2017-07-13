def custom(elem):
    return elem %3


def getrows_byslice(seq, rowlen):
    for start in xrange(0, len(seq), rowlen):
        yield filter(custom, seq[start:start+rowlen])

arr = [ i for i in range(100)]
pages = list(getrows_byslice(arr, 10))
print pages
