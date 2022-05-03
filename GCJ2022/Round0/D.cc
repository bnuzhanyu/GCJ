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

    int N;
    VI val;
    VI pt;
    MAT<int> son;
    void read() {
        cin >> N;
        read_vec(val, N);
        read_vec(pt, N);
        son.clear();
        son.resize(N+1);
        for (int i = 0; i < N; i++) {
            son[pt[i]].push_back(i+1);
        }
    }

    pair<ll,ll> dfs(int c) {
        ll cur_val = (c == 0) ? 0 : val[c-1];
        if (son[c].size() == 0) {
            return make_pair(cur_val, cur_val);
        }
        ll min_son = 1L<<60;
        ll sum = 0;
        int min_son_id = -1;
        for (int i = 0; i < son[c].size(); i++) {
            pair<ll,ll> pp = dfs(son[c][i]);
            ll s1 = pp.first;
            ll s2 = pp.second;
            sum += s1;
            if (min_son > s2) {
                min_son_id = son[c][i];
                min_son = s2;
            }
        }
        ll r = max(min_son, cur_val) + sum - min_son;
        return make_pair(r, max(min_son, cur_val));
    }

    void solve(int ca) {
        cout << "Case #" << ca << ": " << dfs(0).first << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

