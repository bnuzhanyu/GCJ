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

    int R,C,K;
    void read() {
        cin >> R >> C >> K;
    }

    
    void pstr(string s, int cnt) {
        if (cnt <= 0) {
            return;
        }
        FOR(i,0,cnt) {
            cout << s << endl;
        }
    }

    void solveOneColumn(int dead) {
        pstr("S", dead - 1);
        pstr("N", 1);
        pstr("S", R - dead);
    }

    string goDead(int d) {
        if (d == 1) {
            return "N";
        } else {
            return string(d-1,'E') + "W";
        }
    }

    string goOut(int k) {
        return string(k,'E');
    }
    void solveMultiColumn(int dead) {
        int row = dead / C;
        int left = dead % C;
        string fullDead = goDead(C);
        string fullOut = goOut(C);
        pstr(fullDead, row);
        if (left > 0) pstr(goDead(left) + goOut(C - left), 1);
        pstr(fullOut, R - row - (left > 0));
    }

    void solveNoDead() {
        pstr(goOut(C), R);
    }
    
    void solve(int ca) {
        cout << "Case #" << ca << ": ";
        int dead = R * C - K;
        if (dead == 1) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << "POSSIBLE" << endl;
            if (dead == 0) solveNoDead();
            else if (C == 1) solveOneColumn(dead);
            else solveMultiColumn(dead);
        }
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

