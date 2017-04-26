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

    int K, C , S;
    void read(){
        cin >> K >> C >> S;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        if (C * S < K){
            printf("IMPOSSIBLE\n");
            return;
        }
        vector<long long> pos;
        int known = 0;
        while (known < K){
            long long final_pos = 0;
            for (int st = 0; st < C; st++){
                final_pos = final_pos * K + min(K - 1, known);
                known++;
            }
            pos.push_back(final_pos + 1);
        }
        for (auto p : pos){
            printf(" %lld", p);
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

