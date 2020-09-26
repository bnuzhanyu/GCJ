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
                int x;
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
                            dis[i][j] = dis[i][k] + dis[k][j];
                        }
                    }
                }
            }
        }
    }

    bool isOK(ll d, int a, int b) {
        ll da = path[a][b];
        ll db = path[a][b];
        for (int i = 0; i < B; i++) {
            if (dis[i][a] > d && dis[i][b] > d) return false;
            if (dis[i][a] > d) db = min(db, d - dis[i][b]);
            if (dis[i][b] > d) da = min(da, d - dis[i][a]);
        }
        
        ll toB = path[a][b] - da;
        ll toA = path[a][b] - db;

        bool canFromA = true;
        for (int i = 0; i < B; i++) {
            bool ok = dis[i][a] + da <= d || dis[i][b] + toB <= d;
            if(!ok) {
                canFromA = false; break;
            }
        }
        if (canFromA) return true;

        bool canFromB = true;
        for (int i = 0; i < B; i++) {
            bool ok = dis[i][b] + db <= d || dis[i][a] + toA <= d ;
            if(!ok) {
                canFromB = false; break;
            }
        }
        if (canFromB) return true;
        return false;
    }

    ll minDis(int a, int b) {

        ll low = 0;
        ll high = 0;
        for (int i = 0; i < B; i++) {
            low = max(low, min(dis[i][a], dis[i][b]));
            high = max(high, dis[i][a]);
            high = max(high, dis[i][b]);
        }
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
                    minAns = min(minAns, minDis(i,j));
                }
            }
        }
        cout << "Case #" << ca << ": ";
        printf("%.7f\n", minAns / 2.0);
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}


