#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <functional>
#include <cmath>
#include <string.h>

using namespace std;
using ull = unsigned long long;
using ll = long long;
using db = double;
using PII = pair<int, int>;

template<typename T>
void print_vec(T& container, const std::string& sep = " "){
    for (auto& x: container){
        std::cout << x << sep;
    }
    std::cout << std::endl;
}

template<typename T>
void print_map(T& mp){
    for(auto& x: mp){
        std::cout << x.first << " " << x.second << std::endl;
    }
}


const static int N = 5010;
const static int M = 20010;
struct Edge {
    int from, to, next;
} edge[M], edge2[M];
int head[N];
int dfn[N], low[N], idx;
int stk[N], top;
int in[N];
int kind[N], cnt;
int opp[N], ind[N], col[N]; // 相对的点 入度 染色 col[]=1选择

struct TwoSat {

int n;
int cntE, cntE2;
void addedge(int u, int v) {
    edge[cntE].from = u; edge[cntE].to = v; edge[cntE].next = head[u]; head[u] = cntE++;
}
void addedge2(int u, int v) {
    edge2[cntE2].from = u; edge2[cntE2].to = v; edge2[cntE2].next = head[u]; head[u] = cntE2++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++idx;
    in[u] = true;
    stk[++top] = u;
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].to;
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (in[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++cnt;
        while (1) {
            int v = stk[top--]; kind[v] = cnt; in[v] = false;
            if (v == u) break;
        }
    }
}

bool topsort() // 序号从0开始
{
    for (int i = 0; i < n; i += 2) {
        int k1 = kind[i]; int k2 = kind[i^1]; // 相对的两个点
        if (k1 == k2) return false;
        opp[k1] = k2; opp[k2] = k1;
    }
    memset(head, -1, sizeof head);
    int u, v;
    for (int i = 0; i < cntE; ++i) {
        u = edge[i].from, v = edge[i].to;
        if (kind[u] != kind[v]) { // 反向建图
            addedge2(kind[v], kind[u]);
            ind[kind[u]]++;
        }
    }
    queue<int> q;
    for (int i = 1; i <= cnt; ++i) if (!ind[i]) q.push(i);
    while (q.size()) {
        u = q.front(); q.pop();
        if (!col[u]) col[u] = 1, col[ opp[u] ] = -1;
        for (int i = head[u]; i != -1; i = edge2[i].next)
            if (--ind[edge2[i].to] == 0) q.push(edge2[i].to);
    }
    return true;
}

void init(int pn) {
    cntE = cntE2 = 0;
    n = pn;
    memset(head, -1, sizeof head);
    memset(dfn, 0, sizeof dfn);
    memset(in, false, sizeof in);
    idx = top = cnt = 0;
    memset(ind, 0, sizeof ind);
    memset(col, 0, sizeof col);
}

bool sat() {
    for (int i = 0; i < n; i++) {
        if (dfn[i] == 0) {
            tarjan(i);
        }
    }
    return topsort();
}

};

int EAST = 0;
int WEST = 1;
int SOUTH = 2;
int NORTH = 3;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

const int MAXN = 51;
struct Gun {
    int x, y;
    int dir;
    int ok;
};

struct Problem{

    int N;
    TwoSat two_sat;
    string room[MAXN];
    Gun gun[MAXN*MAXN*2];
    PII empty[MAXN][MAXN];
    int mark[MAXN][MAXN];

    const int HORIZON = 0;
    const int VERTICAL = 1;
    int gn;
    int R, C;
    
    void read(){
        cin >> R >> C;
        for (int i = 0; i < R; i++){
            cin >> room[i];
        }
    }

private:
    bool valid(int i, int j) {
        return 0 <= i && i < R && 0 <= j && j < C;
    }

    void init_gun() {
        gn = 0;
        for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
        {
            empty[i][j] = make_pair(-1, -1);
            if (is_gun(i, j)){
                mark[i][j] = gn;
                gun[gn].x = i, gun[gn].y = j, gun[gn].dir = HORIZON, gun[gn].ok = 1;  
                gn++;
                gun[gn].x = i, gun[gn].y = j, gun[gn].dir = VERTICAL, gun[gn].ok = 1; 
                gn++; 
            }
        }
    }
    
    const int HIT_GUN = -2;
    const int HIT_WALL = -1;
    const int HIT_EMPTY = 0;
    const int HIT_MIRROR = 1;

    void record_empty(int x, int y, int d, int gun_id) {
        if (d == EAST || d == WEST) {
            empty[x][y].first = gun_id;
        } else {
            empty[x][y].second = gun_id;
        }
    }

    bool is_gun(int x, int y) {
        return room[x][y] == '-' || room[x][y] == '|';
    }

    bool is_mirror(int x, int y) {
        return room[x][y] == '\\' || room[x][y] == '/';
    }

    int next_dir(int d, char m) {
        static int next_d[2][4] = {
            {NORTH, SOUTH, WEST, EAST}, // mirror is '/'
            {SOUTH, NORTH, EAST, WEST} // mirror is '\'
        };
        int md = (m == '/') ? 0 : 1;
        return next_d[md][d];
    }

    int next(int& x, int& y, int& d) {
        x = x + dx[d]; 
        y = y + dy[d]; 
        if (!valid(x, y) || room[x][y] == '#') {
            return HIT_WALL;
        }
        if (is_gun(x, y)) {
            return HIT_GUN;
        }
        if (room[x][y] == '.') {
            return HIT_EMPTY;
        } else {
            d = next_dir(d, room[x][y]);
            return HIT_MIRROR;
        }
    }

    bool start_search(int g, int d, vector<PII>& r) {
        int x = gun[g].x, y = gun[g].y; 
        while (1) {
            int err = next(x, y, d);
            if (err == HIT_WALL) {
                break;
            } else if (err == HIT_GUN) {
                return false;
            } else if (err == HIT_EMPTY) {
                r.push_back(make_pair(x*C + y, d));
            }
        }
        return true;
    }

    void search() {
        for (int g = 0; g < gn; g++) {
            vector<PII> r;
            bool ret = true;
            if (gun[g].dir == VERTICAL) {
                ret = start_search(g, SOUTH, r);
                ret = ret && start_search(g, NORTH, r);
            } else {
                ret = start_search(g, EAST, r);
                ret = ret && start_search(g, WEST, r);
            }
            if (ret) {
                for (auto x : r) {
                    record_empty(x.first / C, x.first % C, x.second, g);
                }
            } else {
                gun[g].ok = 0; 
            }
        }
    }

    void add_edge(int u, int v) {
        two_sat.addedge(u, v);
    }

    bool build_empty(int i, int j) {
        int x = empty[i][j].first;
        int y = empty[i][j].second;
        if (x > y) {
            swap(x, y);
        }
        if (x == -1 && y == -1) {
            return false;
        }
        if (x == -1 || x == y) {
            add_edge(y^1, y);
        } else if (x != (y ^ 1)) {
            add_edge(x^1, y);
            add_edge(y^1, x);
        }
        return true;
    }

    bool build_gun(int g) {
        if (!gun[g].ok && !gun[g^1].ok) {
            return false;
        }
        if (!gun[g].ok) {
            add_edge(g, g^1);
        }
        return true;
    }

    bool build() {
        for (int g = 0; g < gn; g++) {
            if (!build_gun(g)) {
                return false;
            }
        }

        for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (room[i][j] == '.') {
                if (!build_empty(i, j)) {
                    return false;
                }
            }
        }
        }
        return true;
    }

public:
    void solve(int ca) {
        init_gun();
        search();
        two_sat.init(gn);
        bool ret = build();
        ret = ret && two_sat.sat();

        printf("Case #%d: ", ca);
        if (!ret) {
            printf("IMPOSSIBLE\n");
            return;
        } else {
            printf("POSSIBLE\n");
        }

        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++){
                if (is_gun(i, j)){
                    int g = mark[i][j];
                    if (col[kind[g]] == 1) {
                        room[i][j] = '-';
                    }else{
                        room[i][j] = '|';
                    }
                }
            }
            printf("%s\n", room[i].c_str());
        }
    }
};

int main(){
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}

