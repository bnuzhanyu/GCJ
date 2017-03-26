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

    int N;
    ll P, Q;
    void read(){
        string str;
        cin >> str; 
        sscanf(str.c_str(), "%lld/%lld", &P, &Q);
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        ll b = 1LL<<40;
        //P/Q = a/b
        ll g = __gcd(P, Q);
        P /= g, Q /= g;
        if (b % Q != 0){
            printf("impossible\n");
        }else{
            int cnt = 0;
            while (P < Q){
                cnt++;
                P *= 2;
            }
            printf("%d\n", cnt);
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

