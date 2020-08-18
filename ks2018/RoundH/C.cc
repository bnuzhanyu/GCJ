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
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

using ll = long long;
using VI = vector<int>;
using VLL = vector<ll>;
using VVI = vector<VI>;
#define FOR(i,a,b) for( int i=(a); i<(b); ++i)
#define RANGE(i,n) for( int i=0; i<(n); ++i)

template<typename T>
using VEC = vector<T>;

template<typename T>
using MAT = vector<vector<T> >;

template<typename T>
void print(const VEC<T>& vec) {
    for (const auto& e : vec) cout << e << " ";
    cout << endl;
}

template<typename T>
void print_with_idx(const VEC<T>& vec) {
    FOR(i,0,vec.size()) {
        cout << i << ":" << vec[i] << endl;
    }
}

template<typename T>
void read_vec(VEC<T>& vec, int n, bool need_clear = true) {
    if (need_clear) vec.clear();
    FOR(i,0,n){
        T x; cin >> x;
        vec.push_back(x);
    }
}

template<typename T>
void read_mat(MAT<T>& mat, int r, int c) {
    mat.resize(r);
    FOR(i,0,r) {
        mat[i].resize(c);
        FOR(j,0,c) {
            cin >> mat[i][j];
        }
    }
}

const int MOD = 1000000007;
ll fact[200001] = {1};
ll inv[200001] = {1,1};

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

void init() {
    for (int i = 1; i <= 200000; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
        inv[i] = GetInv(i, MOD);
    }
}

class Problem {
public:
    int T;
    void go() {
        init();
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    int N, M;
    void read() {
        cin >> N >> M;
    }

    void solve(int ca) {
        ll ans = 0; 
        ll cmk = 1;
        ll pow2 = 1;
        int add = 1;
        for (int k = 0; k <= M; k++) {
            ll cur = (pow2 * fact[2*N - k])%MOD * cmk % MOD;
            ans = (ans + add*cur + MOD) % MOD;
            pow2 = (pow2*2) % MOD;
            cmk = (cmk * (M - k)) % MOD * inv[k + 1] % MOD;
            add = -add;
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

