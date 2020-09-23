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

ll ans[26][26];
void init() {
    memset(ans, -1, sizeof(ans));
}

ll dfs(int r, int c) {
    if (r == 1 || c == 1) return 1;
    if (ans[r][c] != -1) {
        return ans[r][c];
    }
    ll s = 0;
    for (int i = 1; i <= r; i++) {
        s += dfs(c-1, i);
    }
    return ans[r][c] = s;
}

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        init();
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    int R,C;
    void read() {
        cin >> R >> C;
    }

    void solve(int ca) {
        cout << "Case #" << ca << ": " << dfs(R, C) << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

