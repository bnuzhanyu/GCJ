#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

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
    using ull = unsigned long long;
    ull prob, n, p, q;

    void read(){
        cin >> prob;
        if (prob == 1){
            cin >> n;
        }else{
            cin >> p >> q;
        }
    }

    ull get_n(ull p, ull q){
        vector<int> vec;
        while (p!=1 || q!=1){
            if (p > q){
                vec.push_back('1');
                p = p-q;
            }else{
                vec.push_back('0');
                q = q-p;
            }
        }
        ull n = 1;
        reverse(vec.begin(), vec.end());
        for (auto d : vec){
            if (d == '0'){
                n = n*2;
            }else{
                n = n*2 + 1;
            }
        }
        return n;
    }

    pair<ull, ull>get_pq(ull n){
        int bit = 1; 
        ull x = n;
        ull p = 1, q = 1;
        vector<int> vec;
        while (n != 1){
            vec.push_back(n&1);
            n >>= 1;
        }
        reverse(vec.begin(), vec.end());
        for (auto d : vec){
            if (d == 1){
                p = p + q;
            }else{
                q = p + q;
            }
        }
        return make_pair(p, q);
    }

    void solve(int ca){
        cout << "Case #" << ca << ": ";
        if (prob == 1){
            auto pq = get_pq(n);
            cout << pq.first << " " << pq.second;
        }else{
            cout << get_n(p, q);
        }
        cout << endl;
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

