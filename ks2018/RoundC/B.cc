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
    int R[20][20];
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int N;
    void read() {
        cin >> N;
        for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> R[i][j];
        }
        }
    }

    bool isOk(vector<int>& edge) {
        if (edge.size() <= 2) {
            return false;
        }
        int maxLen = 0;
        int s = 0;
        for (int e : edge) {
            maxLen = max(e, maxLen);
            s += e;
        }
        return maxLen < s - maxLen;
    }

    int bit(int mask, int i) {
        return (mask >> i) & 1;
    }

    int dfs(int mask, vector<int>& edge) {
        if (mask + 1 == (1<<N)) {
            if (isOk(edge)) {
                return 1;
            }
            return 0;
        }
        int ans = 0;
        for (int i = 0; i < N; i++) {
            if (bit(mask, i)) {
                continue;
            }
            ans += dfs(mask | (1<<i), edge);
            for (int j = i + 1; j < N; j++) {
                if (!bit(mask, j) && R[i][j] > 0) {
                    edge.push_back(R[i][j]);
                    ans += dfs(mask | (1<<j) | (1<<i), edge);
                    edge.pop_back();
                }
            }
            break;
        }
        return ans;
    }

    void solve(int ca) {
        read();
        vector<int> edge;
        int ans = dfs(0, edge);
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

