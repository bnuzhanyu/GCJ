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

struct PNUM {
    int s;
    int p;
    int flag;
    bool operator<(const PNUM& r) const {
        if (s == r.s) return flag < r.flag;
        return s < r.s;
    }
};

const int MOD = 1000002013;
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

    ll cost(ll N, ll st_num) {
        return (2 * N - st_num + 1) * st_num / 2; 
    }

    int N, M;
    VEC<PNUM> people;
    ll origin;
    void read() {
        cin >> N >> M;
        people.clear();
        origin = 0;
        for (int i = 0; i < M; i++) {
            int p,e,o;
            cin >> o >> e >> p;
            origin += cost(N, e - o) % MOD * p % MOD;
            origin %= MOD;
            PNUM pi;
            pi.s = o;
            pi.p = p;
            pi.flag = 0;
            people.push_back(pi);
            PNUM px;
            px.s = e;
            px.p = p;
            px.flag = 1;
            people.push_back(px);
        }
    }

    void solve(int ca) {
        sort(people.begin(), people.end());
        VEC<PNUM> stk;
        ll total = 0;
        for (auto& pe : people) {
            if (pe.flag == 0) {
                stk.push_back(pe);
            } else {
                int curP = pe.p;
                int station = pe.s;
                while (curP > 0) {
                    auto& c = stk.back();
                    int minus = min(c.p, curP); 
                    curP -= minus;
                    c.p -= minus;
                    total += cost(N, station - c.s) % MOD * minus;
                    total %= MOD;
                    if (c.p == 0) stk.pop_back();
                }
            }
        }
        cout << "Case #" << ca << ": " << (origin - total + MOD) % MOD << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

