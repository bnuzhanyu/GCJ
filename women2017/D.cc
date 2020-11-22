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

    int B;
    MAT<ll> dis;
    MAT<ll> path;
    void read() {
        cin >> B;
        dis.resize(B);
        FOR(i,0,B) dis[i].resize(B);
        dis[0][0] = 0;
        for (int i = 1; i < B; i++) {
            dis[i][i] = 0;
            for (int k = 0; k < i; k++) {
                ll x;
                cin >> x;
                dis[i][k] = dis[k][i] = 2 * x;
            }
        }
        path = dis;
    }

    void floyd() {
        FOR(k,0,B) {
            FOR(i,0,B) {
                FOR(j,0,B) {
                    if (dis[i][k] >= 0 && dis[k][j] >=0) {
                        if (dis[i][j] < 0 || dis[i][k] + dis[k][j] < dis[i][j]) {
                            dis[j][i] = dis[i][j] = dis[i][k] + dis[k][j];
                        }
                    }
                }
            }
        }
    }

    bool isOK(ll d, int a, int b) {
        ll ab = path[a][b];
        VEC<pair<ll,ll>> cover;
        for (int i = 0; i < B; i++) {
            if (dis[i][a] > d && dis[i][b] > d) return false;
            if (d - dis[i][a] + d - dis[i][b] >= ab) {
                continue;
            }
            cover.push_back(make_pair(d - dis[i][a] + 1, ab - d + dis[i][b] - 1));
        }
        if (cover.size() == 0) {
            return true;
        }
        sort(cover.begin(), cover.end());
        ll v = 0;
        for (auto& p : cover) {
            if (p.first > v) return true;
            v = max(v, p.second);
        }
        return v < ab;
    }

    ll minDis(int a, int b, ll curMin) {

        ll low = 0;
        ll high = 0;
        for (int i = 0; i < B; i++) {
            low = max(low, min(dis[i][a], dis[i][b]));
            high = max(high, dis[i][a] + path[a][b]);
            high = max(high, dis[i][b] + path[a][b]);
        }
        low = min(curMin, low);
        high = min(curMin, high);
        while (low < high) {
            ll mid = (low + high) / 2;
            if(isOK(mid, a, b)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }

    void solve(int ca) {
        floyd();
        ll minAns = 1L<<50;
        FOR(i,0,B) {
            FOR(j,0,i) {
                if (path[i][j] > 0) {
                    minAns = min(minAns, minDis(i,j,minAns));
                }
            }
        }
        cout << "Case #" << ca << ": ";
        printf("%.8f\n", minAns / 2.0);
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

