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
    int magic[2][4];
    int second[4];

    void read(){
        for (int t = 0; t < 2; t++){
            int line;
            cin >> line;
            for (int i = 1; i <= 4; i++)
            for (int j = 0; j < 4; j++){
                int num;
                cin >> num;
                if (line == i){
                    magic[t][j] = num;
                }
            }
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int rep_num = 0;
        int ans = -1;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if (magic[1][j] == magic[0][i]){
                    rep_num++;
                    ans = magic[1][j];
                }
            }
        }
        if (rep_num == 0){
            printf("Volunteer cheated!\n");
        }else if (rep_num == 1){
            printf("%d\n", ans);
        }else{
            printf("Bad magician!\n");
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

