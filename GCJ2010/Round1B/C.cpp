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

const int MAXN = 501;
const int mod = 100003;
int dp[MAXN][MAXN] = {0};
int ans[MAXN];

int comb[MAXN][MAXN];

void comb_init()
{

    for(int i=0; i<MAXN; i++)
        comb[i][i] = 1, comb[i][0] = 1;
    for(int i=2; i<MAXN; i++){
        for(int j=1; j<i; j++)
            comb[i][j] = (comb[i-1][j-1]+comb[i-1][j]) % mod;
    }
}

void init()
{
    comb_init();

    for(int i=2; i<=MAXN; i++){
        dp[i][1] = 1;
    }
    for(int i=3; i<=MAXN; i++){
        for(int r=2; r<i; r++){
            int m = 0;
            for(int k = 1; k < r; k++){
                if(i-r-1 >= r-k-1)
                    m = (m + dp[r][k] * (ll)comb[i-r-1][r-k-1]) % mod;
            }
            dp[i][r] = m;
        }
    }
    for(int i=2; i<MAXN; i++){
        int cur = 0;
        for(int j=1; j<i; j++)
            cur = cur + dp[i][j];
        ans[i] = cur % mod;
    }
}


int main()
{
    useFile("C2");
    int T;
    init();
    cin >> T;
    int n;
    for(int ca=1; ca<=T; ca++){
        cin >> n;
        cout << "Case #" << ca << ": " << ans[n] << endl;
    }
    return 0;
}
