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
    s = input()
    #solve
    last = 0
    cnt = []
    seq = []
    for c in s:
        if c != last:
            cnt.append(1)
            seq.append(c)
            last = c
        else:
            cnt[-1] = cnt[-1] + 1
    
    print("Case #{}: ".format(ca + 1), end = '')
    last_c = 'a' 
    last_n = 0
    for c, n in zip(seq, cnt):
        if c > last_c:
            print(last_c * (last_n*2), end='')
        else:
            print(last_c * last_n, end='')
        last_c = c
        last_n = n
    print(last_c * last_n)
            


        
