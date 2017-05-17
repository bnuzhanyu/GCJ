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

    int M, V;
    int gn;
    struct Gate{
        int is_and;
        int is_change;
        void input(){
            cin >> is_and >> is_change;
        }
    };
    vector<Gate> gate;
    vector<int> val;

    void read(){
        cin >> M >> V;
        gn = (M-1) / 2;
        gate.resize(gn);
        val.resize(M - gn);
        dp[0].resize(M);
        dp[1].resize(M);
        for (int i = 0; i < gn; i++)
            gate[i].input();
        for (int i = 0; i < (M+1)/2; i++)
            cin >> val[i];
    }

    vector<int> dp[2];

    void dfs(int i){
        if (i >= gn){ //val node
            if (val[i- gn] == 0) {
                dp[0][i] = 0;
                dp[1][i] = M;
            }else{
                dp[0][i] = M;
                dp[1][i] = 0;
            }
        }else{
            dfs(i*2 + 1);
            dfs(i*2 + 2);

            int x0 = dp[0][i*2+1];
            int x1 = dp[1][i*2+1];
            int y0 = dp[0][i*2+2];
            int y1 = dp[1][i*2+2];

            if (gate[i].is_and){
                dp[0][i] = min(x0 + min(y0, y1), y0 + min(x0, x1));
                dp[1][i] = x1 + y1;
                if (gate[i].is_change){
                    dp[1][i] = min(dp[1][i], min(x1 + min(y0, y1), y1 + min(x0, x1)) + 1);
                }
            }else{
                dp[0][i] = x0 + y0;
                dp[1][i] = min(x1 + min(y0, y1), y1 + min(x0, x1));
                if (gate[i].is_change){
                    dp[0][i] = min(dp[0][i], min(x0 + min(y0, y1), y0 + min(x0, x1)) + 1);
                }
            }
            if (dp[0][i] > M) dp[0][i] = M;
            if (dp[1][i] > M) dp[1][i] = M;
        }
    }
    void solve(int ca){
        printf("Case #%d: ", ca);
        dfs(0);
        if (dp[V][0] == M){
            printf("IMPOSSIBLE\n");
        }else{
            printf("%d\n", dp[V][0]);
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

