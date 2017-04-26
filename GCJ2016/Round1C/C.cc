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

    int J, P, S, K;
    void read(){
        cin >> J >> P >> S >> K;
    }

    void solve_min(){
        for (int i = 0; i < J; i++){
            for (int j = 0; j < P; j++){
                for (int d = 0; d < K; d++){
                    printf("%d %d %d\n", i + 1, j + 1, (i+j+d) % S + 1);
                }
            }
        }
    }

    void solve_all(){
        for (int i = 0; i < J; i++){
            for (int j = 0; j < P; j++){
                for (int d = 0; d < S; d++){
                    printf("%d %d %d\n", i + 1, j + 1, d + 1);
                }
            }
        }
    }
    void solve(int ca){
        printf("Case #%d: ", ca);
        printf("%d\n", J * P * min(S, K));
        if (S <= K) solve_all();
        else solve_min();
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

