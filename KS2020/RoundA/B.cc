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

    int K, P;

    void read() {
        cin >> N >> K >> P;
    }

    void solve(int ca) {
        read();
        vector<int> values;
        values.resize(P + 1);
        for (int i = 0; i <= P; i++) {
            values[i] = 0;
        }
        for (int i = 0; i < N; i++) {
            int x, sum = 0;
            vector<int> s;
            s.resize(K);
            for (int k = 0; k < K; k++) {
                cin >> x;
                sum += x;
                s[k] = sum;
            }
            for (int j = P; j >= 1; j--) {
                for (int k = 0; k < K; k++) {
                    if (j - k - 1 >= 0) {
                        values[j] = max(values[j], values[j - k - 1] + s[k]);
                    }
                }
            }
        }
        cout << "Case #" << ca << ": " << values[P] << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

