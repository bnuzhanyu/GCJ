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

    long long N;
    void read(){
        cin >> N;
    }

    int digits[20];
    int mx[20];
    int dn; 
    void get_digits(ll x){
        dn = 0;
        while (x){
            digits[dn++] = x % 10;
            x /= 10;
        }
        mx[dn-1] = digits[dn-1];
        for (int i = dn - 2; i >= 0; i--){
            mx[i] = max(mx[i+1], digits[i]);
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        get_digits(N);
        for (int i = 0; i < dn-1; i++){
            if (digits[i] < mx[i+1]){
                for (int j = i; j >= 0; j--)
                    digits[j] = 9;
                digits[i+1]--;
            }
        }
        int st = dn - 1;
        if (digits[dn-1] == 0){
            st--;
        }
        for (int i = st; i >= 0; i--){
            printf("%d", digits[i]);
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

