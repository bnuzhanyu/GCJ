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

def bin_str(v):
    s = "".join([ str((v >> (7 - i)) & 1) for i in range(8)])
    return s

def rotate(v, b):
    return ((v << (8-b)) & 0x00FF) | (v >> b)

def count_bit(v):
    return sum([(v >> i) & 1 for i in range(8)])
    
def send(v):
    print(bin_str(v), flush=True)
    return int(input())

BIT_COUNT = 8
val_set = [[] for i in range(BIT_COUNT + 1)]

def father(v):
    b = count_bit(v)
    s = val_set[b]
    for i in range(1, BIT_COUNT):
        if rotate(v, i) in s:
            return rotate(v, i)
    s.append(v)
    return v

fa = [father(i) for i in range(1<<BIT_COUNT)]
unique_fa = set(fa)


def state_to_val(bit, st):
    vs = val_set[bit]
    r = []
    for i in range(len(vs)):
        if st & (1 << i):
            r.append(vs[i])
    return r

def val_to_state(bit, vals):
    vs = val_set[bit]
    vals = set([fa[v] for v in vals])
    st = 0
    for x in vals:
        st = st | (1 << vs.index(x))
    return st

def reached_state(bit, st, v):
    vals = state_to_val(bit, st)
    vsb = [set() for i in range(BIT_COUNT+1)]
    reach = []
    for b in range(BIT_COUNT):
        rv = rotate(v, b)
        for c in vals:
            x = fa[c ^ rv]
            bc = count_bit(x)
            vsb[bc].add(x)
        
    for b in range(BIT_COUNT+1):
        if len(vsb[b]) > 0:
            nx_st = val_to_state(b, vsb[b])
            reach.append((b, nx_st, ))
    return reach
    
def bfs():
    next_step = dict()
    next_step[(0, 1, )] = 0
    next_state = dict()
    stop = False
    while not stop:
        stop = True
        for i in range(1, BIT_COUNT + 1):
            for z in range(1, 1 << len(val_set[i])):
                idx = (i, z,)
                if idx in next_step:
                    continue
                stop = False
                for f in unique_fa:
                    if (i, z, f,) in next_state:
                        rs = next_state[(i, z, f,)]
                    else:
                        rs = reached_state(i, z, f)
                        next_state[(i, z, f,)] = rs
                    ok = True
                    for r in rs:
                        if r not in next_step:
                            ok = False
                            break
                    if ok:
                        next_step[idx] = f
                        break
    return next_step
        
next_step = bfs()

def make_set(st, cur_bit, v):
    vs = set()
    for cand in st:
        for i in range(BIT_COUNT):
            x =  cand ^ rotate(v, i)
            if count_bit(x) == cur_bit:
                vs.add(x)
    return vs

def run():
    nxt = bfs()
    case_num = read_int()
    for ca in range(case_num):
        bit = 8
        v = 0
        st = set([i for i in range(256)])
        cur_state = (4, 1,)
        while bit > 0:
            v = next_step[cur_state]
            bit = send(v)
            if bit == -1:
                exit(1)
            if bit == 0:
                break
            st = make_set(st, bit, v)
            cur_state = (bit, val_to_state(bit, st), )

run()   
