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

int maxBit(int v) {
    int cnt = 0;
    while (v) {
        v >>= 1;
        cnt++;
    }
    return cnt;
}

int bitCount(int x) {
    int cnt = 0;
    while (x) {
        cnt += (x&1);
        x >>= 1;
    }
    return cnt;
}

class Problem {
public:
    int T;
    int N;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }


    void read() {
        cin >> N;
    }

    int r, c, dir;
    int K, V, LEFT;
    void search() {
        for (int v = N; v > 0; v--) {
            int k = maxBit(v);
            int b = bitCount(v);
            if (k - b + v <= N) {
                K = k;
                V = v;
                LEFT = N - v - (k - b);
                return;
            }
        }
    }

    void printRow() {
        int st = 1, ed = r;
        if (dir == -1) {
            swap(st, ed);
        }
        for (int i = st, j = 0; j < r; j++, i += dir) {
            cout << r << " " << i << endl;
        }
        r = r + 1;
        dir = -dir;
        c = (dir == 1) ? 1 : r;
    }

    void nextRow() {
        cout << r << " " << c << endl;
        r = r + 1;
        if (c != 1) {
            c = c + 1;
        }
    }

    void solve(int ca) {
        read();
        search();
        cout << "Case #" << ca << ":" << endl;
        r = 1;
        c = 1;
        dir = 1;
        for (int i = 0; i < K; i++) {
            if ((V & (1 << i)) != 0) {
                printRow();
            } else {
                nextRow();
            }
        }
        for (int i = 0; i < LEFT; i++) {
            nextRow();
        }

    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

