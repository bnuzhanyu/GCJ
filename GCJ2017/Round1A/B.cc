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

    int N, P;
    vector<int> style;
    vector<int> gr[60];
    void read(){
        cin >> N >> P;
        style.resize(N);
        for (int i = 0; i < N; i++)
            cin >> style[i];
        for (int i = 0; i < N; i++){
            gr[i].resize(P);
            for (int j = 0; j < P; j++)
                cin >> gr[i][j];
            sort(gr[i].begin(), gr[i].end());
        }
    }

    using PII = pair<int, int>; 
    PII get_serving(int has, int need){
        int b = has * 100 / (need * 90);  //max servings
        int a = (has * 100 + need * 110 - 1) / (need * 110);
        return make_pair(a, b);
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int idx[60] = { 0 };
        bool flag = true;
        int ans = 0;
        while (flag){
            int max_min = 0;
            for (int i = 0; i < N; i++){
                auto p = get_serving(gr[i][idx[i]], style[i]);
                max_min = max(p.first, max_min);
            }
            bool suc = true;
            for (int i = 0; i < N; i++){
                auto p = get_serving(gr[i][idx[i]], style[i]);
                if (p.second < max_min){
                    idx[i]++;
                    suc = false;
                }
            }

            if (suc){
                ans++;
                for (int i = 0; i < N; i++) idx[i]++;
            }
            for (int i = 0; i < N; i++) if (idx[i] == P) flag = false;
        }
        printf("%d\n", ans);

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

