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

def fun(x, y):
    if x <= 1 or y <= 1: return 0
    return min(y-1,x // 2 - 1) + min(x-1, y // 2 - 1)

case_num = read_int()
for ca in range(1, case_num+1):
    #read
    R, C = read_ints()
    mat = read_mats(R, C)

    #solve
    u = copy.deepcopy(mat)
    d = copy.deepcopy(mat)
    l = copy.deepcopy(mat)
    r = copy.deepcopy(mat)
    for i in range(1, R):
        for j in range(C):
            u[i][j] = mat[i][j] + u[i-1][j] * mat[i][j]
    for i in range(R-2,-1,-1):
        for j in range(C):
            d[i][j] = mat[i][j] + d[i+1][j] * mat[i][j];
    for j in range(1,C):
        for i in range(R):
            l[i][j] = mat[i][j] + l[i][j-1] * mat[i][j];
    for j in range(C-2,-1,-1):
        for i in range(R):
            r[i][j] = mat[i][j] + r[i][j+1] * mat[i][j];

    ans = 0
    for i in range(R):
        for j in range(C):
            ans = ans + fun(u[i][j], l[i][j])
            ans = ans + fun(u[i][j], r[i][j])
            ans = ans + fun(d[i][j], l[i][j])
            ans = ans + fun(d[i][j], r[i][j])
    print("Case #{}: {}".format(ca, ans))
    
