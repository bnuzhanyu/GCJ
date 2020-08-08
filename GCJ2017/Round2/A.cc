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

    int N;
    int P;
    int g[4];

    int solve2(){
        return g[0] + (g[1] + 1) / 2;
    }

    int solve3(){
        int ans = g[0];
        int x = min(g[1], g[2]);
        ans += x;
        g[1] -= x;
        g[2] -= x;
        ans += (g[1] + 2) / 3;
        ans += (g[2] + 2) / 3;
        return ans;
    }

    int solve4(){
        int ans = g[0];
        int x = min(g[1], g[3]);
        ans += x;
        ans += g[2] / 2;
        g[1] -= x, g[3] -= x;
        g[2] %= 2;
        int f = max(g[1], g[3]);

        if (g[2] == 0){
            ans += (f + 3) / 4;
        }else{
            ans ++;
            if (f > 2){
                ans += (f + 1) / 4;
            }
        }
        return ans;
    }

    void read(){
        cin >> N >> P;
        g[0] = g[1] = g[2] = g[3] = 0;
        for (int i = 0; i < N; i++){
            int x;
            cin >> x;
            g[x % P]++;
        }

    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int ans = 0;
        if (P == 2) ans = solve2();
        else if (P == 3) ans = solve3();
        else if (P == 4) ans = solve4();
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

