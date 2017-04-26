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

char str[2010];
struct Problem{

    int N;
    string s;

    void read(){
        cin >> s;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int beg = 1002;
        int end = 1002;
        for (auto c : s){
            if (beg == end || c >= str[beg]){
                str[--beg] = c;
            }else if (c < str[beg]){
                str[end++] = c;
            }
        }
        str[end] = 0;
        printf("%s\n", str + beg);
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

