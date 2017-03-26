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

struct Problem{

    ll A;
    ll B;
    ll K;
    void read(){
        cin >> A >> B >> K;
        memset(dp, -1, sizeof(dp));
    }

    ll dp[32][2][2][2];
    int get_bit(int num, int i){
        return (num >> i) & 1;
    }

    ll count(int bit, bool a, bool b, bool c){
        if (bit == -1){
            return a && b && c;
        }
        if (dp[bit][a][b][c] != -1){
            return dp[bit][a][b][c];
        }
        
        int max_a = a ? 1 : get_bit(A, bit);
        int max_b = b ? 1 : get_bit(B, bit);
        int max_c = c ? 1 : get_bit(K, bit);

        ll res = 0;
        for (int av = 0; av <= max_a; av++)
        for (int bv = 0; bv <= max_b; bv++){
            int cv = av & bv;
            if (cv <= max_c){
                res += count(bit - 1, a || av < max_a, b || bv < max_b, c || cv < max_c);
            }
        }
        return dp[bit][a][b][c] = res;
    }

    void solve(int ca){
        printf("Case #%d: %lld\n", ca, count(31, false, false, false));
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

