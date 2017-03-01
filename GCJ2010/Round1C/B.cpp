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

int main()
{
    useFile("B");
    ll T,L,P,C;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> L >> P >> C;
        int ans = 0;
        while ((P + L - 1) / L > C){
            C*=C;
            ans++;
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
    return 0;
}
