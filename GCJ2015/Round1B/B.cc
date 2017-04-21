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

    int N, R, C;
    void read(){
        cin >> R >> C >> N;
    }

    int remove_k(int k, int four, int three, int two){
        int total = (R - 1) * C + (C - 1) * R;
        int x;
        x = min(k, four); k -= x; total -= 4*x;
        x = min(k, three); k -= x; total -= 3*x;
        x = min(k, two); k -= x; total -= 2*x;
        if (k != 0) printf("error\n");
        return total;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int half = (R*C + 1) / 2;
        int ans;
        if (R > C) swap(R, C);
        if (N <= half){
            ans = 0;
        }else{
            int need_remove = R*C - N;
            if (R == 1){
                ans = (C - 1) - 2*need_remove;
            }else{
                if (R*C % 2 == 0){
                    int four = (R-2)*(C-2) / 2;
                    int two = 2; 
                    int three = half - four - two;
                    ans = remove_k(need_remove, four, three, two);
                }else{
                    //method1:
                    int four = ((R-2)*(C-2) / 2 + 1);
                    int two = 4;
                    int three = half - four - two;
                    ans = remove_k(need_remove, four, three, two);
                    four = (R-2)*(C-2) / 2;
                    two = 0;
                    three = half - 1 - four;
                    ans = min(ans, remove_k(need_remove, four, three, two));
                }
            }
        }
        printf("%d\n", ans);
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

