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

struct SeqGen {
    ll x1, x2, a, b, c, m;
    void input() {
        cin >> x1 >> x2 >> a >> b >> c >> m;
    }
    vector<int> gen(int n) {
        vector<int> ret;
        ret.push_back(x1);
        ret.push_back(x2);
        for (int i = 2; i < n; i++) {
            ll nxt = (a * x2 + b * x1 + c) % m;
            ret.push_back(nxt);
            x1 = x2;
            x2 = nxt;
        }
        return ret;
    }
};

struct Interval {
    Interval(int sc, int m) {
        startScore = sc;
        mul = m;
    }
    int startScore;
    int mul; 
    int calc(ll rank) {
        return sc + (rank - 1) / mul;
    }
};

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int N, Q;
    vector<int> left;
    vector<int> right;
    vector<int> query;
    map<int, int> inc;
    
    ll total = 0;
    void read() {
        cin >> N >> Q;
        SeqGen p1, p2, q;
        p1.input();
        p2.input();
        q.input();
        left = p1.gen(N);
        right = p2.gen(N);
        query = q.gen(Q);
        total = 0;
        inc.clear();
        for (int i = 0; i < N; i++) {
            int l = left[i];
            int r = right[i];
            left[i] = min(l, r) + 1;
            right[i] = max(l, r) + 1;
            total += right[i] - left[i] + 1;
            inc[left[i]]++;
            inc[right[i]+1]--;
        }

        for (int i = 0; i < Q; i++) {
            query[i]++;
        }
    }

    void solve(int ca) {
        read();
        int mul = 0;
        int lastScore = 0;
        ll sum = 0;
        vector<Interval> intervals;
        vector<ll> totals;
        for (auto iter = inc.begin(); iter != inc.end(); iter++) {
            int sc = iter->first;
            int add = iter->second;
            sum += (sc - lastScore) * (ll)mul;
            mul += add;
            lastScore = sc;
            if (mul != 0) {
                intervals.push_back(Interval(sc, mul));
                totals.push_back(sum);
            }
        }

        ll ans = 0;
        for (int i = 0; i < Q; i++) {
            if (query[i] > total) {
                continue;
            }
            ll q = total - query[i] + 1; 
            int idx = lower_bound(totals.begin(), totals.end(), q) - totals.begin();
            int sc = intervals[idx-1].calc(q - totals[idx-1]);
            ans += sc * (ll)(i+1);
        }

        cout << "Case #" << ca << ": "<< ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

