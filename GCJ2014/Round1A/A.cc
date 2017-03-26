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

    int N, L;
    vector<ll> flow;
    vector<ll> device;
    unordered_set<ll> device_set;

    void read_bin(vector<ll>& x){
        for (int i = 0; i < N; i++){
            string f;
            cin >> f;
            ll s = 0;
            for (int j = 0; j < L; j++){
                s = s * 2 + f[j] - '0';
            }
            x.push_back(s);
        }
    }

    void read(){
        cin >> N >> L;
        read_bin(flow);
        read_bin(device);
        for (auto x : device){
            device_set.insert(x);
        }
    }

    ll reverse_some_bit(ll x, ll pattern){
        return x ^ pattern; 
    }

    int count_1(ll pattern){
        int count = 0;
        for (int i = 0; i < L; i++){
            if ((pattern >> i) & 1) count++;
        }
        return count;
    }

    bool is_valid_pattern(ll pattern){
        for (auto x : flow){
            if (device_set.find(x ^ pattern) == device_set.end()){
                return false;
            }
        }
        return true;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int min_flip = L+1;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                ll pattern = flow[i] ^ device[j];
                if (is_valid_pattern(pattern)){
                    min_flip = min(min_flip, count_1(pattern));
                }
            }
        }

        if (min_flip == L+1){
            printf("NOT POSSIBLE\n");
        }else{
            printf("%d\n", min_flip);
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

