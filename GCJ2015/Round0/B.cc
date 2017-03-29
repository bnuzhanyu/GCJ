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

int cost[1100][1100];
void init_cost(){
    for (int i = 0; i <=1000; i++){
    for (int j = 1; j <= 1000; j++){
        cost[i][j] = (i + j - 1) / j - 1;
    }
    }
}

struct Problem{

    int N;
    vector<int> p;
    int min_t;
    void read(){
        cin >> N;
        p.resize(N);
        min_t = 0;
        for (int i = 0; i < N; i++){
            cin >> p[i];
            min_t = max(p[i], min_t);
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        for (int t = 1; t <= min_t; t++){
            int sum_t = t;
            for (auto x : p){
                sum_t += cost[x][t];
            }
            min_t = min(min_t, sum_t);
        }
        printf("%d\n", min_t);
    }
};

int main(){
    int T;
    init_cost();
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}

