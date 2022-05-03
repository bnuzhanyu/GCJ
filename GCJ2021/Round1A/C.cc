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

    int N, Q;
    string ans[3];
    int cor[3];
    void read() {
        cin >> N >> Q;
        for(int i = 0; i < N; i++) {
            cin >> ans[i] >> cor[i];
        }
    }


    void solve(int ca) {
        string myans;
        cout << "Case #" << ca << ": ";
        if (N == 1) {
            if (cor[0] * 2 < Q) {
                for (int i = 0; i < Q; i++) {
                    ans[0][i] = ans[0][i] == 'T' ? 'F' : 'T';
                }
                cor[0] = Q - cor[0];
            }
            cout << ans[0] << " " << cor[0] << "/1" << endl;
        }

        if (N == 2) {
            if (cor[1] > cor[0]) {
                swap(cor[1], cor[0]);
                swap(ans[1], ans[0]);
            }

            int s = 0, d = 0;
            for (int i = 0; i < Q; i++) {
                if (ans[0][i] == ans[1][i]) s++;
                else d++;
            }

            int dt = (cor[0] - cor[1] + d) / 2; 
            int df = d - dt;
            int st = cor[0] - dt;
            bool need_rev = (st * 2 < s);

            int exp = max(st, s - st) + dt;

            for (int i = 0; i < Q; i++) {
                if (ans[0][i] == ans[1][i] && need_rev) {
                    ans[0][i] = ans[0][i] == 'T' ? 'F' : 'T';
                }
            }
            cout << ans[0] << " " << exp << "/1" << endl;
        }
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

