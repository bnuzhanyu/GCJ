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

typedef long long ll;

struct CMP {
    bool operator<(const int x, const int y) {
        if ()
    }
};

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    
    vector<ll> slice;
    int N, D;
    void read() {
        slice.resize(N + 1);
        cin >> N >> D;
        ll sum = 0;
        for (int i = 0; i < N; i++) {
            cin >> slice[i]
            sum += slice[i];
        }
        slice[N] = 360LL * 1000000000 - sum; 
    }

    bool test(ll cut, int d) {
        int need = 0;
        vector<ll> v;
        sort(slice.begin(), slice.end(), )
        for (int i = 0; i < slice.size(); i++) {
            
        }
    }

    int isOK() {
        for (int j = 0; j < D - 1; j++) {
            vector<ll> v;
            for (int i = 0; i < N+1; i++) {
                for (int k = 1; k <= j; k++) {
                    if (v[i] % k == 0) {
                        if (test(v[i] / k, j) ) {
                            return j;
                        }
                    }
                }

            }
        }
        return D - 1;
    }

    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": " << isOK() << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

