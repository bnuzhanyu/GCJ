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
    int pn[30];
    priority_queue<pair<int, char> > pq;
    void read(){
        cin >> N;
        for (int i = 0; i < N; i++) {
            cin >> pn[i];
            if (pn[i] != 0)
                pq.push(make_pair(pn[i], i + 'A'));
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        
        while (!pq.empty()){
            if (pq.size() == 2){
                auto a = pq.top(); pq.pop();
                auto b = pq.top(); pq.pop();

                for (int m = a.first; m > b.first; m--){
                    printf(" %c", a.second);
                }
                for (int m = b.first; m > 0; m--){
                    printf(" %c%c", a.second, b.second);
                }
                break;
            }
            auto x = pq.top(); pq.pop();
            printf(" %c", x.second);
            x.first--;
            if (x.first > 0) pq.push(x);
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

