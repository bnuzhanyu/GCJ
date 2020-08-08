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

class Problem {
public:
    int T;
    int W;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    vector<long> count ;
    void read() {
        cin >> W;
        count.clear();
        count.resize(W);
        for (int i = 0; i < W; i++) {
            cout << i << endl;
            cin >> count[i]; 
        }
    }

    void solve(int ca) {
        read();
        int r1 = count[1] - count[0];
        int r2 = count[2] - count[1] - 2 * r1;
        int r3 = count[3] - count[2] - 4 * r1;
        int r4 = count[4] - count[3] - 2 * r2 - 8 * r1;
        int r5 = count[5] - count[4] - 16 * r1;
        int r6 = count[0] - (r1+r2+r3+r4+r5);
        cout << r1 << " " << r2 << " " << r3 << " " << r4 << " " << r5 << " " << r6 << endl;
        int res;
        cin >> res;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

