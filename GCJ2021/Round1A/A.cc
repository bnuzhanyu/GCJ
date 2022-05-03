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

    int prefix_cmp(string& a, string& b) {
        int x = a.size();
        int y = b.size();
        for (int i = 0; i < y; i++) {
            if (a[i] < b[i]) return -1;
            if (a[i] > b[i]) return 1;
        }
        return 0;
    }

    void append0(string& b, int count) {
        for (int i = 0; i < count; i++) {
            b.push_back('0');
        }
    }

    int comp(string a, string& b) {
        if (a.size() < b.size()) {
            return 0;
        }

        if (a.size() == b.size()) {
            if (a < b) return 0;
            if (a >= b) {
                b.push_back('0');
                return 1;
            }
        }
        int c = prefix_cmp(a, b);
        int ret = a.size() - b.size();
        if (c == 0) {
            for (int i = b.size(); i < a.size(); i++) {
                if (a[i] != '9') {
                    b = a;
                    for (int j = b.size() - 1; ; j--) {
                        if (b[j] != '9') {
                            b[j]++;
                            for (int k = j+1; k < b.size(); k++) b[k] = '0';
                            return ret;
                        }
                    }
                }
            }
            ret += 1;
        }
        if (c > 0) ret += 1;
        append0(b, ret);
        return ret;
    }

    int N;
    void read() {
        cin >> N;
    }

    void solve(int ca) {
        string x, y;
        cin >> x;
        int s = 0;
        for (int i = 1; i < N; i++) {
            cin >> y;
            int v = comp(x, y);
            s += v;
            cout << "x="  << x << " y=" << y << " v=" << v << endl;
            x = y;
        }
        cout << "Case #" << ca << ": " << s << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}


