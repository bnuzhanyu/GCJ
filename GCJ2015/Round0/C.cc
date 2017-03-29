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


const int I = 2, J = 3, K = 4;
int table[5][5] = {
{0, 0, 0, 0, 0},
{0, 1, I, J, K},
{0, I, -1, K, -J},
{0, J, -K, -1, I},
{0, K, J, -I, -1},
};

int mul(int x, int y){
    int sgx = (x > 0) ? 1 : -1;
    int sgy = (y > 0) ? 1 : -1;
    return (sgx * sgy) * table[sgx * x][sgy * y];
}

struct Problem{

    int N, L;
    ll X;
    string str;
    void read(){
        cin >> L >> X;
        cin >> str;
    }

    int get_all_mul(){
        int cur = 1;
        for (auto c : str){
            int x = c - 'i' + 2;
            cur = mul(cur, x);
        }
        int f = X % 4;
        int res = 1;
        while(f--){
            res = mul(res, cur); 
        }
        return res;
    }

    int find_first_i(){
        int cur = 1;
        int cnt = 0;
        for (int i = 0; i < 4 && i < X; i++){
            for (auto c : str){
                int x = c - 'i' + 2;
                cnt++;
                cur = mul(cur, x);
                if (cur == I){
                    return cnt;
                }
            }
        }
        return -1;
    }

    int find_last_k(){
        int cur = 1;
        int cnt = 0;
        for (int i = 0; i < 4 && i < X; i++){
            for (auto iter = str.rbegin(); iter != str.rend(); iter++){
                int x = *iter - 'i' + 2;
                cnt++;
                cur = mul(x, cur);
                if (cur == K){
                    return cnt;
                }
            }
        }
        return -1;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int res = get_all_mul();
        bool flag = false;
        if (res == -1){
            int i = find_first_i();
            int k = find_last_k();
            if (i == -1 || k == -1 || (i + k) >= (L * X)){
                flag = false; 
            }else{
                flag = true;
            }
        }
        printf("%s\n", flag ? "YES":"NO");
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

