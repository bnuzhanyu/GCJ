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

const int MAX = 1000000000;
class Problem {
public:
    int T;
    int N;
    int A, B;
    int Rd;
    void go() {
        cin >> T >> A >> B;
        Rd = MAX - A;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }


    string send(int x, int y) {
        string s;
        cout << x << " " << y << endl;
        cin >> s; 
        return s;
    }

    bool isCenter(string& s) {
        return s == "CENTER";
    }
    bool isHit(string& s) {
        return s == "HIT";
    }
    bool isMiss(string &s) {
        return s == "MISS";
    }

    bool test(int x1, int x2, int y1, int y2, int r) {
        if (x1 == x2 && y1 == y2) {
            string ans = send(x1, y1);
            if (!isCenter(ans)) {
                exit(1);
            }
            return true;
        }
        int midx = (x1 + x2) / 2;
        int midy = (y1 + y2) / 2; 

        string n,w,e,s;

        if (y1 == y2) {
            string n = "HIT";
        } else {
            n = send(midx, midy + r);
        }

        if (x1 == x2) {
            w = e = "HIT";
        } else {
            string w = send(midx - r, midy);
            string e = send(midx + r, midy);
        }

        if (y1 == y2) {
            s = "HIT";
        } else if (isHit(n) && isHit(e) && isHit(w)) {
            s = "HIT";
        } else if (isHit(n) && (isHit(w) == !isHit(e))) {
            s = "MISS";
        } else if (!isHit(n) && !isHit(e) && !isHit(w)) {
            s = "HIT";
        } else {
            s = send(midx, midy - r);
        }

        int hitCount = 0;
        hitCount += isHit(n);
        hitCount += isHit(w);
        hitCount += isHit(e);
        hitCount += isHit(s);

        if (hitCount == 4) {
            string ans = send(midx, midy);
            if (!isCenter(ans)) {
                exit(1);
            }
            return true;
        }

        if (hitCount == 3) {
            if(!isHit(n)) {
                return test(x1, x2, y1, midy, r);
            }
            if (!isHit(w)) {
                return test(midx + 1, x2, y1, y2, r);
            }
            if (!isHit(s)) {
                return test(x1, x2, midy + 1, y2, r);
            }
            if (!isHit(e)) {
                return test(x1, midx, y1, y2, r);
            }
        }

        if (hitCount == 1) {
            if(isHit(n)) {
                return test(x1, x2, midy + 1, y2, r);
            }
            if (isHit(w)) {
                return test(x1, midx, y1, y2, r);
            }
            if (isHit(s)) {
                return test(x1, x2, y1, midy, r);
            }
            if (isHit(e)) {
                return test(midx + 1, x2, y1, y2, r);
            }
        }

        if (hitCount == 2) {
            if (isHit(n) && isHit(w)) {
                return test(x1, midx, midy + 1, y2, r);
            }
            if (isHit(s) && isHit(w)) {
                return test(x1, midx, y1, midy, r);
            }
            if (isHit(n) && isHit(e)) {
                return test(midx + 1, x2, midy + 1, y2, r);
            }
            if (isHit(s) && isHit(e)) {
                return test(midx + 1, x2, y1, midy, r);
            }
        } 
        exit(1);
    }

    void solve(int ca) {
        if (Rd == 5) {
            test(-5, 5, -5, 5, A);
            return;
            for (int i = -5; i <= 5; i++) {
                for (int j = -5; j <= 5; j++) {
                    string res = send(i, j);
                    if (res == "CENTER") {
                        return;
                    }
                }
            }
        }

        if (Rd == 50) {
            test(-50, 50, -50, 50, A);
        }
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

