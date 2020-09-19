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

string rep(int& z) {
    string line = "I/O/I/O/I/O/I/O";
    for (int i = 1; i < line.size(); i+=2) {
        if (z > 0) {
            z--;
            line[i] = 'I';
        }
    }
    return line;
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

    int D,N;
    void read() {
        cin >> D >> N;
    }

    void solve(int ca) {
        N = 287 - N;
        int x = N / 3;
        if (x > 91) x = 91;
        int y = N - x * 3;
        cout << "Case #" << ca << ": " << endl;
        cout << rep(y) << endl;
        for (int i = 0; i < 13; i++) {
            cout << rep(x) << endl;
        }
        cout << rep(y) << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

