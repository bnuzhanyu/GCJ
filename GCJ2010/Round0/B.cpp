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

ll num[1005];
ll diff[1005];

int main()
{
    useFile("std");
    int T, N;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N;
        for(int i=0; i<N; i++) cin >> num[i];
        sort(num, num+N);
        ll g = 0;
        for(int i=0; i<N-1; i++){
            diff[i] = num[i+1] - num[i];
            if(diff[i] != 0) g = diff[i];
        }
        for(int i=0; i<N-1; i++){
            g = __gcd(diff[i], g);
        }
        ll ans = 1LL<<60;
        for(int i=0; i<N; i++)
            ans = min( ans, (num[i] + g - 1) / g * g - num[i]);
        cout << "Case #" << ca << ": " << ans << endl;
    }
    return 0;
}
