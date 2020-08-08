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

const int SZ = 16;
int cache[SZ][SZ][SZ][SZ];
int sg[SZ][SZ][SZ][SZ];

class Problem {
public:
    int T;
    int R, C;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    string map[SZ];

    void read() {
        cin >> R >> C;
        for (int i = 0; i < R; i++) {
            cin >> map[i];
        }
    }

    void solve(int ca) {
        read();
        memset(cache, -1, sizeof(cache));
        memset(sg, -1, sizeof(sg));
        int ans = get_sg(0, R, 0, C);
        cout << "Case #" << ca << ": " << cache[0][R][0][C] << endl;
    }

    bool checkValidRow(int i, int y1, int y2) {
        for (int j = y1; j < y2; j++) {
            if (map[i][j] == '#') return false;
        }
        return true;
    }

    bool checkValidCol(int j, int x1, int x2) {
        for (int i = x1; i < x2; i++) {
            if (map[i][j] == '#') return false;
        }
        return true;
    }

    int get_sg(int x1, int x2, int y1, int y2) {
        //cout << "dfs " << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
        if (x1 >= x2 || y1 >= y2) {
            return 0;
        }

        if (sg[x1][x2][y1][y2] != -1) {
            return sg[x1][x2][y1][y2];
        }

        int n = 0;

        set<int> mex;
        for (int i = x1; i < x2; i++) {
            //cout << "row:" << map[i] << endl;
            if(checkValidRow(i, y1, y2)) {
                //cout << "valid row: " << i << endl;
                //put H in row[i];
                int v1 = get_sg(x1, i, y1, y2);
                int v2 = get_sg(i + 1, x2, y1, y2);
                int sub_sg = (v1 ^ v2);
                mex.insert(sub_sg);
                if (sub_sg == 0) {
                    n += (y2 - y1);
                }
            }
        }

        for (int j = y1; j < y2; j++) {
            //put V in col[j];
            //cout << "valid col: " << j << endl;
            if (checkValidCol(j, x1, x2)) {
                int v1 = get_sg(x1, x2, y1, j);
                int v2 = get_sg(x1, x2, j+1, y2);
                int sub_sg = (v1 ^ v2);
                mex.insert(sub_sg);
                if (sub_sg == 0) {
                    n += (x2 - x1);
                }
            }
        }

        cache[x1][x2][y1][y2] = n;
        int c = 0;
        while (mex.count(c) != 0) {
            c++;
        }
        return sg[x1][x2][y1][y2] = c;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

