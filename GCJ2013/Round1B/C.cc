#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <fstream>
using namespace std;

int dp[4010][5];
class Problem {

public:
    std::string str;
    void read(){
        cin >> str;
    }

    void update(const std::string& str, int i, int x, int y, int add){

        if (dict.find(str) != dict.end()){
            int u = i + str.size();
            for (int j = 0; j < 5; j++){
                if (x + j + 1>= 5){
                    int ed = y;
                    if (y == str.size()){
                        ed = j + y;
                    }
                    ed = min(4, ed);
                    dp[u][ed] = min(dp[u][ed], dp[i][j] + add);
                }
            }
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int len = str.size();

        for (int i = 0; i < len + 1; i++){
            for (int j = 0; j < 5; j++){
                dp[i][j] = len;
            }
        }

        for (int j = 0; j < 5; j++){
            dp[0][j] = 0;
        }

        for (int i = 0; i < len; i++){
            for (int l = 1; l <= 10 && i + l <= len; l++){
                auto s = str.substr(i, l);
                update(s, i, 5, l, 0);
                for (int x = 0; x < l; x++){
                    auto ss = s;
                    ss[x] = '*';
                    update(ss, i, x, l - 1 - x, 1);
                }

                for (int x = 0; x < l; x++){
                    for (int y = x + 5; y < l; y++){
                        auto ss = s;
                        ss[x] = ss[y] = '*';
                        update(ss, i, x, l - 1 - y, 2);
                    }
                }

            }
        }

        int ans = len;
        for (int j = 0; j < 5; j++){
            ans = min(ans, dp[len][j]);
        }
        printf("%d\n", ans);
    }

    static void init(){
        ifstream fin("Cdict"); 
        std::string s;
        int sz_max;
        while (fin >> s){
            dict.insert(s);
            
            for (int i = 0; i < s.size(); i++){
                auto x = s;
                x[i] = '*';
                dict.insert(x);
            }

            for (int i = 0; i < s.size(); i++){
                for (int j = i + 5; j < s.size(); j++){
                    auto x = s;
                    x[i] = '*';
                    x[j] = '*';
                    dict.insert(x);
                }
            }
        }
        fin.close();
    }
    static unordered_set<std::string> dict; 
};

unordered_set<std::string> Problem::dict;

int main(){
    Problem::init();
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }

}
