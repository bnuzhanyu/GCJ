import copy
import heapq

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
    mat = []
    for i in range(R):
        mat.append(init_arr(C, val))
    return mat;
        
class Grid(object):
    def __init__(self, h, x, y):
        self.x = x
        self.y = y
        self.h = h

    def __lt__(self, other):
        return self.h > other.h

    def __str__(self):
        return str(x) + ',' + str(y) + ' h:' + str(self.h)


dx = [0,1,0,-1]
dy = [1,0,-1,0]

case_num = read_int()
for ca in range(1, case_num+1):
    #read
    R, C = read_ints()
    mark = init_mat(R, C, False)

    #make queue
    grids = read_mats(R, C)
    q = []
    for i in range(R):
        for j in range(C):
            g = Grid(grids[i][j], i, j)
            heapq.heappush(q, g)

    #solve
    ans = 0
    while len(q)>0:
        g = heapq.heappop(q)
        if mark[g.x][g.y]: continue
        mark[g.x][g.y] = True
        for (x,y) in zip(dx, dy):
            nx = g.x + x
            ny = g.y + y
            if nx >= 0 and nx < R and ny >= 0 and ny < C and not mark[nx][ny]:
                if grids[nx][ny] < g.h - 1:
                    ans += g.h - 1 - grids[nx][ny]
                    grids[nx][ny] = g.h - 1
                    ng = Grid(grids[nx][ny], nx, ny)
                    heapq.heappush(q, ng)

    print("Case #{}: {}".format(ca, ans))
    
