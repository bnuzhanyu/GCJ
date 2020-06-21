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
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int N;
    void read() {
        cin >> N >> O >> D;
    }

    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": ";
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

