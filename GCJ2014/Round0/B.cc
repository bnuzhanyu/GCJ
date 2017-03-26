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
    double F, C, X;
    double rate;
    void read(){
        cin >> C >> F >> X;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        double cur = 0;
        double t = 0;
        rate = 2;
        while (1){
            double t1 = X / rate;
            double t2 = C / rate + X / (rate + F);
            //printf("%.8f  %.8f\n", t1, t2);
            if (t1 < t2){
                t += t1;
                break;
            }else{
                t += C / rate;
                rate += F;
            }
        }
        printf("%.8f\n", t);
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

