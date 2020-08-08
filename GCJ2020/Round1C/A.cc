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

    int X, Y;
    string path;
    void read() {
        cin >> X >> Y >> path;
    }

    void solve(int ca) {
        read();
        int x = X, y = Y;
        int t = 0;
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == 'E') {
                x++;
            } else if (path[i] == 'S') {
                y--;
            } else if (path[i] == 'N') {
                y++;
            } else {
                x--;
            }
            if (abs(x) + abs(y) <= i + 1) {
                t = i + 1;
                break;
            }
        }
        

        cout << "Case #" << ca << ": ";
        if (t == 0) cout << "IMPOSSIBLE" << endl;
        else cout << t << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

