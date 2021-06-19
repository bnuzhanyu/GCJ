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

template<typename T>
void fill(VEC<T>& v, T val) {
    std::fill(v.begin(), v.end(), val);
}

using PII = pair<int,int>;

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

class Problem {
public:
    bool not_visit(int x, int y) {
        return 0 <= x && x < R && 0 <= y && y < C && step[x][y] == -1;
    }

    MAT<int> step;
    void bfs() {
        step.resize(R);
        queue<PII> q;
        FOR(i,0,R) {
            step[i].resize(C);
            fill(step[i], -1);
        }

        FOR(i,0,R) {
            FOR(j,0,C) {
                if (matrix[i][j] == '1') {
                    q.push(make_pair(i,j));
                    step[i][j] = 0;
                }
            }
        }
        while (!q.empty()) {
            PII pos = q.front(); q.pop();
            int x = pos.first, y = pos.second;
            for (int d = 0; d < 4; d++) {
                int xx = x + dx[d];
                int yy = y + dy[d];
                if (not_visit(xx, yy)) {
                    step[xx][yy] = step[x][y] + 1;
                    q.push(make_pair(xx,yy));
                }
            }
        }
    }

    bool valid(int k) {
        int xy1 = 0;
        int xy2 = R+C+1;
        int xy3 = -R-C-1;
        int xy4 = R+C+1;
        bool isValid = true;
        FOR(i,0,R) {
            FOR(j,0,C) {
                if (step[i][j] > k) {
                    xy1 = max(xy1, i+j);
                    xy2 = min(xy2, i+j);
                    xy3 = max(xy3, i-j);
                    xy4 = min(xy4, i-j);
                    isValid = false;
                }
            }
        }
        if (isValid) return true;
        FOR(i,0,R) {
            FOR(j,0,C) {
                int v1 = abs(xy1 - (i + j));
                int v2 = abs(xy2 - (i + j));
                int v3 = abs(xy3 - (i - j));
                int v4 = abs(xy4 - (i - j));
                int s = max(max(v1,v2), max(v3,v4));
                if (s <= k) {
                    return true;
                }
            }
        }
        return false;
    }

    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    int R, C;
    VEC<string> matrix;
    void read() {
        cin >> R >> C;
        read_vec(matrix, R);
    }

    void solve(int ca) {
        bfs();
        int left = 0, right = R + C;
        while (left < right) {
            int mid = (left + right) / 2;
            if (valid(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        cout << "Case #" << ca << ": " << left << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

