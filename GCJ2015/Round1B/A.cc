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

ll reverse_bit(ll x){
    int y = 0;
    while (x){
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}

ll pow10[18];
void pow_init(){
    pow10[0] = 1;
    for (int i = 1; i < 18; i++)
        pow10[i] = pow10[i-1] * 10;
}

int count(ll n){
    auto s = std::to_string(n);
    auto sz = s.size();
    if (sz == 1) return n;

    int l1 = sz / 2;
    int l2 = sz - l1;
    auto first_part = s.substr(0, l1);
    auto second_part = s.substr(l1, l2);
    auto f_n = stoll(first_part);
    auto s_n = stoll(second_part);
    auto f_n_rev = reverse_bit(f_n);
    if (f_n_rev == 1){ //like 100mxyz -> count(999999) + 1 + mxyz
        return count(f_n * pow10[l2] - 1) + 1 + s_n; 
    }
    if (s_n >= 1){ //like 321mxyz where mxyz >= 1 -> count(1000321) + 1 (reverse cost) + n - 3210001
        auto pre = pow10[sz - 1] + f_n_rev;
        return count(pre) + 1 + (n - reverse_bit(pre));
    }else{ 
        //like 3210000 -> count(1000023) + 1(reverse_cost) + n - 3200001
        //but if 2000000 -> count(1000001) + 0 (no need reverse) + n - 1000001
        f_n_rev = reverse_bit(f_n - 1);
        auto pre = pow10[sz - 1] + f_n_rev;
        return count(pre) + 1 + n - reverse_bit(pre) - (f_n_rev == 1);
    }
}

struct Problem{

    ll N;
    void read(){
        cin >> N;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        printf("%lld\n", count(N));
    }
};

int main(){
    int T;
    pow_init();
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}

