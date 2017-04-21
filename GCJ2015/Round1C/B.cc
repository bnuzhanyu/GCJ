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

double prob[101][101];

struct Problem{
    int N;
    int L, K, S;
    int max_overlap;
    
    string input;
    string obj; 
    double p[26];
    double suffix_prob[101];
    void read(){
        cin >> K >> L >> S;
        cin >> input;
        cin >> obj;
    }

    void init(){
        memset(p, 0, sizeof(p));
        for (auto c : input){
            p[c-'A'] += 1.0 / input.size();
        }

        int len = obj.size();
        max_overlap = 0;
        for (int i = 1; i < obj.size(); i++){
            if (obj.substr(i) == obj.substr(0, len - i)){
                max_overlap = len - i;
                break;
            }
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        init();
        double prob = 1;
        for (int i = 0; i < obj.size(); i++){
            prob = prob * p[obj[i] - 'A'];
        }
        double upper = prob == 0  ? 0 : (S-L)/(L-max_overlap) + 1;
        double lower = prob * (S-L+1); 
        printf("%.7f\n", upper - lower);
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

