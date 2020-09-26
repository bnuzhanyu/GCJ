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

    int L;
    string A, B, C;

    set<pair<char,char>> lessThan;
    void cmp(string&a, string&b) {
        FOR(i,0,L) {
            if (a[i] != b[i]) {
                lessThan.insert(make_pair(a[i],b[i]));
                return;
            }
        }
    }

    bool ok(string& left,string&mid, string&right) {
        lessThan.clear();
        cmp(left, mid);
        cmp(mid, right);
        cmp(left, right);
        set<pair<char,char>> lt;
        for (auto & p1 : lessThan) {
            lt.insert(make_pair(p1.first, p1.second));
            for (auto &p2 : lessThan) {
                if (p1.second == p2.first) {
                    lt.insert(make_pair(p1.first, p2.second));
                }
                if (p1.first == p2.first || p1.second == p2.second) {
                    lt.insert(make_pair(p1.first, p2.second));
                    lt.insert(make_pair(p2.first, p1.second));
                }
            }
        }
        for (auto &p1:lt)
        for (auto &p2:lt) 
            if (p1.first == p2.second && p1.second == p2.first) return false;
        return true;
    }
    
    string canBeMiddle(string&mid, string&x, string&y) {
        if (ok(x,mid,y) || ok(y,mid,x)) {
            return " YES";
        } else {
            return " NO";
        }
    }

    void read() {
        lessThan.clear();
        cin >> L;
        cin >> A >> B >> C;
    }

    void solve(int ca) {
        cout << "Case #" << ca << ":" << canBeMiddle(A, B, C) << canBeMiddle(B, A, C) << canBeMiddle(C, A, B) << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

