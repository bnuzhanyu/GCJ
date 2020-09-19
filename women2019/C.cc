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

double step[501][501];

void init() {

    step[0][0] = 0;
    step[0][1] = step[1][0] = 3.0;
    step[1][1] = 4.0;
    for (int i = 2; i <= 500; i++) {
        step[0][i] = step[i][0] = (step[i-1][1] + step[i-1][0] * 2 + 6) / 3.0;
        step[i][1] = step[1][i] = 0.5*(step[i-1][1] + step[i][0]) + 1;
    }
    for (int i = 2; i <= 500; i++) {
        for (int j = i; j <= 500; j++) {
            step[i][j] = step[j][i] = 0.5 * (step[i-1][j] + step[j-1][i]) + 1;
        }
    }
}

class Problem {
public:
    int T;
    void go() {
        init();
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    int X, Y;
    void read() {
        cin >> X >> Y;
        X = abs(X);
        Y = abs(Y);
    }

    void solve(int ca) {

        cout << "Case #" << ca << ": ";
        printf("%.7f\n", step[X][Y]);
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

