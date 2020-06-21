#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <stack>
#include <queue>
#include <stdio.h>
#include <cmath>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Graph {
    int n;
    void init(int _n) {
        n = _n;
        adj.clear();
        adj.resize(n);
    }
    vector<vector<int>> adj;
    void add_edge(int i, int j) {
        adj[i].push_back(j);
        adj[j].push_back(i);
    }

    vector<int>& edges(int i) {
        return adj[i];
    }
};

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    
    Graph graph;

    int N;
    void read() {
        cin >> N;
        graph.init(N);
        visited.resize(N);
        dist.resize(N);
        fill(dist.begin(), dist.end(), N + 1);
        fill(visited.begin(), visited.end(), false);
        loop = queue<int>();
        int x, y;
        for (int i = 0; i < N; i++) {
            cin >> x >> y;
            graph.add_edge(x-1, y-1);
        }
    }

    vector<bool> visited;
    queue<int> loop;
    vector<int> dist;

    int dfs(int fa, int cur) {
        int ret = -1;
        visited[cur] = true;
        for (int c : graph.edges(cur)) {
            if (c != fa && visited[c]) {
                ret = c;
            }
        }
        for (int c : graph.edges(cur)) {
            if (!visited[c]) {
                int x = dfs(cur, c);
                if (x != -1) {
                    ret = x;
                }
            }
        }
        if (ret != -1) {
            loop.push(cur);
            dist[cur] = 0;
        }
        if (ret == cur) {
            ret = -1;
        }
        return ret;
    }

    void bfs() {
        while (!loop.empty()) {
            int cur = loop.front();
            loop.pop();
            for (int x : graph.edges(cur)) {
                if (dist[x] > N) {
                    dist[x] = dist[cur] + 1;
                    loop.push(x);
                }
            }
        }
    }

    void solve(int ca) {
        read();
        dfs(-1, 0);
        bfs();
        cout << "Case #" << ca << ":";
        for (int i = 0; i < N; i++) {
            cout << " " << dist[i]; 
        }
        cout << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

