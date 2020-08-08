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

class Problem {
public:
    int T;
    int N;
    void go() {
        cin >> T >> N;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    void read() {
    }

    string ans;
    //int okcount[3] = {6, 2, 1};
    int okcount[5] = {120, 24, 6, 2, 1};
    set<int> contains;
    int qcount = 0;
    int FACT_N = 5;
    void dfs(int dep, vector<int>& fig) {
        if (fig.size() != okcount[dep] - 1) {
            cout << "err " << endl;
            exit(1);
        }
        if (dep == FACT_N - 1) {
            for (int i = 0; i < FACT_N; i++) {
                if (contains.find(i) == contains.end()) {
                    ans.push_back(i+'A');
                }
            }
            return;
        }
        string x;
        vector<int> query[FACT_N];
        for (int i = 0; i < fig.size(); i++) {
            int q = fig[i] * FACT_N + dep + 1;
            cout << q << endl;
            cin >> x;
            if (x[0] == 'N') exit(1);
            int id = x[0] - 'A';
            query[id].push_back(fig[i]);
        }
        for (int i = 0; i < FACT_N; i++) {
            if (contains.find(i) == contains.end() && query[i].size() < okcount[dep + 1]) {
                if (query[i].size() != okcount[dep + 1] - 1) {
                    cout << i << " query[i].size = " << query[i].size() << endl;
                    //return;
                    exit(1);
                }
                ans.push_back(i + 'A');
                contains.insert(i);
                dfs(dep+1, query[i]);
                return;
            }
        }
    }
    void solve(int ca) {
        read();
        ans.clear();
        contains.clear();
        vector<int> fig;
        int n = okcount[0];
        for (int i = 0; i < n - 1; i++) {
            fig.push_back(i);
        }
        dfs(0, fig);
        cout << ans << endl;
        string x;
        cin >> x;
        if (x[0] == 'N') exit(1);
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

