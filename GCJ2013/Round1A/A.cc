#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

template<typename T>
void print_vec(T& container){
    for (auto& x: container){
        std::cout << x << " ";
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
    using ll = long long;
    using ull = unsigned long long;
    ull r, t;
    void read(){
        cin >> r >> t;
    }

    //return if a*b > c for all positive 
    bool mul_greater(ull a, ull b, ull c){
        if (b == 0){
            return false;
        }
        return a > c / b;
    }

    bool calc(ull n){ //can draw n
        if (n == 0){
            return true;
        }
        if (mul_greater(2*r, n, t)){
            return false;
        }
        auto s1 = 2*r*n;
        if (mul_greater(2*n - 1, n, t)){
            return false;
        }
        auto s2 = (2*n - 1)*n;
        return s1 + s2 <= t;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);

        ull min_use = 2*r;
        ull lo = 0, hi = t / min_use; 
        while (lo < hi){
            ull mid = (lo + hi + 1) / 2;
            if (calc(mid)){
                lo = mid;
            }else{
                hi = mid - 1;
            }
        }
        printf("%lld\n", lo);
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

