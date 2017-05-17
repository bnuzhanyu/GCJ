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

int dp[1<<17][17];
struct Problem{

    int K;
    string S;
    void read(){
        cin >> K >> S;
    }

    int dis[20][20];
    int add[20][20]; //add[i][j] means i as begin, j as end, addition cost
    void init(){
        int sz = S.size();
        for (int i = 0; i < K; i++)
        for (int j = i+1; j < K; j++){
            int d = 0;
            for (int x = i, y = j; x < sz ; x += K, y += K)
                d += (S[x] == S[y]) ? 0 : 1;
            dis[j][i] = dis[i][j] = d;
        }

        for (int i = 0; i < K; i++)
        for (int j = 0; j < K; j++){
            int d = 0;
            for (int x = i + K, y = j; x < sz; x += K, y += K)
                d += (S[x] == S[y]) ? 0 : 1;
            add[i][j] = d;
            //printf("add %d %d %d\n", i, j, d);
        }
    }

    int calc(int st){ //start as st
        int sz = S.size(); 
        memset(dp, 0x3f, sizeof(dp));
        dp[1<<st][st] = 1;
        for (int m = 1; m < (1<<K); m++){
            if (((m >> st) & 1) == 0 ) continue;
            for (int i = 0; i < K; i++){
                if (i == st) continue;
                if (((m >> i) & 1) == 0) continue;
                for (int j = 0; j < K; j++){
                    if (((m >> j) & 1) == 0) continue;
                    dp[m][i] = min(dp[m][i] , dp[m - (1<<i)][j] + dis[j][i]);
                }
            }
        }

        int ans = S.size() + 1;
        for (int i = 0; i < K; i++){
            if (i == st) continue;
            //printf("res %d %d %d %d\n", st, i, dp[(1<<K)-1][i], add[st][i]);
            ans = min(ans, dp[(1<<K) - 1][i] + add[st][i]);
        }
        return ans;
    }
    void solve(int ca){
        printf("Case #%d: ", ca);
        init();
        int ans = S.size() + 1;
        for (int i = 0; i < K; i++)
            ans = min(ans, calc(i));
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

