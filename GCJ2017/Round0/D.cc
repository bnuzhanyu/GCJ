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

struct Graph{
    int ux[201];
    int uy[201];
    int visited[201];
    vector<int> adj[201];
    int N;
    void init(int n){
        N = n;
    }
    void add_edge(int u, int v){
        adj[u].push_back(v);
    }

    int dfs(int x){
        for (auto v : adj[x]){
            if (!visited[v]){
                visited[v] = 1;
                if (ux[v] == -1 || dfs(ux[v])){
                    ux[v] = x;
                    uy[x] = v;
                    return 1;
                }
            }
        }
        return 0;
    }

    int max_match(){
        int ret = 0;
        memset(ux, -1, sizeof(ux));
        memset(uy, -1, sizeof(uy));
        for (int i = 1; i <= N; i++){
            if (uy[i] == -1){
                memset(visited, 0, sizeof(visited));
                ret += dfs(i);
            }
        }
        return ret;
    }
};
struct Problem{

    int N, M;
    static int ud(int x, int y){
        return (x + y) - 1;
    }
    static int dd(int x, int y){
        return x - y + 100;
    }

    int row[101];
    int col[101];
    int u_diag[201];
    int d_diag[201];
    int ans[101][101];
    int ori[101][101];
    map<pair<int,int>, pair<int,int> > dd2rc;
    void init(){
        for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            int _ud = ud(r, c);
            int _dd = dd(r, c);
            dd2rc[make_pair(_ud, _dd)] = make_pair(r, c);
        }
        }
    }
    void read(){
        cin >> N >> M;
        string s;
        int x, y;
        init();
        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));
        memset(u_diag, 0, sizeof(u_diag));
        memset(d_diag, 0, sizeof(d_diag));
        memset(ans, 0, sizeof(ans));
        memset(ori, 0, sizeof(ori));
        for (int i = 0; i < M; i++){
            cin >> s >> x >> y;
            int m = 0;
            if (s == "o") m = 3;
            else if (s == "x") m = 1;
            else if (s == "+") m = 2;
            if (m & 1){
                row[x] = 1;
                col[y] = 1;
                ori[x][y] |= 1;
            }
            if (m & 2){
                u_diag[ud(x,y)] = 1;
                d_diag[dd(x,y)] = 1;
                ori[x][y] |= 2;
            }
        }
    }

    void get_rc(){
        int r = 1, c = 1;
        while (r <= N && c <= N){
            if (row[r]) {
                r++;
                continue;
            }
            if (col[c]) {
                c++;
                continue;
            }
            ans[r][c] |= 1;
            r++, c++;
        }
    }

    void get_diag(){
        Graph g;
        g.init(2*N);
        for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++){
            int _ud = ud(i, j);
            int _dd = dd(i, j);
            if (u_diag[_ud] || d_diag[_dd]) continue;
            g.add_edge(_ud, _dd);
        }
        g.max_match();
        for (int i = 1; i <= 2*N; i++){
            if (g.uy[i] != -1){
                auto pos = dd2rc[make_pair(i, g.uy[i])];
                ans[pos.first][pos.second] |= 2;
            }
        }
    }

    char to_char(int x){
        if (x == 1) return 'x';
        if (x == 2) return '+';
        if (x == 3) return 'o';
        return 0;
    }
    void solve(int ca){
        printf("Case #%d: ", ca);
        //calc row col
        get_rc();
        get_diag();
        int n = 0;
        int score = 0;
        for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            int cur = ans[i][j] | ori[i][j];
            if (cur > ori[i][j]){
                n++;
            }
            score += (cur & 1) + ((cur >> 1) & 1);
        }
        }

        printf("%d %d\n", score, n);
        for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            int cur = ans[i][j] | ori[i][j];
            if (cur > ori[i][j]){
                printf("%c %d %d\n", to_char(ans[i][j] | ori[i][j]), i, j);
            }
        }
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

