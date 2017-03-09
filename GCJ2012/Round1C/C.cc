#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Problem{

int N, M;

std::vector<int> toy;
std::vector<long long> tn;
std::vector<int> box;
std::vector<long long> bn;

void read(){
    cin >> N >> M;
    toy.resize(N + 1);
    tn.resize(N + 1);
    box.resize(M + 1);
    bn.resize(M + 1);

    for (int i = 1; i <= N; i++){
        cin >> tn[i] >> toy[i];
    }
    for (int i = 1; i <= M; i++){
        cin >> bn[i] >> box[i];
    }
}

void solve(int ca){
    //printf("Case #%d: ");
    cout << "Case #" << ca << ": ";
    long long dp[101][101] = { 0 };

    for (int i = 1; i <= N; i++){
    for (int j = 1; j <= M; j++){
        long long ans = 0;
        ans = max(dp[i-1][j], dp[i][j-1]);
        if (toy[i] == box[j]){
            int type = toy[i];
            int x = i, y = j;
            long long toy_num = tn[x];
            long long box_num = bn[y];
            do{
                ans = max(ans, dp[x-1][y-1] + min(toy_num, box_num));
                if (toy_num == box_num){
                    break;
                }
                if (toy_num > box_num){
                    do{
                        y--;
                    }while(y > 0 && box[y] != type);
                    box_num += bn[y];
                }else{
                    do{
                        x--;
                    }while(x > 0 && toy[x] != type);
                    toy_num += tn[x];
                }
            }while(x > 0 && y > 0);
        }
        dp[i][j] = ans;
    }
    }
    printf("%lld\n", dp[N][M]);
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
