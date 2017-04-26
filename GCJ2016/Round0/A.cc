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
    int mask;
    void read(){
        cin >> N;
        mask = 0;
    }

    void update_mask(){
        int x = N;
        while (x){
            int s = x % 10;
            mask |= (1<<s);
            x /= 10;
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        if (N == 0){
            printf("INSOMNIA\n");
            return;
        }
        int ori = N;
        update_mask();
        while (mask != (0x3ff)){
            N += ori;
            update_mask();
        }
        printf("%d\n", N);
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

