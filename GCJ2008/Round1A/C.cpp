#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <string.h>
#include <stdio.h>
using namespace std;

void useFile(const string &fname)
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname+".out").c_str(), "w", stdout);
}

const int N = 2;
const int mod = 1000;

void mat_mul(int c[N][N], int a[N][N], int b[N][N])
{
    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++){
        int x = 0;
        for(int k=0; k<N; k++){
            x += a[i][k]*b[k][j];
        }
        c[i][j] = x % mod;
    }
}

void mat_copy(int dst[N][N], int src[N][N])
{
    for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
        dst[i][j] = src[i][j];
}

void mat_pow(int a[N][N], int p)
{
    int d[N][N];
    int res[N][N] = {1,0,0,1};
    int tmp[N][N];
    mat_copy(d, a);
    while(p){
        if(p&1) {
            mat_copy(a, res);
            mat_mul(res, a, d);
        }
        mat_copy(a, d);
        mat_mul(d, a, a);
        p >>= 1;
    }
    mat_copy(a, res);
}


int main()
{
    useFile("C2");
    int T;

    cin >> T;
    for(int ca=1; ca<=T; ca++){
        int a[N][N] = {3, 5, 1, 3};
        int n;
        cin >> n;
        mat_pow(a, n-1);
        n = a[0][0] * 3 + a[0][1];
        n = (n * 2 + 999) % 1000;
        printf("Case #%d: %03d\n", ca, n);
    }
    return 0;
}
