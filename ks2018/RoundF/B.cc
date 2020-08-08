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
#include <unordered_map>
#include <unordered_set>
using namespace std;


struct DIST {
    int u;
    int d;
    int v;

    void update(int _v, int _d) {
        if (_d < d) {
            v = _v;
            d = _d;
        }
    }

    DIST(int _u) {
        u = _u;
        v = -1;
        d = 1<<20;
    }

    bool operator<(const DIST& o) const {
        return d < o.d;
    }
};

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    vector<DIST> vec;
    int V, E;
    int zeroA, zeroB;
    bool isZero(int u) {
        return u == zeroA || u == zeroB;
    }
    void read() {
        cin >> V >> E;
        vec.clear();
        for (int i = 0; i < V; i++) {
            vec.push_back(DIST(i));
        }
        zeroA = -2;
        zeroB = -2;
        for (int i = 0; i < E; i++) {
            int u,v,d;
            cin >> u >> v >> d;
            u--, v--;
            vec[u].update(v, d);
            vec[v].update(u, d);
            if (d == 0) {
                zeroA = u;
                zeroB = v;
            }
        }
    }


    void solve(int ca) {
        read();
        sort(vec.begin(), vec.end());
        vector<bool> isOk;
        for (int i = 0; i < V; i++) {
            isOk.push_back(false);
        }

        int cnt = 0;
        for (auto& dist: vec) {
            if ((!isZero(dist.u) && isZero(dist.v)) || !isOk[dist.v]) {
                cnt++;
            }
            isOk[dist.u] = true;
            isOk[dist.v] = true;
        }
        cout << "Case #" << ca << ": " << (1LL<<cnt) << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

