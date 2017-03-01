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


typedef unsigned long long ull;
const int MAXL = 45;
const int PN = 4;

vector<int> factors;
vector<int> signs;

int primes[] = {2, 3, 5, 7};

void init(){
    int n = sizeof(primes)/sizeof(int);
    for(int i=1; i<(1<<n); i++){
        int f = 1, s = -1;
        for(int j=0; j<n; j++){
            if((i>>j) & 1) { f *= primes[j];  s *= -1; }
        }
        if(f!=1) cout << " " << s << " " << f << endl;
        signs.push_back(s);
        factors.push_back(f);
    }
}

vector<int> dp[MAXL][MAXL][1<<PN];
void dp_init(int sz)
{
    for(int i=0; i<sz; i++)
    for(int j=0; j<sz; j++)
    for(int k=0; k<factors.size(); k++){
        dp[i][j][k] = vector<int>(factors[k], -1);
    }
}


//Ô¤´¦Àínum_mod[i][j][k] Îª str[i..j] % factors[k]
int num_mod[MAXL][MAXL][1<<PN];
int str_mod(const string& str)
{
    int len = str.size();
    for(int i=0; i<len; i++){
        for(int k=0; k<factors.size(); k++){
            int st = 0;
            for(int j=i; j<len; j++){
                num_mod[i][j][k] = (st*10 + str[j]-'0') % factors[k];
                st = num_mod[i][j][k];
            }
        }
    }
}


ull calc(int i, int j, int f, int mod){
    if(dp[i][j][f][mod] != -1) return dp[i][j][f][mod];
    else {
        dp[i][j][f][mod] = 0;
        ull ans = int(num_mod[i][j][f] == mod);
        if(i == j) return ans;

        int mid = (i+j)/2;
        for(int m = 0; m < factors[f]; m++){
            ans += calc(i, mid, f, m) * calc(mid+1, j, f, (m - mod + factors[f]) % factors[f]);
            ans += calc(i, mid, f, m) * calc(mid+1, j, f, (mod - m + factors[f]) % factors[f]);
        }


        if(ans) cout << "dp[" << i << "," << j <<"] % " << factors[f] << "=" << mod << "  count:" << ans << endl;
        return dp[i][j][f][mod] = ans;
    }
}


int main(){
    usefile("std");
    init();
    int T;
    cin >> T;
    string num;
    for(int ca=1; ca<=T; ca++)
    {
        cin >> num;
        dp_init(num.size());
        str_mod(num);
        for(int i=0; i<factors.size(); i++)
            calc(0, num.size()-1, i, 0);

        ull ans = 0;
        for(int i=0; i<factors.size(); i++){
            if(signs[i] == 1) ans += dp[0][num.size()-1][i][0];
            else ans -= dp[0][num.size()-1][i][0];
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
}







