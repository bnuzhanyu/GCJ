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

    int M, N;
    int p[101];
    void read() {
        cin >> M;
        N = 0;
        for (int i = 0; i < M; i++) {
            int tp,c;
            cin >> tp >> c;
            for (int j = 0; j < c; j++) {
                p[N++] = tp;
            }
        }
    }



    void solve(int ca) {
        ll maxAns = 0;
        for (int i = 0; i < (1<<N); i++) {
            ll sum = 0;
            for (int j = 0; j < N; j++) {
                if (i & (1<<j)) {
                    sum += p[j];
                }
            }
            ll tmp = sum;
            bool ok = true;
            for (int j = 0; j < N; j++) {
                if (!(i & (1<<j))) {
                    if (tmp % p[j] != 0) {
                        ok = false;
                        break;
                    }
                    tmp /= p[j];
                }
            }
            if (ok && tmp == 1) {
                maxAns = max(maxAns, sum);
            }
        }
        cout << "Case #" << ca << ": " << maxAns << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

