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

const int MAXN = 1001;

//find out_deg in reverse graph
//find loops calculate length 
//find size-2 loops + max_chain_size_of each of the 2 node

struct Problem{

    int N;
    int BFF[MAXN];
    int in_deg[MAXN];
    int belong_loop[MAXN];
    bool in_loop[MAXN];
    int chain_sz[MAXN];
    int visited[MAXN];

    void read(){
        cin >> N;
        memset(belong_loop, -1, sizeof(belong_loop));
        memset(in_loop, 0, sizeof(in_loop));
        memset(visited, 0, sizeof(visited));
        memset(chain_sz, 0, sizeof(chain_sz));
        memset(in_deg, 0, sizeof(in_deg));
        for (int i = 1; i <= N; i++){
            cin >> BFF[i];
            in_deg[BFF[i]]++;
        }
    }

    void dfs_loop(int tt, int cur){
        if (visited[cur] == tt){
            //cur is in loop
            in_loop[cur] = true;
        }else{
            if (visited[cur] != 0) return;
            visited[cur] = tt;
            dfs_loop(tt, BFF[cur]);
        }
    }

    void calc_chain_size(){
        for (int i = 1; i <= N; i++){
            if (in_deg[i] == 0){
                int sz = 0;
                int cur = i;
                while (belong_loop[cur] == -1){
                    sz++;
                    cur = BFF[cur];
                }
                chain_sz[cur] = max(chain_sz[cur], sz); 
            }
        }
    }

    int calc_loop_size(int root){
        int sz = 0;
        int r = root;
        do{
            r = BFF[r];
            belong_loop[r] = root;
            sz++;
        }while (r != root);
        return sz;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int tt = 1;
        for (int i = 1; i <= N; i++){
            dfs_loop(tt, i);
            tt++;
        }

        int ans = 0;
        for (int i = 1; i <= N; i++){
            if (in_loop[i] && belong_loop[i] == -1){
                ans = max(ans, calc_loop_size(i));
            }
        }

        calc_chain_size();

        int c2 = 0;
        for (int i = 1; i <= N; i++){
            if (BFF[BFF[i]] == i){
                c2 += chain_sz[i] + 1;
            }
        }
        ans = max(ans, c2);
        printf("%d\n", ans);
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

