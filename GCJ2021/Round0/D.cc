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
    int T, N , Q;
    void go() {
        cin >> T >> N >> Q;
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    void read() {
    }

    int query(int i, int j, int k) {
        cout << i << " " << j << " " << k << endl;
        int m;
        cin >> m;
        return m;
    }

    int ans[52];
    void insert_at(int id, int val) {
        for (int i = N - 1; i >= id; i--) {
            ans[i] = ans[i-1];
        }
        ans[id] = val;
    }

    int output() {
        for (int i = 0; i < N; i++) {
            cout << ans[i];
            if (i != N - 1) {
                cout << " ";
            }
        }
        cout << endl;
        int r;
        cin >> r;
        return r;
    }

    int query_interval(int st, int ed, int cur) {
        /*
        cout << "q interval: " << st << " " << ed << " and " << cur << endl;
        for (int i = 0; i < cur - 1; i++) {
            cout << ans[i] << ",";
        }
        cout << endl;
        */
        int v0 = ans[st];
        int v1 = ans[st + 1];
        int v2 = ans[st + 2];
        if (ed - st == 2) {
            int m = query(v0, v1, cur);
            if (m == v0) return st;
            if (m == cur) return st + 1; 
            else return st + 2;
        }
        if (ed - st == 3) {
            int m = query(v0, v1, cur);
            if (m == v0) return st;
            if (m == cur) return st + 1;
            return query_interval(st + 1, ed, cur);
        } 
        else {
            int mid1 = st + (ed - st) / 3;
            int mid2 = st + (ed - st) * 2 / 3;
            int m = query(ans[mid1], ans[mid2], cur);
            if (m == ans[mid1]) {
                if (mid1 - st == 1) mid1 += 1;
                return query_interval(st, mid1, cur);
            } else if (m == cur) {
                if (mid2 - mid1 == 1) mid2 += 1;
                return query_interval(mid1, mid2 + 1, cur);
            } else {
                if (ed - mid2 == 1) mid2 -= 1;
                return query_interval(mid2, ed, cur);
            }
        }
    }

    void solve(int ca) {
        int m = query(1, 2, 3);
        ans[0] = (m == 1) ? 2 : 1;
        ans[1] = m;
        ans[2] = (m == 3) ? 2 : 3;

        for (int x = 4; x <= N; x++) {
            int v = query_interval(0, x - 1, x);
            insert_at(v, x);
        }
        int v = output();
        if (v != 1) exit(1);
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

