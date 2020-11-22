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

using ll = long long;

//等差数列求和公式
ll seq_sum(ll st, int d, ll n) {
    return (st + st + (n-1) * d) * n / 2;
}

//求从st开始的公差为d的数列前n项和<= value的最大n
ll solve_seq(ll st, int d, ll value) {
    if (value == 0) return 0;
    ll left = 0, right = 2*sqrt(value + 1) + 1;
    while (left < right) {
        ll mid = left + (right - left) / 2;
        if (seq_sum(st, d, mid) > value) right = mid;
        else left = mid + 1;
    }
    return left - 1;
}

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    long long L, R;

    void read() {
        cin >> L >> R;
    }

    void solve(int ca) {
        int f = solve_seq(1, 1, abs(L-R));
        ll fsum = seq_sum(1, 1, f);
        if (L < R) R -= fsum; 
        else L -= fsum;

        bool swp = L < R;
        if (swp) swap(L, R);

        int n = solve_seq(f+1, 2, L);
        L -= seq_sum(f+1, 2, n);
        int m = solve_seq(f+2, 2, R);
        R -= seq_sum(f+2, 2, m);

        if (swp) swap(L, R);

        cout << "Case #" << ca << ": " << (f + n + m) << " " << L << " " << R << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

