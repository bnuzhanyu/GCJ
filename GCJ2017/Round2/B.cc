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

template<typename T>
using VEC = vector<T>;

template<typename T>
void fill_vec(VEC<T>& vec, int n, T val) {
    vec.resize(n);
    fill(vec.begin(), vec.end(), val);
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

    int N, C, M;
    VI tOfB;
    VI tOfP;

    void read() {
        cin >> N >> C >> M;
        fill_vec(tOfB, C, 0);
        fill_vec(tOfP, N, 0);
        int p,b;
        for (int i = 0; i < M; i++){
            cin >> p >> b;
            p--,b--;
            tOfB[b]++;
            tOfP[p]++;
        }
    }

    void solve(int ca) {
        int r = 0;
        for (auto bc : tOfB) r = max(r, bc);
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            cnt += tOfP[i];
            r = max(r, (cnt + i) / (i + 1));
        }

        int pro = 0;
        for (int i = 0; i < N; i++) {
            int c = tOfP[i];
            if (c > r) {
                pro += c - r;
            }
        }
        cout << "Case #" << ca << ": " << r << " " << pro << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

