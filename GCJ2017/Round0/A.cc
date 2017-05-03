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

    string S;
    void change(int i){
        S[i] = (S[i] == '-' ? '+':'-');
    }

    void change_interval(int i){
        for (int j = i; j < i + K; j++){
            change(j);
        }
    }

    int K;
    void read(){
        cin >> S >> K;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int c = 0;
        for (int i = 0; i < S.size() - K + 1; i++){
            if (S[i] == '-'){
                change_interval(i);
                c++;
            }
        }

        bool is_ok = true;
        for (int i = S.size() - K + 1; i < S.size(); i++)
            if (S[i] == '-')  {
                is_ok = false;
                break;
            }

        if (is_ok) printf("%d\n" , c);
        else printf("IMPOSSIBLE\n");
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

