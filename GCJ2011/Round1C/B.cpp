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

void useFile(const string &fname, const string& suf = "")
{
    if(fname == "" || fname[0] > 'E') return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname + suf +".out").c_str(), "w", stdout);
}

typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 1100;

int dis[MAXN];
long long dsum[MAXN];

struct DIS{
    long long dis;
    int n;
    bool operator<(const DIS& x) const{
        return dis > x.dis;
    }
}acc_dis[MAXN];

int get_start_station(long long t, int N, int C, int &cn, int &dis_to_next)
{
    long long total_dis = t / 2;
    cn = total_dis / dsum[C];
    int left_dis = total_dis % dsum[C];
    int sn = upper_bound(dsum, dsum + C, left_dis) - dsum - 1;
    int start = cn * C + sn;
    dis_to_next = dsum[sn + 1] - left_dis;
    return start;
}

long long calc(long long t, int N, int C, int L)
{
    int dis_to_next, cn;
    int p = get_start_station(t, N, C, cn, dis_to_next);
    if(p >= N){
       return (N/C*dsum[C] + dsum[N%C])*2;
    }else{
        p++;
        int dn = 0;
        acc_dis[dn].dis = dis_to_next;
        acc_dis[dn++].n = 1;
        if(cn == N/C){
            while(p < N){
                acc_dis[dn].dis = dis[p % C];
                acc_dis[dn++].n = 1;
                p++;
            }
        }
        else{
            p = (p-1)%C + 1;
            cn = N/C - cn - 1;
            for(int i=1; i<=C; i++){
                int n = cn;
                if(i > p) n++;
                if(i <= N%C) n++;
                if(n != 0) {
                    acc_dis[dn].dis = dis[i-1];
                    acc_dis[dn++].n = n;
                }
            }
        }
        sort(acc_dis , acc_dis + dn);
        long long ans = t;

        for(int i=0; i<dn; i++){
            if(L>=acc_dis[i].n){
                ans += acc_dis[i].dis * acc_dis[i].n;
                L -= acc_dis[i].n;
            }else{
                ans += acc_dis[i].dis * L;
                ans += acc_dis[i].dis * 2 * (acc_dis[i].n - L);
                L = 0;
            }
        }
        return ans;
    }

}

int main(){
    useFile("B2");
    int T, N, C, L;
    long long t;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> L >> t >> N >> C;
        dsum[0] = 0;
        for(int i=0; i<C; i++){
            cin >> dis[i];
            dsum[i+1] = dsum[i] + dis[i];
        }
        cout << "Case #" << ca << ": " << calc(t, N, C, L) << endl;

    }

}
