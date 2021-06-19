#include <iostream>
#include <string>
using namespace std;

double dp[2][4000] = { 0 };

struct Problem{

int N, M;

void read(){
    cin >> N >> M;
}

void solve(int ca){
    printf("Case #%d: ", ca);
    memset(dp, 0, sizeof(dp));
    dp[1][1] = (double) N / (N + M);
    int cur = 0;
    for (int i = 2; i <= N + M; i++){
        int left = N + M - i + 1;

        for (int j = 0; j <= N; j++){
            dp[cur][j] = 0;
        }
        //for dp[cur^1][j] , used j A  and i - 1 - j B
        for (int j = i / 2 + 1; j <= N && j <= i; j++){
            
            int Aleft = N - j + 1;
            int Bleft = left - Aleft;
            dp[cur][j] = dp[cur^1][j-1] * (double)(Aleft) / left;

            Aleft--;
            Bleft++;
            dp[cur][j] += dp[cur^1][j] * (double)(Bleft) / left;
        }
        cur^=1;
    }
    printf("%.7f\n", dp[cur^1][N]);
}

};

int main(){
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
    
}
