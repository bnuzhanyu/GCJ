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
    n = read_int()
    s = input()
    pre, idx = chr(0), -1
    l = 0
    ans = []
    for ch in s:
        if ch > pre: 
            l = l + 1 
            ans.append(l)
        else:
            l = 1
            ans.append(l) 
        pre = ch

    ans = " ".join([str(f) for f in ans])
    #solve
    print("Case #{}: {}".format(ca + 1, ans))
    
