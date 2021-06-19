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

using ll = long long;
ll ExtGcd(ll a, ll b, ll &x, ll &y) {
    if(!b) { x=1, y=0; return a;}
    ll d = ExtGcd(b, a%b, x, y), tmp = x; x = y, y = tmp - (a/b)*y;
    return d;
}

//a*ret = 1(mod m)
ll GetInv(ll a, ll m){
    ll d,x,y;
    d = ExtGcd(a,m,x,y);
    return d==1?(x%m+m)%m:-1;
}

struct Problem{
    long long R, C;
    const int MOD = 1000000007;

    ll cof[5], inv[5], order; 
    ll origin[5];
    
    ll function(int i){
        return origin[0] + origin[1]*i + origin[2]*i*i + origin[3]*i*i*i;
    }

    void init(){
        order = 3;
        origin[0] = 0;
        origin[1] = (R*C) % MOD;
        origin[2] = (-(R + C)) % MOD + MOD;
        origin[3] = 1;

        for(int i=0; i<=order; ++i) 
            cof[i] = function(i);         
        inv[0] = 1;
        for(int i = 1; i <= order; i++) {
            inv[i] = GetInv(i+1, MOD);//如果没有逆元,那是变态啊。。
            for(int j = order; j >= i; j--) 
                cof[j] -= cof[j - 1]; 
        }
    }

    ll calc(ll n) // f(0)+f(1)+...f(n)
    {
        int i; 
        ll res = 0;
        for(i = order; i >= 0; i--) {
           res += cof[i], res %= MOD;
           res *= (n - i + 1) % MOD * inv[i] % MOD;
           res %= MOD;
        }
        while(res < 0) res += MOD;
        return res;
    }

    void read(){
        cin >> R >> C;
    }

    void solve(int ca){
        init();
        printf("Case #%d: ", ca);
        long long ans = calc(min(R,C));
        printf("%lld\n", ans);
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

