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
    return mat

val = []
step = []

def init_case():
    global val
    global step
    val = []
    step = []
    for _ in range(61):
        val.append(init_mat(61, 61, -1))
        step.append(init_mat(61, 61, -1))

def solve(W, E):
    init_case()
    we = W / 3.0 + E / 3.0
    val[1][0][0] = we 
    val[0][1][0] = we
    val[0][0][1] = we
    step[1][0][0] = 'P'
    step[0][1][0] = 'R'
    step[0][0][1] = 'S'
    v = 0
    for i in range(61):
        for j in range(61):
            if i + j > 60: continue
            k = 60 - i - j
            s = dfs(i, j, k, W, E)
            if v < s: 
                opt = (i, j, k)
                v = s
    
    ans = []
    i, j, k = opt
    #print("max:", v)
    #print("i,j,k:", i, j, k)
    while i + j + k > 0:
        ans.append(step[i][j][k])
        if step[i][j][k] == 'P': i = i - 1
        elif step[i][j][k] == 'R': j = j - 1
        elif step[i][j][k] == 'S': k = k - 1
    ans.reverse()
    return "".join(ans)

def dfs(p, r, s, W, E):
    if val[p][r][s] > 0: return val[p][r][s]
    game = p + r + s - 1
    x = 0
    if p > 0: #choose p
        win = s / game
        eq = r / game
        v = win * W + eq * E + dfs(p-1, r, s, W, E)
        if x < v:
            nxt = 'P'
            x = v

    if r > 0:
        win = p / game
        eq = s / game
        v = win * W + eq * E + dfs(p, r-1, s, W, E)
        if x < v:
            nxt = 'R'
            x = v

    if s > 0:
        win = r / game
        eq = p / game
        v = win * W + eq * E + dfs(p, r, s-1, W, E)
        if x < v:
            nxt = 'S'
            x = v

    val[p][r][s] = x
    step[p][r][s] = nxt
    return x
        

case_num = read_int()
X = read_int()
for ca in range(case_num):
    #read
    W, E = read_ints()
    ans = solve(W, E)

    print("Case #{}: {}".format(ca + 1, ans))
    
