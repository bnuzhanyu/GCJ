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

const int MAXN = 1001;
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


struct Problem{
    int N;
    map<string, int> mpa; 
    map<string, int> mpb; 
    vector<vector<int> > g;
    
    void add_edge(int u, int v){
        g[u].push_back(v);
    }
    int aid, bid;

    void read(){
        cin >> N;
        g.resize(N);
        aid = 0;
        bid = 0;
        for (int i = 0; i < N; i++){
            string a, b;
            cin >> a >> b; 
            int u, v;
            if (mpa.find(a) == mpa.end()){
                mpa[a] = aid++; 
            }
            if (mpb.find(b) == mpb.end()){
                mpb[b] = bid++; 
            }
            u = mpa[a];
            v = mpb[b];
            add_edge(u, v);
        }
    }

    int cy[MAXN];
    int visited[MAXN];
    int cx[MAXN];
    bool dfs(int u){
        for (auto v : g[u]){
            if (!visited[v]){
                visited[v] = true;
                if (cy[v] == -1 || dfs(cy[v])){
                    cy[v] = u;
                    cx[u] = v;
                    return true;
                }
            }
        }
        return false;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        memset(cy, -1, sizeof(cy));
        memset(cx, -1, sizeof(cx));
        int cnt = 0;
        for (int i = 0; i < aid; i++){
            if (cx[i] == -1){
                memset(visited, 0, sizeof(visited));
                cnt += dfs(i);
            }
        }
        printf("%d\n",  N - aid - bid + cnt);
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

