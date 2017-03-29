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

    int X, R, C;
    void read(){
        cin >> X >> R >> C;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        if (R > C) swap(R, C);
        bool is_ok = (R * C % X) == 0;
        if (X >= 7) is_ok = false;
        else if (X == 1 || X == 2) is_ok = is_ok && true;
        else{
            is_ok = is_ok && R >= (X + 1) / 2 && C >= X;
            if (X==4){
                is_ok = is_ok && R >= 3;
            }else if (X == 5){
                if (R == 3){
                    is_ok = is_ok && (C >= 10);
                }
            }else if (X == 6){
                is_ok = is_ok && R >= 4;
            }
        }
        if (is_ok) printf("GABRIEL\n");
        else printf("RICHARD\n");

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

