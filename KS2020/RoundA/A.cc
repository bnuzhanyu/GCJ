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

    int N, B;
    vector<int> price;
    void read() {
        cin >> N >> B;
        price.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> price[i];
        }
    }

    void solve(int ca) {
        read();
        sort(price.begin(), price.end());
        int cnt = 0;
        for (int i = 0; i < price.size(); i++) {
            if (B >= price[i]) {
                cnt++;
                B -= price[i];
            } else {
                break;
            }
        }

        cout << "Case #" << ca << ": " << cnt << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

