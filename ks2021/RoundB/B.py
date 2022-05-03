import copy

def read_int():
    return int(input())

def read_ints():
    return [int(x) for x in input().split(' ')]

def read_mats(R, C):
    mat = []
    for i in range(R):
        mat.append(read_ints())
    return mat

def init_arr(n, val):
    return [val] * n

def init_mat(R, C, val):
    mat = [[val] * C for _ in range(R)]

def diff(v):
    z = []
    for i in range(1, len(v)):
        z.append(v[i] - v[i-1])
    return z

def same(z):
    L = [1]
    for i in range(1, len(z)):
        if z[i] == z[i-1]:
            L.append(L[-1] + 1)
        else:
            L.append(1)
    return L
            
case_num = read_int()
for ca in range(case_num):
    #read
    n = read_int()
    v = read_ints()

    if n <= 3:
        ans = n 
    else:
        x = diff(v)
        L = same(x)
        x.reverse()
        R = same(x)
        R.reverse()
        x.reverse()
        ans = 0

        ans = max(ans, L[-1] + 1, L[-2] + 2)
        ans = max(ans, R[0] + 1, R[1] + 2)

        for i in range(0, n-2):
            s = x[i] + x[i+1]
            c = 0
            eq_l, eq_r = False, False

            if i == 0: pre = 0
            else: 
                ans = max(ans, L[i-1] + 2)
                pre = L[i-1]
                eq_l = (s == 2 * x[i-1])

            if i == n-3: nxt = 0
            else: 
                ans = max(ans, R[i+2] + 2)
                nxt = R[i+2]
                eq_r = (s == 2 * x[i+2])

            if eq_l: c += pre
            if eq_r: c += nxt
            ans = max(ans, c + 3)


    #solve
    print("Case #{}: {}".format(ca + 1, ans))
    
