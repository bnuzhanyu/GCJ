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

int times[1010];
int main(){
    usefile("A2");
    int T, P, K, L;
    cin >> T;

    for(int ca=1; ca<=T; ca++)
    {
        cin >> P >> K >> L;
        for(int i=0; i<L; i++)
            cin >> times[i];
        sort(times, times+L, greater<int>());
        long long ans = 0;
        long long mul = 0;
        for(int i=0; i<L; i++){
            if(i%K == 0) mul++;
            ans += mul*times[i];
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
}







