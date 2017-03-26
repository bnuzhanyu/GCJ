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
    vector<vector<int> > adj;
    void init(int n){
        adj.clear();
        adj.resize(n);
    }
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    struct Child{
        Child(int n = 1, int c = 0){
            node_n = n;
            cut = c;
        }

        int cut_diff(){
            return cut - node_n;
        }
        int node_n;
        int cut; 
    };

    Child dfs(int fa, int u){ //return least cut of node u
        Child cur(1, 0);
        vector<Child> children;
        int ch_total = 0;
        for (auto v : adj[u]){
            if (v == fa){
                continue;
            }
            children.push_back(dfs(u, v));
            ch_total += children.back().node_n;
        }
        cur.node_n = ch_total + 1;
            
        if (children.size() == 1){
            cur.cut = ch_total;
        }else if(children.size() > 1){ //find 2 children not cut
            int min1 = adj.size()*2;
            int min2 = min1;
            for (auto& c : children){
                if (c.cut_diff() < min1){
                    min2 = min1;
                    min1 = c.cut_diff();
                }else if (c.cut_diff() < min2){
                    min2 = c.cut_diff();
                }
            }
            cur.cut = ch_total + min1 + min2;
        }
        return cur;
    }

};

struct Problem{

    int N;
    Graph g;
    void read(){
        cin >> N;
        int x, y;
        g.init(N);
        for (int i = 0; i < N-1; i++){
            cin >> x >> y;
            x--, y--;
            g.add_edge(x, y);
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int min_ans = N;
        for (int i = 0; i < N; i++){
            auto ch = g.dfs(-1, i);
            min_ans = min(min_ans, ch.cut);
        }
        printf("%d\n", min_ans);

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

