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
#include <climits>
using namespace std;

using ull = unsigned long long;
using VI = vector<int>;
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
    ull p10[20];
    int T;
    void go() {
        cin >> T;
        p10[1] = 1;
        for (int i = 2; i < 20; i++) {
            p10[i] = p10[i-1]*10;
        }
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    string Y;
    ull y;
    int len;
    void read() {
        cin >> y;
        Y = to_string(y); 
        len = Y.size();
    }
    
    string gen(ull st, int n) {
        string x;
        for (int i = 0; i < n; i++) {
            x += to_string(st + i);
        }
        return x;
    }

    string gen(int l1, int n1, int l2, int n2) {
        ull st = p10[l2];
        string x;
        for (int i = 0; i < n1; i++) {
            x += to_string(st - n1 + i);
        }
        for (int i = 0; i< n2; i++) {
            x += to_string(st+i);
        }
        return x;
    }

    ull calc(int l, int n) {
        string x = Y.substr(0, l); 
        ull m = stoull(x);
        string z = gen(m, n);
        string z2 = gen(m+1, n);
        string z3 = gen(p10[l], n);
        ull ans = ULLONG_MAX;
        if (z.size() == l * n && stoull(z) > y) {
            ans = min(ans, stoull(z));
        }
        if (z2.size() == l * n && stoull(z2) > y) {
            ans = min(ans, stoull(z2));
        }
        if (z3.size() == l * n && stoull(z3) > y) {
            ans = min(ans, stoull(z3));
        }
        return ans;
    }

    ull calc(int l1, int n1, int l2, int n2) {
        string x = gen(l1, n1, l2, n2);
        ull ans = stoull(x);
        if (ans > y) return ans;
        return ULLONG_MAX;
    }
    
    bool split(int l, int l1, int l2, int&n1, int &n2) {
        for (int i = 1; i <= min(9,l / l1); i++)
        for (int j = 1; j <= min(9,l / l2); j++) {
            if (l1 * i + l2 * j == l) {
                n1 = i, n2 = j;
                return true;
            }
        }
        return false;
    }

    ull getOfLen(int length) {
        ull ans = ULLONG_MAX;
        for (int i = 1; i <= length; i++) {
            if (length % i == 0) {
                if (length / i <= 9 && length / i >= 2) ans = min(ans, calc(i, length / i));
            }
            for (int n1 = 1; n1 <= min(9,length / i); n1++)
            for (int n2 = 1; n2 <= min(9,length / (i+1)); n2++) {
                if (n1 * i + n2 *(i+1) == length) ans = min(ans, calc(i, n1, i+1, n2));
            }
        }
        return ans;
    }

    ull getAns() {
        if (len == 1) {
            return 12;
        }
        ull ans = getOfLen(len);
        if (ans != ULLONG_MAX) return ans;
        return getOfLen(len + 1);
    }
    

    void solve(int ca) {
        cout << "Case #" << ca << ": " << getAns() << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

