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
    string a, b;
    int size;
    ll mdiff;
    ll mx, my;
    void update_mindiff(ll x, ll y){
        ll diff = abs(x - y);
        if (diff > mdiff){
            return;
        }
        if (diff < mdiff){
            mdiff = diff;
            mx = x;
            my = y;
        }
        if (diff == mdiff){
            if (x == mx) {
                my = min(my, y);
            }else if (x < mx){
                mx = x;
                my = y;
            }
        }
    }

    void dfs(ll x, ll y, int depth){
        if (depth == size){
            update_mindiff(x, y);
            return;
        }
        int cur_a = (a[depth] == '?') ? -1 : a[depth] - '0';
        int cur_b = (b[depth] == '?') ? -1 : b[depth] - '0';
        vector<pair<int, int> > v;
        if (x == y){
            if (cur_a == -1 && cur_b == -1){
                v.push_back(make_pair(0, 0));
                v.push_back(make_pair(0, 1));
                v.push_back(make_pair(1, 0));
            }else if (cur_a != -1 && cur_b == -1){
                v.push_back(make_pair(cur_a, (cur_a + 1) % 10));
                v.push_back(make_pair(cur_a, (cur_a + 9) % 10));
                v.push_back(make_pair(cur_a, cur_a));
            }else if (cur_a == -1 && cur_b != -1){
                v.push_back(make_pair(cur_b, cur_b));
                v.push_back(make_pair((cur_b + 1) % 10, cur_b));
                v.push_back(make_pair((cur_b + 9) % 10, cur_b));
            }else{
                v.push_back(make_pair(cur_a, cur_b));
            }
        }else{ 
            if (cur_a == -1) cur_a = (x > y)?0:9;
            if (cur_b == -1) cur_b = (x > y)?9:0;
            v.push_back(make_pair(cur_a, cur_b));
        }
        for (auto p : v){
            dfs(x * 10 + p.first, y * 10 + p.second, depth + 1);
        }
    }

    void read(){
        cin >> a >> b;
        size = a.size();
    }

    
    string to_str(ll n){
        auto str_a = to_string(n);
        int sz_0 = size - str_a.size();
        return string(sz_0, '0') + str_a;
    }
    void solve(int ca){
        printf("Case #%d: ", ca);
        mdiff = 0x7fffffffffffffff;
        dfs(0, 0, 0);
        auto x = to_str(mx);
        auto y = to_str(my);
        printf("%s %s\n", x.c_str(), y.c_str());
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

