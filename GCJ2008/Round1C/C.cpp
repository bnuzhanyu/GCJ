#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,n) for(int i=0; i<n; i++)

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}

const int MAXN = 500020;

const int mod = 1000000007;

int lowbit(int i){ return i&(-i);}

struct BITTREE{
    int n;
    int *a;
    void init(int _n, int *_a){
        n = _n;
        a = _a;
        memset(a ,0, sizeof(int)*(n+1));
    }

    void add(int i, int v){
        while(i<=n){
            a[i] += v;
            a[i] %= mod;
            i += lowbit(i);
        }
    }

    int sum(int i){
        long long s = 0;
        while(i>0){
            s += a[i];
            i -= lowbit(i);
        }
        return s % mod;
    }

};

int bit[MAXN];
int A[MAXN];

struct NUM{
    int v, id;
    bool operator<(const NUM& x) const{
        if(v == x.v) return id > x.id;
        return v < x.v;
    }
}num[MAXN];

int main(){
    usefile("C2");
    int T;
    cin >> T;
    int n, m, X, Y, Z;
    for(int ca=1; ca<=T; ca++)
    {
        cin >> n >> m >> X >> Y >> Z;
        for(int i=0; i<m; i++) cin >> A[i];

        for(int i=0; i<n; i++){
            int id = i % m;
            num[i].v = A[id];
            num[i].id = i;

            A[id] = (X*(long long)A[id] + Y*(long long)(i+1)) % Z;
        }

        sort(num, num + n);

        BITTREE bt;
        bt.init(n, bit);
        int ans = 0;
        int dpi = 0;
        for(int i=0; i<n; i++){
            dpi = bt.sum(num[i].id + 1) + 1;
            ans += dpi;
            ans %= mod;
            bt.add(num[i].id + 1, dpi);
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
}







