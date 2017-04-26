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

    int N, J;
    void read(){
        cin >> N >> J;
    }

    string to_bin(int x){
        string ret;
        while (x){
            ret.push_back(x&1 ? '1':'0');
            x >>= 1;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    long long to_base(int x, int b){
        long long ans = 0; 
        long long d = 1;
        while (x){
            if (x & 1) ans += d;
            d *= b;
            x >>= 1;
        }
        return ans;
    }

    void solve(int ca){
        printf("Case #%d:\n", ca);
        int x =  (1<<(N/2 - 1)) | 1;
        while (J--){
            auto s = to_bin(x);
            printf("%s%s", s.c_str(), s.c_str());
            for (int i = 2; i <= 10; i++){
                printf(" %lld", to_base(x, i));
            }
            printf("\n");
            x += 2;
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

