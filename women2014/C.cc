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
using VI = vector<int>;
using VLL = vector<ll>;
using VVI = vector<VI>;
#define FOR(i,a,b) for( int i=(a); i<(b); ++i)
#define RANGE(i,n) for( int i=0; i<(n); ++i)

ll fact[21];
void init() {
    fact[0] = fact[1] = 1;
    for(int i = 2; i < 21; i++) {
        fact[i] = i * fact[i-1];
    }
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

    int N, K;
    void read() {
        cin >> N >> K;
    }

    void solve(int ca) {
        int small = N / K;
        int large = small + 1;
        int largeN = N % K;  
        int smallN = K - largeN; 
        ll ans = fact[N];
        for (int i = 0; i < largeN; i++) {
            ans = ans / large;
            if (large >= 3) ans /= 2;
        }
        for (int i = 0; i < smallN; i++) {
            ans = ans / small;
            if (small >= 3) ans /= 2;
        }
        ans /= fact[largeN];
        ans /= fact[smallN];

        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    init();
    Problem p;
    p.go();
    return 0;
}


