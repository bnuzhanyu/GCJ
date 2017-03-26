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

const int MAXN = 1010;
double p[MAXN][MAXN] = { 0 };
void init(int n){
    memset(p, 0, sizeof(p));
    for (int i = 0; i < n; i++) p[i][i] = 1;
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            double pik = p[i][k];
            for (int j = 0; j < n; j++){
                if (j == k){
                    p[i][j] = 1.0 / n;
                }else{
                    p[i][j] = pik * 1.0/n + p[i][j] * (n-1)/n;
                }
            }
        }
    }
}

struct Problem{

    int N;
    double p1, p2;
    void read(){
        cin >> N; 
        p1 = N * log(1.0 / N);
        p2 = 0;
        for (int i = 0; i < N; i++){
            int x;
            cin >> x;
            p2 += log(p[x][i]);
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        if (p1 > p2){
            printf("GOOD\n");
        }else{
            printf("BAD\n");
        }
    }
};

int main(){
    init(1000);
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}

