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
    int N, K;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    vector<int> minutes;
    void read() {
        cin >> N >> K;
        minutes.resize(N);
        for (int i = 0; i < N; i++) {
            cin >> minutes[i];
        }
    }

    
    int needAdd(int gap, int v) {
        return (gap + v - 1) / v - 1;
    }

    bool isOk(int v) {
        int count = 0;
        for (int i = 1; i < minutes.size(); i++) {
            int diff = minutes[i] - minutes[i-1];
            count += needAdd(diff, v);
        }
        return count <= K;
    }

    void solve(int ca) {
        read();
        int left = 1, right = minutes.back();
        while (left < right) {
            int mid = (left + right) >> 1;
            if (isOk(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        cout << "Case #" << ca << ": " << left << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

