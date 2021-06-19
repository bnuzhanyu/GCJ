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

    int N, K;
    VI p;
    void read() {
        cin >> N >> K;
        read_vec(p, N);
    }

    int m1, m2;
    void add(int x) {
        if (x >= m1) {
            m2 = m1;
            m1 = x;
        }
        else if (x > m2) {
            m2 = x;
        }
    }

    void solve(int ca) {
        sort(p.begin(), p.end());
        m1 = m2 = 0;
        if (p[0] != 1) {
            add(p[0] - 1);
        }
        if (p.back() != K) {
            add(K - p.back());
        }

        int ans = 0;
        for (int i = 1; i < p.size(); i++) {
            int x = p[i] - p[i-1] - 1;
            add((x + 1) / 2);
            ans = max(ans, x);
        }
        ans = max(ans, m1 + m2);
        printf("Case #%d: %.7f\n", ca, (double)ans/K);
        //cout << "Case #" << ca << ": " << (double)ans / K << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

