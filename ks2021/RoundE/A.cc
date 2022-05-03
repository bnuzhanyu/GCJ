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

    string s;
    string ori;
    void read() {
        cin >> s;
        ori = s;
    }

    int pos[5001];

    void solve(int ca) {
        VI mat[26];
        map<char, int> cnt;
        int m = 0;
        char mc = 0;
        for (int i = 0; i < ori.size(); i++) {
            char x = ori[i];
            cnt[x]++;
            mat[x - 'a'].push_back(i);
            if (cnt[x] > m) {
                m = cnt[x];
                mc = x;
            }
        }
        cout << "Case #" << ca << ": ";
        if (m > s.size() / 2) {
            cout << "IMPOSSIBLE" << endl;
            return;
        } 

        int idx = 0;
        for (int i = 0; i < ori.size(); i++) {
            if (mc == ori[i]) pos[idx++] = i;
        }

        idx = 0;
        for (int c = 0; c < 26; c++) {
            if (c == mc - 'a') continue;
            for (int i = 0; i < mat[c].size(); i++) {
                int p = mat[c][i];
                swap(s[p], s[pos[idx]]);
                pos[idx] = p;
                idx = (idx + 1) % m;
            }
        }
        cout << s << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

