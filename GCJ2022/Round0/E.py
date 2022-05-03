import copy
import random

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
    N, K = read_ints()
    paths = init_arr(N+1, 0)
    c = 0
    seq = [x for x in range(1, N+1)]
    random.shuffle(seq)
    idx = 0

    s_res = 0
    s_n = 0
    r, p = read_ints()
    paths[r] = p

    def trans(s):
        print(f'T {s}', flush=True)
        r, p = read_ints()
        return r, p

    def walk():
        print('W', flush=True)
        r, p = read_ints()
        return r, p
    
    for _ in range((K-1) // 2):
        while idx < N and paths[seq[idx]] > 0:
            idx = idx + 1 
        if idx == N:
            break
        nxt = seq[idx]
        r, p = trans(nxt)
        paths[r] = p
        s_res = s_res + p
        s_n = s_n + 1
        r, p = walk()
        paths[r] = p
    
    avg = s_res / s_n
    total = 0
    zn = 0
    for i in range(1, N+1):
        if paths[i] > 0:
            total = total + paths[i]
        else:
            zn = zn + 1
    total = (total + zn * avg)
    total = int(total / 2)
    print(f'E {total}', flush=True)
    





