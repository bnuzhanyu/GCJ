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

    long long N;
    long long L, F;

    long long count(long long n) {
        string s = to_string(n);
        long long x = 0;
        for (char c : s) {
            x = x * 9 + c - '0';
        }
        x++;
        long long mul = x / 9;
        if (x % 9 == 0) {
            return x - mul;
        }
        for (int i = 0; i <= n % 10; i++) {
             if ((n - i) % 9 == 0) {
                mul++;
             }
        }
        return x - mul;
    }

    void read() {
        cin >> F >> L;
    }

    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": " << count(L) - count(F) + 1 << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

