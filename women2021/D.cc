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

    int ans[101][101];
    string B;

    int INF = 1000;
    int fun(int i, int j, char c) {
        if (ans[i][j] != INF) {
            return ans[i][j];
        }
        int x;
        if (i == j) {
            if (B[i] == c) return 1;
            else return -2;
        }

        char nxc = 'I' + 'O' - c;
        if (B[i] != c && B[j] != c) {
            x = -(j-i+1)-1;
        } else if (B[i] == c && B[j] == c) {
            x = max(-fun(i+1, j, nxc), -fun(i, j-1, nxc));
        } else if (B[i] == c) {
            x = -fun(i+1, j, nxc);
        } else if (B[j] == c) {
            x = -fun(i, j-1, nxc);
        }
        return ans[i][j] = x;
    }

    void read() {
        cin >> B;
        for (int i = 0; i < B.size() + 1; i++)
        for (int j = 0; j < B.size() + 1; j++)
            ans[i][j] = INF;
    }

    void solve(int ca) {
        int x = fun(0, B.size() - 1, 'I');
        char c = x > 0 ? 'I' : 'O';
        cout << "Case #" << ca << ": " << c << " " << abs(x) << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

