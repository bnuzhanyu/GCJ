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

typedef long long ll;

const int MAXQ = 110;
int release[MAXQ];
int dp[MAXQ][MAXQ];
int solve(int p, int q)
{
    //[0] ... [q]
    for(int i=0; i<q; i++)
        dp[i][i+1] = 0;

    for(int k=2; k<=q; k++){
        for(int i=0; i+k<=q; i++){
            int t = 1<<30;
            for(int j=i+1; j<i+k; j++){
                t = min(t, dp[i][j] + dp[j][i+k]);
            }
            dp[i][i+k] = t + release[i+k] - release[i] - 2;
        }
    }
    return dp[0][q];
}

int main(){
    useFile("C2");
    int T, P, Q;
    cin >> T;

    for(int ca=1; ca<=T; ca++){
        cin >> P >> Q;
        release[0] = 0;
        release[Q+1] = P+1;
        for(int i=1; i<=Q; i++)
            cin >> release[i];
        sort(release, release + Q + 1);
        cout << "Case #" << ca << ": " << solve(P, Q+1) << endl;
    }

}
