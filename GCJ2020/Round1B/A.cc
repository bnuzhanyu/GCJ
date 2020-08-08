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
    int N;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int X, Y;
    void read() {
        cin >> X >> Y;
    }

    bool isOk(int x, int y) {
        return (x==0 && y==0) || ((x + y) & 1);
    }

    //next step from 0, 0 to dx, dy
    void solve(int dx, int dy, string& ans) {
        
        if (dx == 0 && dy == 0) {
            return;
        }

        int nx, ny;
        char step;
        if ((dx & 1)) {
            //east
            int x1 = (dx - 1) / 2;
            int x2 = (dx + 1) / 2;
            ny = dy / 2;
            if((x2 != 0 || ny != 0) && isOk(x1, ny)) {
                step = 'E';
                nx = x1;
            } else {
                step = 'W';
                nx = x2;
            }
        } else {
            nx = dx / 2;
            int y1 = (dy - 1) / 2;
            int y2 = (dy + 1) / 2;
            if ((nx != 0 || y2 != 0) && isOk(nx, y1)) {
                step = 'N';
                ny = y1;
            } else {
                step = 'S';
                ny = y2;
            }
        }
        //cout << "--" << dx << " " << dy << " " << nx << " " << ny << " " << step << endl;
        ans.push_back(step);
        solve(nx, ny, ans);
    }

    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": ";
        string ans;
        if (!isOk(X, Y)) {
            ans = "IMPOSSIBLE";
        } else {
            solve(X, Y, ans);
        }
        cout << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

