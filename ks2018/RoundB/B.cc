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

struct Interval {
    int a, b, c;
    void input() {
        cin >> a >> b >> c;
    }
};

long long cnt[1<<15][100];

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int N, K;
    long long P;

    vector<Interval> intervals;
    vector<vector<Interval>> sameEndInterval;
    void read() {
        cin >> N >> K >> P;
        intervals.resize(K);
        sameEndInterval.clear();
        sameEndInterval.resize(N);
        memset(cnt, -1, sizeof(cnt));
        for (int i = 0; i < K; i++) {
            intervals[i].input();
            sameEndInterval[intervals[i].b - 1].push_back(intervals[i]);
        }
    }

    int ans[200];

    int shift(int bit15, int nxt) {
        return ((bit15 << 1) & 0x7fff) | nxt;
    }

    int countBit(int x, int len) {
        int c = 0;
        for (int i = 0; i < len; i++) {
            c += (x & 1);
            x >>= 1;
        }
        return c;
    }

    bool valid(int cur_bit16, int idx) {
        vector<Interval>& vs = sameEndInterval[idx];
        for (Interval& v : vs) {
            int len = v.b - v.a + 1;
            int expected = v.c;
            if (countBit(cur_bit16, len) != expected) {
                return false;
            }
        }
        return true;
    }

    long long getCount(int bit15, int idx) {
        if (idx == N) {
            return 1;
        }

        if (cnt[bit15][idx] != -1) {
            return cnt[bit15][idx];
        }

        long long c = 0;
        for (int v = 0; v <= 1; v++) {
            int cur_bit16 = (bit15 << 1) | v;
            int nxt_bit15 = shift(bit15, v);
            if (valid(cur_bit16, idx)) {
                long long cc = getCount(nxt_bit15, idx+1);
                //cout << "valid:" << bin(cur_bit16) << " " << idx << ":" << cc << endl;
                c += cc;
            } 
            if (c > P) {
                c = P + 1;
                break;
            }
        }
        //cout << "cnt:" << bin(bit15) << " " << idx << ":" << c << endl;
        return cnt[bit15][idx] = c;
    }

    string bin(int p) {
        string x;
        if (p == 0) {
            x = "0";
        }
        while(p) {
            x.push_back((p&1) + '0');
            p >>= 1;
        }
        reverse(x.begin(), x.end());
        return x;
    }

    void calc(int idx, int prefix, long long left) {
        if (idx == N) {
            return;
        }
        int nxt_bit15 = shift(prefix, 0);
        long long b0 = valid(prefix << 1, idx) ? getCount(nxt_bit15, idx + 1) : 0;
        if (b0 >= left) {
            ans[idx] = 0;
            calc(idx+1, nxt_bit15, left);
        } else {
            ans[idx] = 1;
            calc(idx+1, nxt_bit15 | 1, left - b0);
        }
    }

    void solve(int ca) {
        read();
        getCount(0, 0);
        calc(0, 0, P);
        cout << "Case #" << ca << ": ";
        for (int i = 0; i < N; i++) {
            cout << ans[i];
        }
        cout << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

