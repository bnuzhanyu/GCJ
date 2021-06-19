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
const int INF = 1 << 29;

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

    int N;
    int X, Y;
    string cj;
    VI dp[2];
    void read() {
        cin >> X >> Y >> cj;
    }

    void solve(int ca) {
        int sz = cj.size();
        dp[0].resize(sz+1);
        dp[1].resize(sz+1);
        dp[0][0] = 0;
        dp[1][0] = 0;
        int st = 0;
        if (cj[0] == '?') {
            dp[0][1] = 0;
            dp[1][1] = 0;
        } else {
            dp[0][1] = (cj[0] == 'C') ? 0 : INF;
            dp[1][1] = (cj[0] == 'J') ? 0 : INF;
        }
        for (int i = 1; i < sz; i++) {
            dp[0][i+1] = INF;
            dp[1][i+1] = INF;
            if (cj[i] == '?' || cj[i] == 'C') {
                dp[0][i+1] = min(dp[0][i], dp[1][i] + Y);
            } 
            if (cj[i] == '?' || cj[i] == 'J') {
                dp[1][i+1] = min(dp[1][i], dp[0][i] + X);
            }
        }
        cout << "Case #" << ca << ": " << min(dp[0][sz], dp[1][sz]) << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

