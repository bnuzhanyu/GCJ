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

    int D, K , N;
    void read() {
        cin >> D >> K >> N;
    }

    int posK(int k) {
        if (k % 2 == 0) k = (k + N) % D;
        else k = (k - N + D) % D;
        return k;
    }

    int rev(int pos) {
        int x = pos & 1;
        int y = N & 1;
        if (x != y) return (pos + N) % D;
        else return (pos - N + D) % D;
    }

    void solve(int ca) {
        N %= D;
        K--;
        int pk = posK(K);
        int p1 = (pk + 1) % D;
        int p2 = (pk + D - 1) % D;
        int x = rev(p1) + 1;
        int y = rev(p2) + 1;
        cout << "Case #" << ca << ": " << x << " " << y << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

