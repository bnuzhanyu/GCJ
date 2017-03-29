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
    string s;
    void read(){
        cin >> N >> s;

    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int ans = 0;
        int pn = s[0] - '0';
        for (int i = 1; i < s.size(); i++){
            int cur = s[i] - '0';
            if (cur > 0 && pn < i){
                ans += (i - pn);
                pn = i;
            }
            pn += cur;
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

