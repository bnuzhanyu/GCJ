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

    int N, B;
    vector<int> cost;
    void read(){
        cin >> B >> N;
        for (int i = 0; i < B; i++){
            int x;
            cin >> x;
            cost.push_back(x);
        }
    }

    ll served(ll t){
        if (t < 0){
            return 0;
        }

        ll n = 0;
        for (int i = 0; i < B; i++){
            n += t / cost[i] + 1;
        }
        return n;
    }

    bool is_cover_n(ll t){
        return served(t) >= N;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        
        int tmax = *max_element(cost.begin(), cost.end());
        ll st = 0, ed = (ll)tmax * N;
        while (st < ed){
            ll mid = (st + ed) / 2;
            if (is_cover_n(mid)){
                ed = mid;
            }else{
                st = mid + 1;
            }
        }

        ll last_serve = served(st - 1);
        for (int i = 0; i < B; i++){
            if (st % cost[i] == 0){
                last_serve++;
            }
            if (last_serve == N){
                printf("%d\n", i + 1);
                break;
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

