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

struct Problem{

    int N, Q;
    struct Horse{
        int e;
        int s;
        int id;
        void input(){
            cin >> e >> s;
        }
    };

    long long dist[101][101];
    Horse horse[101];
    void read(){
        cin >> N >> Q;
        for (int i = 0; i < N; i++) {
            horse[i].input();
            horse[i].id = i;
        }
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                cin >> dist[i][j];
                if (dist[i][j] == -1) dist[i][j] = 1LL<<60;
            }
            dist[i][i] = 0;
        }
    }
    
    void floyd(){
        for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            if (i != j && i != k && j != k){
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }

    double mincost[101][101];
    void calc(){
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            mincost[i][j] = (dist[i][j] > horse[i].e) ? 1e50 : dist[i][j]*1.0 / horse[i].s;

        for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            if (i != j && i != k && j != k){
                mincost[i][j] = min(mincost[i][k] + mincost[k][j], mincost[i][j]);
            }
        }
    }

    void solve(int ca){
        floyd();
        calc();
        printf("Case #%d:", ca);
        while (Q--){
            int u, v;
            cin >> u >> v; 
            u--, v--;
            printf(" %.7f", mincost[u][v]);
        }
        printf("\n");
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

