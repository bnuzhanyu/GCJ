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

const unsigned MMM = 1<<16;
VI adj[MMM];
unsigned rvs(unsigned x) {
    if (x == 0) return 1;
    int b = 0;
    unsigned mask = 0;
    unsigned ori = x;
    while(x != 1) {
        x >>= 1;
        mask=mask*2 + 1;
        b++;
    }
    return (~ori) & mask;
}

void build() {
    for (unsigned i = 0; i < 1<<16; i++) {
        if (i * 2 < MMM) adj[i].push_back(i*2);
        unsigned r = rvs(i);
        if (r < MMM) adj[i].push_back(r);
    }
}

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        build();
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    int bit(string x) {
        int v = 0;
        for (auto c : x) {
            v = v * 2 + c - '0';
        }
        return v;
    }

    string S, E;
    void read() {
        cin >> S >> E;
    }

    VEC<bool> vis;
    int bfs(int s, int e) {
        vis.resize(MMM);
        fill(vis.begin(), vis.end(), false);
        vis[s] = true;
        queue<pair<int, int>> q;
        q.push(make_pair(s, 0));
        while(!q.empty()) {
            auto c = q.front();
            //cout << "cur:" << c.first << " " << c.second<< endl;
            if (c.first == e) {
                return c.second;
            }
            q.pop();
            for (auto nx : adj[c.first]) {
                if (!vis[nx]) {
                    vis[nx] = true;
                    q.push(make_pair(nx, c.second+1));
                }
            }
        }
        return -1;
        
    }
    void solve(int ca) {
        cout << "Case #" << ca << ": ";
        int s = bit(S), e = bit(E);
        int step = bfs(s, e);
        if (step == -1) cout << "IMPOSSIBLE" << endl;
        else cout << step << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

