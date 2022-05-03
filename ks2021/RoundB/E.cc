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

struct Comb {
    string s;
    int v;
    Comb() {

    }
    Comb(string _s, int _v) {
        s = _s;
        v = _v;
    }

    Comb gen(int nxt, int add) {
        Comb n;
        n.s = s;
        n.s.push_back('0'+nxt);
        n.v = v + add;
        return n;
    }

    bool operator<(const Comb& c) const {
        return v < c.v;
    }
};


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

    int N, M, P;
    VI sum;
    VI cost;
    unordered_set<string> forbid;
    void read() {
        cin >> N >> M >> P;
        sum.resize(P);
        forbid.clear();
        for (int i = 0; i < P; i++) {
            sum[i] = 0;
        }
        for (int i = 0; i < N; i++) {
            string str;
            cin >> str;
            for(int j = 0; j < P; j++) sum[j] += str[j]-'0';
        }

        for (int i = 0; i < M; i++) {
            string s;
            cin >> s;
            forbid.insert(s);
        }
    }

    void solve(int ca) {
        VEC<Comb> cand;
        int min_cost = 0;
        for (int i = 0; i < P; i++) {
            min_cost += min(N-sum[i], sum[i]);
        }
        cand.push_back(Comb("", 0));
        for (int i = 0; i < P; i++) {
            min_cost = min_cost - min(N-sum[i], sum[i]);
            VEC<Comb> v;
            for (Comb c : cand) {
                v.emplace_back(c.gen(0, sum[i]));
                v.emplace_back(c.gen(1, N - sum[i]));
            }
            sort(v.begin(), v.end());
            if (v.size() > M + 1)
                v.resize(M+1);
            swap(cand, v);
        }

        int ans = 0;
        for (Comb c : cand) {
            if (forbid.find(c.s) == forbid.end()) {
                ans = c.v;
                break;
            }
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

