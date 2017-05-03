#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <functional>
#include <cmath>
#include <string.h>

using namespace std;
using ull = unsigned long long;
using ll = long long;
using db = double;
using PII = pair<int, int>;

template<typename T>
void print_vec(T& container, const std::string& sep = " "){
    for (auto& x: container){
        std::cout << x << sep;
    }
    std::cout << std::endl;
}

template<typename T>
void print_map(T& mp){
    for(auto& x: mp){
        std::cout << x.first << " " << x.second << std::endl;
    }
}

struct Problem{

    int N;
    int R, C;
    char mp[30][30];
    void read(){
        cin >> R >> C;
        for (int i = 0; i < R; i++)
            cin >> mp[i];
    }

    void fillrow(int i, int j, char c){
        int pre = j - 1;
        while (pre >= 0 && mp[i][pre] == '?') mp[i][pre--] = c;
        int cur = j + 1;
        while (cur < C && mp[i][cur] == '?') mp[i][cur++] = c;
    }

    void fillcol(int i, int j, char c){
        int pre = i - 1;
        while (pre >= 0 && mp[pre][j] == '?') mp[pre--][j] = c;
        int cur = i + 1;
        while (cur < R && mp[cur][j] == '?') mp[cur++][j] = c;
    }

    void solve(int ca){
        printf("Case #%d:\n", ca);
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++){
                if (mp[i][j] != '?'){
                    fillrow(i, j, mp[i][j]);
                }
            }
        }

        for (int j = 0; j < C; j++){
            for (int i = 0; i < R; i++){
                if (mp[i][j] != '?'){
                    fillcol(i, j, mp[i][j]);
                }
            }
        }

        for (int i = 0; i < R; i++)
            printf("%s\n", mp[i]);

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

