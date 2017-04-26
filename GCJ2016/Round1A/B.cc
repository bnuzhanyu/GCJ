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
    int lst[2510];
    void read(){
        cin >> N;
        memset(lst, 0, sizeof(lst));
        for (int i = 0; i < N*2 - 1; i++){
            for (int j = 0; j < N; j++){
                int x;
                cin >> x;
                lst[x]++; 
            }
        }
    }

    void solve(int ca){
        printf("Case #%d:", ca);
        for (int i = 0; i < 2501; i++){
            if (lst[i] & 1){
                printf(" %d", i);
            }
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

