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

const int MN = 9000;
double logx[MN + 1];
int len[MN + 1];
void init() {
    const double log10 = log(10.0);
    for (int i = 1; i < MN + 1; i++) {
        logx[i] = log(i);  
    }
    
    for (int f = 1; f <= MN; f++) {
        double sum = 0;
        for (int i = MN; i > 0; i-=f) {
            sum += logx[i];
        }
        len[f] = int(sum / log10 + 1e-8) + 1;
    }
}

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        init();
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    int D;
    void read() {
        cin >> D;
    }

    void solve(int ca) {
        int flag = -1;
        for (int i = 1; i <= MN; i++) {
            if (len[i] < D) {
                flag = i;
                break;
            }
        }

        cout << "Case #" << ca << ": ";
        if (flag > 0) {
            cout << "IT'S OVER 9000" << string(flag, '!') << endl;
        } else {
            cout << "..." << endl;
        }
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

