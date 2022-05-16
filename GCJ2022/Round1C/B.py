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
    
def judge(e):
    S1 = sum(e)
    S2 = sum([x*x for x in e])
    return S1*S1 == S2

case_num = read_int()
for ca in range(case_num):
    #read
    N, K = read_ints()
    E = read_ints()
    ans = None
    if N == 1:
        ans = (0, )
    else:
        S1 = sum(E)
        S2 = (S1 * S1 - sum([e*e for e in E])) // 2
        if K == 1:
            if S1 == 0 and S2 == 0:
                ans = (0, )
            elif S1 != 0 and S2 % S1 == 0:
                ans = (-S2 // S1, )
        else:
            for i in range(-100000, 100000):
                v1 = S1 + i
                v2 = - S2 - S1*i
                if v1 == 0 and v2 == 0:
                    ans = (i, 0, )
                    break
                elif v1 != 0 and v2 % v1 == 0:
                    ans = (i, v2 // v1, )
                    break

    #solve
    # if ans is not None:
    #     vv = E + [x for x in ans]
    #     print(f"{vv}, {judge(vv)}")
    print(f"Case #{ca+1}:", end='')
    if ans is None: print(" IMPOSSIBLE")
    else:
        for x in ans:
            print(f" {x}", end='')
        print()
