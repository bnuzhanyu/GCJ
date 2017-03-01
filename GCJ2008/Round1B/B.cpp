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

const int MAXN = 1001000;
int primes[MAXN];
int pn;
int mindiv[MAXN] = {0};
int GetPrime(int N)
{
    pn = 0;
    for(int i=2; i<=N; i++){
        if(mindiv[i] == 0) primes[pn++] = i;
        for(int j=0; (long long)primes[j]*i <=N && j<pn; j++){
            mindiv[primes[j]*i] = primes[j];
            if(mindiv[i] == primes[j]) break;
        }
    }
}
typedef long long ll;
int us_set[MAXN];
int rank[MAXN];
void us_init(int n)
{
    for(int i=0; i<=n; i++)
        us_set[i] = i, rank[i] = 0;
}

int us_find(int u)
{
    int fu = u;
    while(us_set[fu] != fu){
        fu = us_set[fu];
    }
    while(us_set[u] != fu){
        int c = us_set[u];
        us_set[u] = fu;
        u = c;
    }
    return us_set[u];
}

void us_union(int x, int y)
{
    int fx = us_find(x), fy = us_find(y);
    if(fx == fy) return;
    if(rank[fx] < rank[fy]){
        us_set[fx] = fy;
    }else{
        us_set[fy] = fx;
        if(rank[fx] == rank[fy]) rank[fx]++;
    }
}

int count_prime_us(ll l, ll r, ll S)
{
    us_init(r - l + 1);
    int p = lower_bound(primes, primes + pn, S) - primes;
    ll un = 0;
    for(int i=p; i<pn && primes[i] <=(r-l); i++)
    {
        ll st = ((l + primes[i] - 1)/ primes[i])*(long long)primes[i];
        int last = -1;
        while(st <= r)
        {
            if(last != -1) {
                un++;
                us_union(last, st - l);
            }
            last = st - l;
            st += primes[i];
        }
    }
    int ans = 0;
    for(int i=0; i<=(r-l); i++)
        if(us_find(i) == i) ans++;
    return ans;
}

int main(){
    usefile("B2");
    GetPrime(MAXN - 1);
    int T;
    cin >> T;
    ll a, b, S;
    for(int ca=1; ca<=T; ca++)
    {
        cin >> a >> b >> S;
        cout << "Case #" << ca << ": " << count_prime_us(a, b, S) << endl;
    }
}
