#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <stack>
#include <queue>
#include <stdio.h>
#include <cmath>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

typedef long long ll;

ll pow_mod(ll x, ll n, ll m) {
    ll ret = 1;
    ll d = x;
    while(n > 0) {
        if (n & 1) {
            ret = ret * d % m;
        }
        d = d * d % m;
        n >>= 1;
    }
    return ret;
}

ll ExtGcd(ll a, ll b, ll &x, ll &y) {
    if(!b) { x=1, y=0; return a;}
    ll d = ExtGcd(b, a%b, x, y), tmp = x; 
    x = y, y = tmp - (a/b)*y;
    return d;
}

ll GetInv(ll a, ll m){
    ll d,x,y;
    d = ExtGcd(a,m,x,y);
    return d==1?(x%m+m)%m:-1;
}

ll A[1000010];
ll S[1000010];
ll inv[1000010];

const int MOD = 1000000007;

void initInv() {
    for (int i = 1; i <= 1000000; i++) {
        inv[i] = GetInv(i, MOD);
    }
}

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    ll N, K, x, y, C, D, E1, E2, F;

    void read() {
        cin >> N >> K >> x >> y >> C >> D >> E1 >> E2 >> F;
        A[0] = (x + y) % F;
        for (int i = 1; i < N; i++) {
            ll nx = (C * x + D * y + E1) % F;
            ll ny = (D * x + C * y + E2) % F;
            A[i] = (nx + ny) % F;
            x = nx, y = ny;
        }

        ll sum = 0;
        for (int i = N - 1; i >= 0; i--) {
            sum += A[i] * (N - i);
            sum %= MOD;
            S[i] = sum;
        }
    }


    void solve(int ca) {
        read();
        ll sum = S[0] * K % MOD;
        for (int i = 1; i < N; i++){
            sum += (S[i] * ((i + 1) * (pow_mod(i+1, K, MOD) - 1) % MOD) % MOD * ((inv[i] + MOD) % MOD)) % MOD;
            sum %= MOD;
        }
        cout << "Case #" << ca << ": " << sum << endl;
    }
};

int main() {
    initInv();
    Problem p;
    p.go();
    return 0;
}

