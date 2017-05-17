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

    int M, N, A;
    void read(){
        cin >> N >> M >> A;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        if (N * M < A){
            printf("IMPOSSIBLE\n");
            return;
        }
        int x0 = A / M;
        int x1 = x0;
        if (x0 != N){
            x1 = x0 + 1;
        }
        int y = A - x0 * M;
        printf("%d %d %d %d %d %d\n", 0, y, x0, 0, x1, M);
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

