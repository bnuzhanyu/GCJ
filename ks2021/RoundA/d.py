import copy

def read_int():
    return int(input())

def read_ints():
    return [int(x) for x in input().split(' ')]

def read_mat(R, C):
    mat = []
    for i in range(R):
        mat.append(read_ints())
    return mat

def init_arr(n, val):
    return [val] * n

def init_mat(R, C, val):
    return [[val] * C for _ in range(R)]


def maxSpan(G, n):
    ans = 0
    global maxD
    global visited
    maxD = init_arr(n, -1)
    visited = init_arr(n, False)
    U = []
    for st in range(n):
        if visited[st] : continue
        ans = ans + prim(G, U, st)
    return ans

def maxEdgeUpdate(G, f):
    n = len(G)
    for i in range(n):
        if not visited[i] and G[i][f] > 0:
            if maxD[i] == -1 or G[i][f] > G[i][maxD[i]]: maxD[i] = f
    
def chooseNext(G, U):
    nxt = -1
    e = 0
    n = len(G)
    for i in range(n):
        if visited[i] or maxD[i] == -1: continue
        if G[i][maxD[i]] > e:
            e = G[i][maxD[i]]
            nxt = i
    return nxt, e

def prim(G, U, st):
    U.append(st)
    visited[st] = True
    maxEdgeUpdate(G, st)
    ans = 0
    while st != -1:
        nxt, e = chooseNext(G, U)
        if nxt == -1: break
        #print("choose {} nxt:{}".format(st, nxt))
        U.append(nxt)
        visited[nxt] = True
        maxEdgeUpdate(G, nxt)
        st = nxt
        ans += e
    return ans
        
case_num = read_int()
for ca in range(case_num):
    sz = read_int()
    #read
    A = read_mat(sz, sz)
    B = read_mat(sz, sz)
    R = read_ints()
    C = read_ints()

    G = init_mat(sz * 2, sz * 2, 0)
    #solve
    total = 0
    for i in range(sz):
        for j in range(sz):
            if (A[i][j] == -1):
                G[i][j+sz] = B[i][j]
                G[j+sz][i] = B[i][j]
                total += B[i][j]

    m = maxSpan(G, sz*2)
    print("Case #{}: {}".format(ca + 1, total - m))
    
