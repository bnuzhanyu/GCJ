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
    ll C, D, V;
    int d[101];
    void read(){
        cin >> C >> D >> V;
        for (int i = 0; i < D; i++){
            cin >> d[i];
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        ll cur = 0;
        int id = 0;
        int ans = 0;
        while (cur < V){
            if (id == D || cur + 1 < d[id]){
                ans++;
                cur = (cur + 1) * C + cur;
            }else{
                cur = (d[id] * C + cur);
                id++;
            }
        }
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

