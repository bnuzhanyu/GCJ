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

    ll N;
    ll K;

    priority_queue<ll> queue;
    map<ll, ll> mp;
    void read(){
        cin >> N >> K;
        mp[N] = 1;
        queue.push(N);
    }

    pair<ll,ll> calc_size(ll x){
        return make_pair((x)/2, (x-1)/2);
    }

    void insert(ll x, ll cnt){
        if (x == 0) return;
        if (mp.find(x) == mp.end()) queue.push(x);
        mp[x] += cnt; 
    }
    void solve(int ca){
        printf("Case #%d: ", ca);
        
        while (true){
            ll cur = queue.top(); 
            //printf("%lld\n", cur);
            if (mp[cur] >= K){
                break;
            }else{
                ll cnt = mp[cur];
                K -= cnt;
                queue.pop();
                mp.erase(cur);
                auto p = calc_size(cur);
                insert(p.first, cnt);
                insert(p.second, cnt);
            }
        }
        ll cur = queue.top();
        auto ans = calc_size(cur);
        printf("%lld %lld\n", ans.first, ans.second);
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

