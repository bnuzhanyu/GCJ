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

int dp[150][300];
int num[150];

int solve(int a[], int n, int D, int I, int M)
{
    for(int i=0; i<=255; i++)
        dp[0][i] = abs(a[0] - i);
    for(int i=1; i<n; i++){
        for(int j=0; j<=255; j++){
            dp[i][j] = D*i + abs(a[i]-j);
            dp[i][j] = min(dp[i][j], D + dp[i-1][j]);
            int x = abs(a[i]-j);
            if(M==0) dp[i][j] = min(dp[i][j] , x + dp[i-1][j]);
            else{
                for(int f=0; f<=255; f++){
                    dp[i][j] = min(dp[i][j], x + dp[i-1][f] + max(0,(abs(f-j) - 1)) / M * I );
                }
            }
        }
    }
    int ans = dp[n-1][0];
    for(int i=1; i<=255; i++){
        ans = min(ans, dp[n-1][i]);
    }
    return ans;
}

int main()
{
    useFile("B2");
    int T;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        int D , I, M, N;
        cin >> D >> I >> M >> N;
        for(int i=0; i<N; i++) cin >> num[i];

        cout << "Case #" << ca << ": " << solve(num, N, D, I, M) << endl;
    }
    return 0;
}
