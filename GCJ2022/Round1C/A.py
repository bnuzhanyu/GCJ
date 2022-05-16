import copy
from collections import deque

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

def uniq(word):
    if not word:
        return ""
    r = []
    x = word[0]
    r.append(x)
    for w in word:
        if ord(w) != ord(x):
            r.append(w)
            x = w
    return "".join(r)

def parse(word):
    u = uniq(word)
    if len(u) == 1:
        return (True, u[0], len(word))
    return (False, u[0], u[-1], set([ x for x in u[1:-1]]), word, )

def fetch(pure, e):
    if e in pure:
        a = e * pure[e]
        pure.pop(e)
        return a
    else:
        return ""

def combine(pure, objs):
    visit = [False for i in range(len(objs))]
    def detect():
        h = None
        e = None
        dq = deque()
        while True:
            find = False
            for i in range(len(objs)):
                if not visit[i]:
                    if not e or e == objs[i][1]:
                        dq.append(objs[i][4])
                        e = objs[i][2]
                        if not h:
                            h = objs[i][1]
                        visit[i] = True
                        find = True
                    elif not h or h == objs[i][2]:
                        dq.appendleft(objs[i][4])
                        h = objs[i][1]
                        if not e:
                            e = objs[i][2]
                        visit[i] = True
                        find = True
                    if h in pure:
                        dq.appendleft(fetch(pure, h))
                    if e in pure:
                        dq.append(fetch(pure, e))
            if not find:
                return dq 
    ans = []
    while True:
        d = detect()
        if d:
            ans.extend(d)
        else:
            break

    for x in pure:
        ans.append(x * pure[x])

    result = "".join([x for x in ans])
    z = uniq(result)
    ele = set()
    for e in z:
        if e in ele:
            return "IMPOSSIBLE"
        ele.add(e)
    return result
   

case_num = read_int()
 
for ca in range(case_num):
    #read
    pure = dict()
    obj = []
    word_n = read_int()
    s = input()
    words = s.split()
    for word in words:
        z = parse(word)
        if z[0]:
            l = pure.get(z[1], 0)
            pure[z[1]] = l + z[2]
        else:
            obj.append(z)

    ans = combine(pure, obj)

    #solve
    print("Case #{}: {}".format(ca + 1, ans))
    
