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

int mapS(char x) {
    switch (x) {
        case 'S':return 0;
        case 'P':return 1;
        case 'R':return 2;
    }
}

int possible(int p, char x) {
    switch (x) {
        case 'S': p = p & 5; break;
        case 'P': p = p & 3; break;
        case 'R': p = p & 6; break;
    }
    return p;
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

    string robots[260];
    void read() {
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> robots[i];
        }
    }

    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": ";
        beat.resize(N);
        for (int i = 0; i < N; i++) beat[i] = false;
        string ans;
        for (int i = 0; i < 500; i++) ans.push_back('0');
        if (solve(0, ans)) {
            cout << ans << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    bool checkBeat() {
        for (int i = 0; i < N; i++) if(!beat[i]) return false;
        return true;
    }
    vector<bool> beat;
    bool solve(int id, string& ans) {
        if (checkBeat()) {
            ans.resize(id);
            return true;
        }
        if (id == 500) {
            return false;
        }

        vector<int> x[3];
        int p = 7;
        for (int i = 0; i < N; i++) {
            if (!beat[i]) {
                int j = id % robots[i].size();
                p = possible(p, robots[i][j]);
                int m = mapS(robots[i][j]);
                x[m].push_back(i);
            }
        }
        if (p == 0) {
            return false;
        }
        static char* op = "SPR";
        for (int k = 0; k < 3; k++) {
            if (p & (1<<k)) {
                int d = (k+1) % 3;
                for (int j = 0; j < x[d].size(); j++) {
                    beat[x[d][j]] = true;
                }
                ans[id] = op[k]; 
                if (solve(id+1, ans)) {
                    return true;
                }
                for (int j = 0; j < x[d].size(); j++) {
                    beat[x[d][j]] = false;
                }
            }
        }
        return false;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

