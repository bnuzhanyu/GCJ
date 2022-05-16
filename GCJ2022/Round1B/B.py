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

case_num = read_int()
for ca in range(case_num):
    #read
    N, P = read_ints()

    #solve
    l, h, vl, vh = 0, 0, 0, 0
    for _ in range(N):
        w = read_ints()
        cl, ch = min(w), max(w)
        tl = min(vh + abs(h-ch), vl + abs(l-ch)) + ch - cl
        th = min(vh + abs(h-cl), vl + abs(l-cl)) + ch - cl
        l, h, vl, vh = cl, ch, tl, th

    print("Case #{}: {}".format(ca + 1, min(vl, vh)))
    
