#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
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

struct Problem{

    int N;
    vector<vector<int> > graph;
    vector<bool> visited;
    vector<int> in;
    void read(){
        cin >> N;
        graph.resize(N);
        visited.resize(N);
        in.resize(N);
        fill(in.begin(), in.end(), 0);
        for (int i = 0; i < N; i++){
            int M;
            cin >> M;
            for (int j = 0; j < M; j++){
                int f;
                cin >> f;
                graph[f-1].push_back(i);
                in[i]++;
            }
        }

    }

    void clear(){
        fill(visited.begin(), visited.end(), 0);
    }

    bool dfs(int fa){
        if (visited[fa]){
            return true;
        }
        visited[fa] = true;
        bool ret = false;
        for (auto u : graph[fa]){
            ret = ret || dfs(u);
        }
        return ret;
    }

    bool doit(){
        for (int i = 0; i < N; i++){
            if (in[i] == 0){
                clear();
                bool ret = dfs(i);
                if (ret){
                    return true;
                }
            }
        }
        return false;
    }

    void solve(int ca){
        printf("Case #%d: %s\n", ca, doit() ? "Yes": "No");
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

