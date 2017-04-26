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

    int B;
    long long M;
    int mat[51][51];
    void read(){
        cin >> B >> M;
    }

    void solve(int ca){
        memset(mat, 0, sizeof(mat));
        printf("Case #%d: ", ca);
        if (1LL<<(B-2) < M) printf("IMPOSSIBLE\n");
        else{
            printf("POSSIBLE\n");
            M--;
            mat[0][B-1] = 1;
            for (int i = B-2; i > 0 ; i--){
                mat[i][B-1] = 1;
                for (int j = 1; j < i; j++)
                    mat[i][j] = 1;
            }
            int cur = 1;
            while (M){
                if (M & 1) mat[0][cur] = 1;
                M >>= 1;
                cur++;
            }
            for(int i = 0; i < B; i++)
            {
                for (int j = 0; j < B; j++){
                    printf("%d", mat[i][j]);
                }
                printf("\n");
            }
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

