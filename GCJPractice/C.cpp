#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstdio>
using namespace std;

/*
对于D,B，第一个蛋在哪儿扔呢？
如果蛋破了，那就是看D-1, B-1能扔多少楼了。
如果蛋没破，那么还有D-1,B，这是D-1,B能测出的楼高。
所以dp[D][B] = dp[D-1][B-1] + 1 + dp[D-1][B];
小数据直接打表可过，对于大数据，只要打2^17 * 33的表就行了。其他情况特殊考虑。
*/
const int MAXN = (1<<17);
long long dp[MAXN][34];
void init(){
    bool flag = false;
    for(int i=1;i<MAXN; i++)
        dp[i][1] = i;
    for(int j=1; j<34; j++)
        dp[1][j] = 1;
    for(int i=2; i<MAXN; i++)
    for(int j=2; j<34; j++){
        dp[i][j] = dp[i-1][j-1] + dp[i-1][j] + 1;
        if(dp[i][j] >= (1LL<<32)) {
            dp[i][j] = (1LL<<32);
            //if(!flag) {printf("first at %d\n", i); flag = true;}
        }
    }
}

long long calcMaxF(int F, int D, int B)
{
    long long ans;
    if(D<=B) B = D;
    if(B == 1) ans = D;
    else if(B >= 34 || D >= MAXN) ans = -1;
    else ans = dp[D][B];
    return (ans >= (1LL<<32)) ? -1 : ans;
}


int calcMinD(int F, int D, int B){
    if(D<=B) B = D;
    if(B == 1) D = F;
    else {
        if(B > 33) B = 33;
        D = 1;
        while(dp[D][B] < F) D++; //如果case多，可以用二分
    }
    return D;
}

int calcMinB(int F, int D, int B){
    if(D<=B) B = D;
    if(D>=F) B = 1;
    else if(D>=MAXN) B = 2;
    else {
        B = 1;
        while(dp[D][B] < F) B++;
    }
    return B;
}

void ReadAndSolve(){
    int T, F, D, B;
    scanf("%d", &T);
    for(int ca=1; ca<=T; ca++){
        scanf("%d%d%d", &F, &D, &B);
        long long f = calcMaxF(F, D, B);
        int d = calcMinD(F, D, B);
        int b = calcMinB(F, D, B);
        printf("Case #%d: %lld %d %d\n", ca, f, d, b);
    }
}

void UseStdIO()
{
    ReadAndSolve();
}
void UseFileIO(){
    freopen("GCJPP-C-large.in", "r", stdin);
    freopen("GCJPP-C-large.out", "w", stdout);
    ReadAndSolve();
}

int main()
{
    init();
    //UseStdIO();
    UseFileIO();
    return 0;
}
