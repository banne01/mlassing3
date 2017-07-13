def menu(A, s, cur, res):
    if s == 0:
        res.append(cur[:])
        return
    if not A or s < 0:
        return
    cur.append(A[0])
    menu(A, s-A[0], cur, res)
    cur.pop()
    menu(A[1:], s, cur, res)

res = []
s = 4
A = [1, 2, 3, 4]
cur = []
menu(A, s, cur, res)
print res
