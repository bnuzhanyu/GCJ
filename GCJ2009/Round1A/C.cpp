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
typedef long long ll;

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}


long long comb[50][50];

void getComb(int n){
    for(int i=0; i<=n; i++)
        comb[i][i] = 1, comb[i][0] = 1;
    for(int i=2; i<=n; i++){
        for(int j=1; j<i; j++){
            comb[i][j] = comb[i-1][j] + comb[i-1][j-1];
        }
    }

}

double getProb(int c, int n, int x, int y)
{ // x->y
    double p = 1;
    int k = y - x;
    p = comb[c-x][k] *1.0 / comb[c][n] * comb[x][n-k];
    return p;
}

double res[50];
double prob[50];
double solve(int c, int n)
{
    res[c] = 0;
    for(int i=c-1; i>=0; i--){
        double pii = getProb(c, n, i, i);
        double tmp = 0;
        double pij;
        for(int j=i+1; j<=min(c, i+n); j++){
            pij = getProb(c, n, i, j);
            tmp += pij * res[j];
        }
        res[i] = (1+tmp) / (1-pii);
    }
    return res[0];
}

int main(){
    getComb(40);

    usefile("C2");
    int T;
    cin >> T;
    for(int ca=1; ca<=T; ca++)
    {
        int N, C;
        cin >> C >> N;
        cout << "Case #" << ca << ": " << fixed << solve(C, N) << endl;
    }
}







