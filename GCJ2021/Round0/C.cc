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

    int ans[300];

    int N,C;
    void read() {
        cin >> N >> C;
    }

    bool make(int cur, int left) {
        if (cur == N) {
            ans[0] = cur;
            return left == 0;
        }
        if (left < N - cur) {
            return false;
        }
        int dest_pos = min(N - cur + 1, left - (N - 1 - cur));
        left -= dest_pos; 
        bool ok = make(cur + 1, left);
        if (!ok) {
            return false;
        }
        for (int i = N - 1; i > 0; i--) {
            ans[i] = ans[i - 1];
        }
        ans[0] = cur;
        reverse(ans, ans + dest_pos);
        return true;
    }

    void solve(int ca) {
        bool ok = make(1, C);
        
        cout << "Case #" << ca << ":";
        if (ok) {
            for (int i = 0; i < N; i++) {
                cout << " " << ans[i];
            }
            cout << endl;
        } else {
            cout << " IMPOSSIBLE" << endl;
        }
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

