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

typedef unsigned long long ull;
typedef unsigned long long ll;

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}

const int MAXN = 510;

int dp[MAXN][20];

const string welcome = "welcome to code jam";
int calc(const string& str)
{
    for(int i=0; i<str.size(); i++)
        dp[i][0] = (str[i] == welcome[0]);
    for(int j=1; j<welcome.size(); j++)
    {
        for(int i=0; i<str.size(); i++){
            dp[i][j] = 0;
            if(str[i] == welcome[j]){
                for(int k=0; k<i; k++){
                    dp[i][j] = dp[i][j] + dp[k][j-1];
                    dp[i][j] %= 10000;
                }
            }
        }
    }
    int ans = 0;
    for(int i=0; i<str.size(); i++){
        ans += dp[i][welcome.size() - 1];
        ans %= 10000;
    }
    return ans;
}

int main(){
    usefile("C2");
    int T;
    cin >> T;
    string str;
    getline(cin, str);

    for(int ca=1; ca<=T; ca++)
    {
        getline(cin, str);
        printf("Case #%d: %04d\n", ca, calc(str));
    }
}


