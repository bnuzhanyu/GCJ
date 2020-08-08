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

    string ans;

    void read() {
        string str;
        cin >> str;
        ans.clear();
        int cur = 0;
        for (char c : str) {
            int x = c - '0';
            while (cur > x) {
                ans.push_back(')');
                cur--;
            }
            while (cur < x) {
                ans.push_back('(');
                cur++;
            }
            ans.push_back(c);
        }
        for (int i = 0; i < cur; i++) {
            ans.push_back(')');
        }

    }

    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": " << ans << "\n";
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

