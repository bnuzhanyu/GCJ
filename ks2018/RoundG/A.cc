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

typedef long long ll;

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
    ll zeroN;
    vector<int> num;
    unordered_map<ll, int> count;
    void read() {
        num.clear();
        count.clear();
        zeroN = 0;
        cin >> N;
        for (int i = 0; i < N; i++) {
            int a;
            cin >> a;
            if (a == 0) zeroN++;
            else {
                num.push_back(a);
                count[a]++;
            }
        }
    }

    ll countZero() {
        return zeroN * (zeroN - 1) * (zeroN - 2) / 6 + zeroN * (zeroN - 1) / 2 * num.size();
    }

    ll countNonZero() {
        ll ret = 0;
        count[num[0]]--;
        for (int k = 1; k + 1 < num.size(); k++) {
            long long v = num[k];
            count[v]--;
            for (int j = 0; j < k; j++) {
                int v2 = num[j];
                ll v3 = v2 * v;
                auto iter = count.find(v3);
                if (iter != count.end()) {
                    ret += iter->second;
                }
            }
        }
        return ret;
    }

    void solve(int ca) {
        read();
        sort(num.begin(), num.end());
        ll ans = countZero();
        if (num.size() >= 3) {
            ans += countNonZero();
        } 
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

