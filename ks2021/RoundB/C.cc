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

template<typename T>
using VEC = vector<T>;

template<typename T>
using MAT = vector<vector<T> >;

template<typename T>
void print(const VEC<T>& vec) {
    for (const auto& e : vec) cout << e << " ";
    cout << endl;
}

template<typename T>
void print_with_idx(const VEC<T>& vec) {
    FOR(i,0,vec.size()) {
        cout << i << ":" << vec[i] << endl;
    }
}

template<typename T>
void read_vec(VEC<T>& vec, int n, bool need_clear = true) {
    if (need_clear) vec.clear();
    FOR(i,0,n){
        T x; cin >> x;
        vec.push_back(x);
    }
}

template<typename T>
void read_mat(MAT<T>& mat, int r, int c) {
    mat.resize(r);
    FOR(i,0,r) {
        mat[i].resize(c);
        FOR(j,0,c) {
            cin >> mat[i][j];
        }
    }
}

const int MAXN = 100000;
int primes[MAXN] = {2};
int pn = 1;
int check[MAXN];

void initPrime() {
    memset(check, 0, sizeof(check));
    for (int i = 2; i < MAXN; ++i)
    {
        if (!check[i]) primes[pn++] = i;
        for (int j = 0; j < pn; ++j)
        {
            if (i * primes[j] > MAXN) break;
            check[i*primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
}

bool is_prime(ll x) {
    for (int i = 0; (ll)primes[i] * primes[i] <= x; i++) {
        if (x % primes[i] == 0) return false;
    }
    return true;
}

int get_sq(ll x) {
    int l = 1, r = min(1000000000LL, x);
    while (l < r) {
        int mid = l + (r - l + 1) / 2;
        if (mid * (ll)mid >= x) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    return l;
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

    ll N;
    void read() {
        cin >> N;
    }

    ll get_ans(ll N) {
        int sq = get_sq(N);
        ll c = sq + 1;
        while(!is_prime(c)) {
            c++;
        }
        ll b = sq;
        while(!is_prime(b)) {
            b--;
        }
        ll ans = 0;
        ll a = 1;
        if (b * c <= N) {
            ans = b * c;
        } else {
            a = b - 1;
            while(!is_prime(a)) {
                a--;
            }
            ans = a * b;
        }
        //cout << sq << " " << a << " " << b << " " << c << endl;
        return ans;
    }

    void solve(int ca) {
        ll ans = get_ans(N);
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    initPrime();
    Problem p;
    p.go();
    return 0;
}

