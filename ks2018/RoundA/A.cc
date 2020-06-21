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
    string digits;

    string doupper(string ori, int pos, int digit) {
        string ret = ori;
        ret[pos] = digit + 1 + '0';
        for (int j = pos + 1; j < ori.size(); j++) {
            ret[j] = '0';
        }
        return ret; 
    }

    string dolower(string ori, int pos, int digit) {
        string ret = ori;
        ret[pos] = digit - 1 + '0';
        for (int j = pos + 1; j < ori.size(); j++) {
            ret[j] = '8';
        }
        return ret; 
    }

    void read() {
        cin >> digits;
    }
    
    void solve(int ca) {
        read();
        string upper = digits;
        string lower = digits;
        for (int i = 0; i < digits.size(); i++) {
            int d = digits[i] - '0';
            if (d & 1) {
                lower = dolower(digits, i, d);
                if (d == 9) {
                    upper = lower;
                } else {
                    upper = doupper(digits, i, d);
                }
                break;
            }
        }
        long long cur = stoll(digits);
        long long upperN = stoll(upper);
        long long lowerN = stoll(lower);
        long long diff = min(abs(upperN - cur), abs(cur - lowerN));
        cout << "Case #" << ca << ": " << diff << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

