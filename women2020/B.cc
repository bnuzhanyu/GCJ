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

const int LEFT = 0;
const int RIGHT = 1;
const int NONE = -1;
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
    VI order;
    VI p;
    VI mark;
    void init() {
        mark.resize(N);
        fill(mark.begin(), mark.end(), -1);
    }

    void mk_pair() {
        p.resize(N);
        for (int i = N%2; i < N; i+=2) {
            p[order[i]] = order[i+1];
            p[order[i+1]] = order[i];
        }
    }

    void read() {
        cin >> N;
        read_vec(order, N);
        FOR(i,0,N) order[i]--;
        init();
    }

    void dfs(int x, int d) {
        mark[x] = d;
        if (mark[x^1] == -1) dfs(x^1, d^1);
        if (mark[p[x]] == -1) dfs(p[x], d^1);
    }

    void solve(int ca) {
        mk_pair();
        if (N & 1) {
            mark[order[0]] = LEFT;
            if (order[0] != N - 1) {
                dfs(order[0] ^ 1, RIGHT);
                dfs(N-1, LEFT);
            }
        }

        for (int i = N%2; i < N; i++) {
            int o = order[i];
            if (mark[o] == -1) dfs(o, LEFT);
        }

        string ans;
        FOR(i,0,N) {
            ans += mark[i] == 0 ? 'L':'R'; 
        }

        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

