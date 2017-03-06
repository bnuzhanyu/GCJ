#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

bool dp[2][2010];
int lenA[2010];
int lenB[2010];

struct Problem{
    string s1, s2;
    void read(){
        cin >> s1 >> s2;
        s1 = "#"+s1;
        s2 = "#"+s2;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        memset(dp,0, sizeof(dp));
        memset(lenA, 0, sizeof(lenA));
        memset(lenB, 0, sizeof(lenB));

        dp[0][0] = 1;
        for (int i = 1; i < s2.size(); i++){
            dp[0][i] = (s2[i] == '*') ? dp[0][i-1] : 0;
        }

        int cur = 1;
        for (int i = 1; i < s1.size(); i++){
            memset(dp[cur], 0, sizeof(dp[cur]));
            dp[cur][0] = (s1[i] == '*') ? dp[cur^1][0] : 0;
            for (int j = 1; j < s2.size(); j++){
                if (s1[i] == '*'){
                    if (dp[cur^1][j]){
                        dp[cur][j] = 1;
                        lenA[i] = 0;
                    }else if (dp[cur][j-1]){
                        if (s2[j] != '*' && lenA[i] < 4){
                            dp[cur][j] = 1;
                            lenA[i]++;
                        }else if (s2[j] == '*'){
                            dp[cur][j] = 1;
                        }
                    }
                }

                if (s2[j] == '*'){
                    if (dp[cur][j-1]){
                        dp[cur][j] = 1;
                        lenB[j] = 0;
                    }else if (dp[cur^1][j]){
                        if (s1[i] != '*' && lenB[j] < 4){
                            dp[cur][j] = 1;
                            lenB[j]++;
                        }else if(s1[i] == '*'){
                            dp[cur][j] = 1;
                        }
                    }
                }

                if (s1[i] != '*' && s2[j] != '*'){
                    dp[cur][j] = (dp[cur^1][j-1] && s1[i] == s2[j]);
                }
            }
            cur = cur^1;
        }

        if (dp[cur^1][s2.size() - 1]){
            printf("TRUE\n");
        }else{
            printf("FALSE\n");
        }

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

