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
using namespace std;

void useFile(const string &fname)
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname+".out").c_str(), "w", stdout);
}

typedef unsigned long long ll;

const int MAXN = 1005;
ll people[MAXN*2];
ll money[MAXN];
int last_start[MAXN];

//st 是开始， 第一个和大于k的值，当然，也可以用尺取法在O(N)预处理
int find_next_group(int st, int k, int n, ll &cur){
    int ed = st + n;
    ll st_pn = people[st-1];
    while(st < ed){
        int mid = (ed + st) / 2;
        if(people[mid] - st_pn <= k) st = mid + 1;
        else ed = mid;
    }
    cur = people[st-1] - st_pn;
    return (st - 1) % n + 1;
}

int main()
{
    useFile("C2");
    people[0] = 0;

    int T, k, R, N;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        memset(last_start, 0, sizeof(last_start));
        cin >> R >> k >> N;
        for(int i=1; i<=N; i++) {
            cin >> people[i] ;
            people[i+N] = people[i];
        }

        for(int i=1; i<=N*2; i++){
            people[i] += people[i-1];
        }

        ll ans = 0;
        int st = 1;
        int id = 1;
        money[1] = 0;
        while(!last_start[st] && id <= R){
            last_start[st] = id++;
            ll cur;
            st = find_next_group(st, k, N, cur);
            ans += cur;
            money[id] = ans;
        }
        if(id <= R){
            int circle_round = id - last_start[st];
            R -= (last_start[st] - 1);
            ll circle_make = ans - money[last_start[st]];
            ans -= circle_make;
            ans += R/circle_round * circle_make;
            int remain = R % circle_round;
            while(remain--){
                ll cur;
                st = find_next_group(st, k, N, cur);
                ans += cur;
            }
        }
        cout << "Case #" << ca << ": " << ans  << endl;
    }
    return 0;
}
