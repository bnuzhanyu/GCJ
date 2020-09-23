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

    ll free(int v) {
        ll ans = 0;
        for (int i = -v; i <= v; i++) {
            int low = max(0, i) - v;
            int high = min(0, i) + v;
            ans += high - low + 1;
        }
        return ans;
    }

    ll getThird(int i, int j, int k, int v) {
        int low = max(0, max(i, j) - v);
        int high = min(k, min(i, j) + v);
        return high - low + 1;
    }

    ll calc(int c, int k, int v) {
        ll ans = 0;
        for (int i = 0; i <= c; i++) {
            for (int j = max(0, i - v); j <= min(k, i + v); j++) {
                ans += getThird(i, j, k, v); 
            }
        }
        return ans;
    }

    int V,K;
    void read() {
        cin >> K >> V;
    }

    void solve(int ca) {
        ll ans;
        if (K > 2 * V) {
            ans = calc(V - 1, K, V) * 2 + (K + 1 - 2 * V) * free(V);
        } else {
            ans = calc(K, K, V);
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

