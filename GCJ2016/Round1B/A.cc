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

string num_str[10] = {
"ZERO", //z
"ONE",
"TWO", //w
"THREE", //
"FOUR",
"FIVE", //
"SIX", //x
"SEVEN", //s
"EIGHT",
"NINE"
};

char num_seq[] = {0, 2, 4, 6, 8, 1, 7, 3, 5, 9};
char alp[] = "ZOWHUVXSGE";

struct Problem{

    int N;
    string str;
    int count[10];
    int al_count[26];
    void read(){
        cin >> str;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        memset(count, 0, sizeof(count));
        memset(al_count, 0, sizeof(al_count));
        for(auto c : str){
            al_count[c-'A']++;
        }
        for (int i = 0; i < 10; i++){
            int cur = num_seq[i];
            char c = alp[cur];
            count[cur] = al_count[c-'A'];
            for (auto x : num_str[cur]){
                al_count[x - 'A'] -= count[cur];
            }
        }
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < count[i]; j++){
                printf("%d", i);
            }
        }
        printf("\n");

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

