#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

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
    vector<vector<int> > adj;
    vector<int> low;
    vector<int> dfn;
    int ts;
    int n;
    void init(int _n){
        adj.resize(_n);
        n = _n;
        low.resize(_n);
        dfn.resize(_n);
        fill(dfn.begin(), dfn.end(), 0);
        ts = 0;
    }
    set<pair<int, int> > st;
    stack<pair<int, int> > stk;
    void add_edge(int a, int b){
        if (a > b) {
            swap(a, b);
        }
        if (st.find(make_pair(a, b)) == st.end()){
            adj[a].push_back(b);
            adj[b].push_back(a);
            st.insert(make_pair(a,b));
        }
    }

    bool is_reached(int u){
        return dfn[u] != 0;
    }

    void dfs(int u, int fa){
        dfn[u] = ++ts;
        low[u] = dfn[u];
        for (auto v : adj[u]){
            if (v == fa){
                continue;
            }
            auto p = make_pair(u, v);
            if (dfn[v] == 0){
                stk.push(p);
                dfs(v, u);
                low[u] = min(low[v], low[u]);
                if (low[v] >= dfn[u]){ //find a 
                    bcc.push_back(unordered_set<int>());
                    while (1){
                        auto cur_e = stk.top(); stk.pop();
                        bcc.back().insert(cur_e.first);
                        bcc.back().insert(cur_e.second);
                        if (cur_e.first == u && cur_e.second == v){
                            break;
                        }
                    }
                    bcc.back().insert(u);
                }
            }else{
                //if(dfn[v] < dfn[u]){
                //stk.push(p);
                low[u] = min(low[u], low[v]);
            }
        }
    }

    bool has_two_path(int u, int v){
        for (auto& s : bcc){
            if (s.find(u) != s.end() && s.find(v) != s.end()){
                return true;
            }
        }
        return false;
    }

    void search_from(int u){
        dfs(u, -1);
    }

    vector<unordered_set<int> > bcc;
};

struct Problem{
    char board[110][110];
    int id[110][110];
    int N;
    int countBlue;
    int countRed;
    int blueSrc, blueDst;
    int redSrc, redDst;
    Graph g;

    void read(){
        cin >> N; 
        blueSrc = 0;
        blueDst = 1;
        redSrc = 2;
        redDst = 3;
        for (int i = 0; i < N+2; i++){
            board[0][i] = 'R'; id[0][i] = redSrc;
            board[N+1][i] = 'R'; id[N+1][i] = redDst;
            board[i][0] = 'B'; id[i][0] = blueSrc;
            board[i][N+1] = 'B'; id[i][N+1] = blueDst;
        }
        board[0][0] = board[0][N+1] = board[N+1][0] = board[N+1][N+1] = '.';

        string line;
        int _id = 4;
        for (int i = 1; i <= N; i++){
            cin >> line;
            for (int j = 1; j <= N; j++){
                board[i][j] = line[j-1];
                id[i][j] = _id++;
            }
        }
        g.init(_id);
    }

    void build_graph(){
        int di[] = { 0, -1, -1, 0, 1 , 1};
        int dj[] = { -1, 0, 1, 1, 0 , -1};

        countBlue = 0;
        countRed = 0;
        for (int i = 1; i <= N; i++){
            for (int j = 1; j <= N; j++){
                if (board[i][j] == 'B'){
                    countBlue++;
                }else if (board[i][j] == 'R'){
                    countRed++;
                }
                for (int d = 0; d < 6; d++){
                    int x = i + di[d];
                    int y = j + dj[d];
                    if (board[i][j] != '.' && board[i][j] == board[x][y]){
                        g.add_edge(id[i][j], id[x][y]);
                    }
                }
            }
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        build_graph();
        if (abs(countBlue - countRed) > 1){
            //impossible
            printf("Impossible\n");
        }else{
            g.search_from(blueSrc);
            g.search_from(redSrc);

            bool blue_win = g.is_reached(blueDst);
            bool red_win = g.is_reached(redDst);
            if (!blue_win && !red_win){
                //not yet
                printf("Nobody wins\n");
            }else if (blue_win && !red_win 
                     && countRed <= countBlue 
                     && !g.has_two_path(blueSrc, blueDst)){
                printf("Blue wins\n");

            }else if (red_win && !blue_win 
                      && countBlue <= countRed
                      && !g.has_two_path(redSrc, redDst)){
                printf("Red wins\n");
            }else{
                //impossible
                printf("Impossible\n");
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

