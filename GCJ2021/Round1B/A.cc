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

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    ll ST = 1000000000LL;
    ll CIRCLE_T = 12LL * 60 * 60 * ST;

    
    ll ok(ll h, ll m, ll s, ll ht, ll mt, ll st) {
        ll x = (mt - ht - (m*60 + s)*12*ST + (h*3600 + m*60 + s)*ST) % CIRCLE_T;
        ll y = (st - ht - s*720*ST + (h*3600 + m*60 + s)*ST) % CIRCLE_T;
        if (x % 11 != 0 || y % 719 != 0) return -1;
        if (x < 0) x += CIRCLE_T;
        if (y < 0) y += CIRCLE_T;
        if (x / 11 < ST && y / 719 < ST) {
            cout << h << " " << m << " " << s << " " << x / 11 << endl; 
            return 0;
        }
        return -1;
    }

    ll ok(ll h, ll m, ll s) {
        ll ns;
        ns = ok(h, m, s, A, B, C);
        if (ns >= 0) return true; 
        ns = ok(h, m, s, A, C, B);
        if (ns >= 0) return true; 
        ns = ok(h, m, s, B, A, C);
        if (ns >= 0) return true; 
        ns = ok(h, m, s, B, C, A);
        if (ns >= 0) return true; 
        ns = ok(h, m, s, C, A, B);
        if (ns >= 0) return true; 
        ns = ok(h, m, s, C, B, A);
        if (ns >= 0) return true; 
        return false;
    }

    int N;
    ll A, B, C;
    void read() {
        cin >> A >> B >> C;
    }

    void solve(int ca) {
        cout << "Case #" << ca << ": ";
        for (int h = 0; h < 12; h++)
        for (int m = 0; m < 60; m++)
        for (int s = 0; s < 60; s++) {
            //ok(h,m,s);
            if (ok(h,m,s)) return;
        }
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

