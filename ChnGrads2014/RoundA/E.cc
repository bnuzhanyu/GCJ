#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <queue>

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


const int MAXN = 80010;

struct Edge{
    Edge(int _u, int _w) : u(_u), w(_w){ }
    int u;
    int w;
};

struct Graph{
    vector<vector<Edge> > adj;
    int N;
    void init(int n){
        adj.clear();
        adj.resize(n + 1);
        N = n;
    }
    void add_edge(int a, int b, int t){
        adj[a].push_back(Edge(b, t));
    }

    int spfa(int src, int dst){
        const int INF = 1<<30;
        queue<int> q;
        vector<bool> in_q(N+1, false);
        vector<int> dist(N+1, INF);
        vector<int> q_cnt(N+1, 0);

        dist[src] = 0;
        q.push(src);
        in_q[src] = true;
        q_cnt[src] = 1;
        bool end = false;
        while(!q.empty() && !end){
            int u = q.front(); q.pop();
            in_q[u] = false;
            for (int i = 0; i < adj[u].size(); i++){
                int v = adj[u][i].u;
                int w = adj[u][i].w;
                if (dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;
                    if (!in_q[v]){
                        q_cnt[v]++; 
                        if (q_cnt[v] > N){
                            end = true;
                            break;
                        }
                        in_q[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        return dist[dst] == INF ? -1 : dist[dst];
    }
};

struct Problem{

    int N, M;
    int origin[MAXN];
    unordered_map<string, int> mp;
    Graph g;
    void read(){
        cin >> N;
        int count = 0;
        for (int i = 1; i <= N; i++){
            string s;
            cin >> s;
            if (mp.find(s) == mp.end()){
                mp[s] = count++;
            }
            origin[i] = mp[s];
        }
        g.init(count);
        cin >> M;
        while (M--){
            int a, b, t;
            cin >> a >> b >> t;
            int x = origin[a];
            int y = origin[b];
            if (x != y){
                g.add_edge(x, y, t);
            }
        }
    }

    void solve(int ca){
        printf("Case #%d:\n", ca);
        int S, p, q;
        cin >> S;
        while (S--){
            cin >> p >> q;
            p = origin[p];
            q = origin[q];
            if (p == q){
                printf("0\n");
            }else{
                printf("%d\n", g.spfa(p, q));
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

