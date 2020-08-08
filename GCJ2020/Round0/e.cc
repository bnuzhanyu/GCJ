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

int mat[52][52];

void print(int n, int seq[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", seq[mat[i][j]]);
            printf((j==n-1)?"\n":" ");
        }
    }
}

void produceDiag(int n) {
    for (int i = 0; i < n; i++) {
        int st = i;
        for (int j = 0; j<n;j++ ) {
            mat[i][st % n] = j + 1;
            st++;
        }
    }
}

void firstN_3Lines(int n) {
    for (int i = 0; i < n - 3; i++) {
        int st = i;
        for (int j = 0; j<n; j++) {
            mat[i][st % n] = j + 1;
            st++;
        }
    }
}

void set(int i, int j, int v) {
    mat[i][j] = v;
}

void snakeAB(int n) {
    int dir = 1;//down
    int r = n - 3;
    int st = 2;
    for (int j = 0; j < n - 4; j++) {
        int cur = st + j;
        for (int i = 0; i < 3; i++) {
            mat[r][j] = cur++;
            r += dir;
        }
        dir = -dir;
        r += dir;
    }
    if (n % 2 == 0) {
        mat[n-3][n-4] = n - 2;
        mat[n-2][n-4] = mat[n-1][n-3] = n;
        mat[n-2][n-3] = mat[n-1][n-4] = n-1;
    } else {
        mat[n-3][n-4] = mat[n-2][n-3] = n - 1;
        mat[n-2][n-4] = mat[n-1][n-3] = n;
        mat[n-1][n-4] = n - 2;
    }
}

void snakeABC(int n) {
    int dir = -1;//up
    int r = n - 1;
    int st = 2;
    for (int j = 0; j < n - 4; j++) {
        int cur = st + j;
        for (int i = 0; i < 3; i++) {
            mat[r][j] = cur++;
            r += dir;
        }
        dir = -dir;
        r += dir;
    }
    if (n % 2 == 1) {
        mat[n-3][n-4] = n - 2;
        mat[n-2][n-4] = mat[n-1][n-3] = n;
        mat[n-2][n-3] = mat[n-1][n-4] = n-1;
    } else {
        mat[n-3][n-4] = mat[n-2][n-3] = n - 1;
        mat[n-2][n-4] = mat[n-1][n-3] = n;
        mat[n-1][n-4] = n - 2;
    }
}
//with n >= 4
void produceABC(int n) {
    firstN_3Lines(n);
    int r = n - 3;
    set(r, r, 1);
    set(r, r + 1, n);
    set(r, r + 2, 2);
    set(r+1, r+1, 2);
    set(n-1, 0, 2);
    set(n-1, n-1, 3);
    set(n-1, n-2, 1);
    set(n-2, n-1, 1);
    snakeABC(n);
}
void produceAB(int n) {
    firstN_3Lines(n);
    int r = n - 3;
    set(n-3, n-3, 1);
    set(n-3, n-2, n);
    set(n-3, n-1, 3);
    mat[n-2][n-2] = mat[n-1][n-1] = 2;
    mat[n-1][n-2] = mat[n-2][n-1] = 1;
    snakeAB(n);
}


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

    int A, B, C;
    void eq(int n, int k) {
        A = -1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                int x = k - (n-2)*i - j;
                if (x != i && x > 0 && x <= n) {
                    A = i;
                    B = j;
                    C = x;
                    break;
                }
            }
        }
    }

    void make(int n, int k) {
        int seq[52];
        for (int i = 1; i <=n; i++) {
            seq[i] = i;
        }

        if (k % n == 0) {
            produceDiag(n);
            int b = k / n;
            swap(seq[b], seq[1]);
            print(n, seq);
            return;
        }

        eq(n, k);
        int s = 1;
        seq[s++] = A;
        seq[s++] = B;
        if (B == C) {
            produceAB(n);
        } else {
            produceABC(n);
            seq[s++] = C;
        }
        for (int i = 1; i <= n; i++) {
            if (i == A || i == B || i == C) continue;
            seq[s++] = i;
        }
        print(n, seq);
    }

    bool judge(int n, int k) {
        if (n == 2 || n == 3) {
            return k % n == 0;
        }
        if (k == n*n - 1 || k == n + 1) {
            return false;
        }
        return true;
    }

    void read() {
        cin >> N >> K;
    }


    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": ";
        if (judge(N, K)) {
            cout << "POSSIBLE" << endl;
            make(N, K);
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

