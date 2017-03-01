#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <cmath>
using namespace std;
/*
状态压缩dp，dp[pa][i][j]表示最后留在i商场购买完pa的二进制中1所表示的商品，j表示在i商场是否购买了perish产品。
*/

const int MAXN = 60;
const int MAXI = 16;
double sq(double x) {return x*x;}

double dist[MAXN][MAXN];
double price[MAXN][MAXI];
bool exist[MAXN][MAXI];
double dp[1<<MAXI][MAXN][2];
int perish[MAXI];
char name[100];
char store[1000];


void ReadAndSolve(){
    int N, S, T;
    double gas;
    scanf("%d", &T);
    double x[MAXN], y[MAXN];
    for(int ca=1; ca<=T; ca++){
        map<string, int> mp;
        memset(perish, 0, sizeof(perish));
        memset(exist, 0, sizeof(exist));
        scanf("%d%d%lf", &N, &S, &gas);

        for(int i=0; i<N; i++){
            scanf("%s", name);
            int l = strlen(name);
            if(name[l-1] == '!') { perish[i] = 1; name[l-1] = 0;}
            else perish[i] = 0;
            mp[string(name)] = i;
        }

        x[0] = 0, y[0] = 0;
        for(int i=1; i<=S; i++){
            scanf("%lf%lf", &x[i], &y[i]);
            gets(store);
            int j=0;
            while(store[j]){
                while(store[j]==' ')j++;
                int k = 0;
                while(store[j]!=':') name[k++] = store[j++];
                name[k] = 0; j++;
                int id = mp[string(name)];
                exist[i][id] = true;
                sscanf(&store[j], "%lf", &price[i][id]);
                while(store[j] && store[j]!=' ') j++;
            }
        }

        //calc dist
        S++;
        for(int i=0; i<S; i++){
            for(int j=0; j<S; j++)
                dist[i][j] = sqrt(sq(x[i]-x[j]) + sq(y[i]-y[j])) * gas;
        }

        //dp
        const double INF = 1e50;
        for(int i=0; i<(1<<N); i++)
        for(int k=0; k<S; k++)
        dp[i][k][0] = dp[i][k][1] = INF;

        for(int i=1; i<S; i++)
        for(int j=0; j<N; j++){
            if(exist[i][j]) dp[1<<j][i][perish[j]] = dist[0][i] + price[i][j];
        }

        for(int pa=1; pa<(1<<N); pa++){
            for(int j=0; j<N; j++){
                if((pa>>j) & 1) continue;
                int y = j;
                for(int s=1; s<S; s++){
                    double cur0 = dp[pa][s][0];
                    double cur1 = dp[pa][s][1];
                    if(cur0 == INF && cur1 == INF) continue;
                    for(int d=1; d<S; d++){
                        int pay = pa|(1<<y);
                        double z0 = dp[pay][d][0];
                        double z1 = dp[pay][d][1];
                        if(exist[d][y]){
                            double pdy = price[d][y];
                            if(s == d){
                                if(perish[y]) dp[pay][d][1] = min(z1, min(cur0, cur1) + pdy);
                                else dp[pay][d][0] = min(z0, cur0 + pdy);
                            }
                            else{
                                    dp[pay][d][perish[y]] = min(dp[pay][d][perish[y]],
                                            min(cur0 + dist[s][d] + pdy, cur1 + dist[0][s] + dist[0][d] + pdy));
                            }
                        }
                    }
                }
            }
        }

        double ans = INF;
        for(int i=1; i<S; i++){
            for(int k=0; k<2; k++)
                ans = min(ans, dp[(1<<N) - 1][i][k]  + dist[0][i]);
        }
        printf("Case #%d: %.7f\n", ca, ans);
    }
}

void UseStdIO()
{
    ReadAndSolve();
}
void UseFileIO(){
    freopen("GCJPP-D-large.in", "r", stdin);
    freopen("GCJPP-D-large.out", "w", stdout);
    ReadAndSolve();
}

int main()
{
    UseStdIO();
    //UseFileIO();
    return 0;
}
