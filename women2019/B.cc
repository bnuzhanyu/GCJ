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

const int INC = 1;
const int DEC = -1;

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

    int N;
    VI mark;
    void read() {
        cin >> N;
        read_vec(mark, N+1);
    }

    bool determin(int& decOrInc, int& st, int idx) {
        if (idx - st == 1) {
            if (mark[idx] > mark[st]) {
                decOrInc = INC;
            } else if (mark[idx] == mark[st]) {
                st++;
                decOrInc = 0;
            } else {
                decOrInc = DEC;
            }
            return false;
        } else {
            if (decOrInc == INC && mark[idx] < mark[idx -1]) {
                st = idx;
                return true;
            } else if (decOrInc == DEC && mark[idx] > mark[idx - 1]) {
                st = idx;
                return true;
            }
            return false;
        }
    }

    void solve(int ca) {
        int ans = 0;
        bool can = false;
        int st = 0;
        int decOrInc = 0;
        bool last;
        FOR(i,1,N+1) {
            last = determin(decOrInc, st, i);
            if (last) {
                ans++;
            }
        }
        cout << "Case #" << ca << ": " << ans - 1 << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

