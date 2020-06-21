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
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int N, K;
    vector<int> val;
    vector<long long> sum;
    void read() {
        cin >> N >> K;
        val.resize(N);
        sum.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> val[i];
        }
    }

    void solve(int ca) {
        read();
        sort(val.begin(), val.end());
        reverse(val.begin(), val.end());
        long long acc = 0;
        for (int i = 0; i < val.size(); i++) {
            acc += val[i];
            sum[i] = acc;
        }

        double e = acc * 1.0 / N;
        int id = N - 1;
        for (int i = 0; i < K; i++) {
            while (val[id] < e) {
                id--;
            }
            long long s = sum[id];
            e = (e * (N - id - 1) + s) / N;
        }
        printf("Case #%d: %.7f\n", ca, e);
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

