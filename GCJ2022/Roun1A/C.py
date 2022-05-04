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
    return [[val] * C for _ in range(R)]

def _intersection(w1, w2):
    v = [min(v1, v2) for v1, v2 in zip(w1, w2)]
    return v

def solve(M, C, l, r):
    if l == r:
        return 0
    if M[l][r] != -1:
        return M[l][r]
    
    val = 1<<30
    for i in range(l, r):
        left = solve(M, C, l, i)
        right = solve(M, C, i+1, r)
        cur = left + right + 2 * (C[l][i] + C[i+1][r] - 2 * C[l][r])
        val = min(val, cur)
    M[l][r] = val
    #print(f'C[{l}][{r}]:{C[l][r]}, M[{l}][{r}]: {M[l][r]}')
    return val

case_num = read_int()
for ca in range(case_num):
    #read
    E, W = read_ints()
    wts = []
    C = init_mat(E, E, 0)
    for i in range(E):
        w = read_ints()
        C[i][i] = sum(w)
        wts.append(w)

    for i in range(E):
        C[i][i] = sum(wts[i])
        v = wts[i]
        for j in range(i+1, E):
            v = _intersection(v, wts[j])
            C[i][j] = sum(v)
        
    M = init_mat(E, E, -1)

    #solve
    ans = solve(M, C, 0, E-1) + C[0][E-1] * 2
    print("Case #{}: {}".format(ca + 1, ans))
