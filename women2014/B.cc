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

    ll A,B,a,b,Y;
    void read() {
        cin >> A>>B>>a>>b>>Y;
    }

    bool next() {
        int da = A / 100, db = B / 100;
        int match = min(A,B) * 2 / 100;
        int ia = match * a / 100;
        int ib = match * b / 100;
        int left = (match - ia - ib);
        int la = left / 2;
        int lb = left - la;
        int na = A - da + ia + la;
        int nb = B - db + ib + lb;
        bool ret = A!=na || B!=nb;
        A = na;
        B = nb;
        return ret;
    }

    void solve(int ca) {
        while (Y--) {
            if (!next()) {
                break;
            }
        }
        cout << "Case #" << ca << ": " << A << " " << B << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

