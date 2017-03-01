#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <limits>
using namespace std;

void useFile(const string &fname , const string& suf = "")
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname + suf +".out").c_str(), "w", stdout);
}

typedef long long ll;
const int MAXN = 210;

struct VENDOR{
    int p, v;
    void input(){ cin >> p >> v; p*=2;}
    bool operator < (const VENDOR& x) const{
        return p < x.p;
    }
}vendor[MAXN];

bool judge(long long t, int n, int d)
{
    long long st = -(1LL<<62);

    for(int i=0; i<n; i++){
        st = max(st,  vendor[i].p - t);
        long long rt = st + (long long)d*(vendor[i].v - 1);
        if( (rt - vendor[i].p) > t ) return false;
        st = rt + d;
    }
    return true;
}

long long solve(int n, int d)
{
    d *= 2;
    sort(vendor, vendor + n);
    int vn = 0;
    for(int i=0; i<n; i++)
        vn += vendor[i].v;
    long long l = 0, r = (long long)vn * d;

    while(l < r){
        long long mid = (l+r)/2;
        if(!judge(mid, n, d)) {
            l = mid + 1;
        }else{
            r = mid;
        }
    }
    return l;
}

int main(){
    useFile("B2");

    int T, N, M, D;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N >> D;
        for(int i=0; i<N; i++)
            vendor[i].input();

        long long ans = solve(N, D);

        cout << "Case #" << ca << ": " << ans / 2 << ((ans & 1)?".5":"") << endl;
    }

}
