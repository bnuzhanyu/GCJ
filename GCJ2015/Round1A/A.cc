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
    vector<int> mush;
    void read(){
        cin >> N;
        for (int i = 0; i < N; i++){
            int a;
            cin >> a;
            mush.push_back(a);
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int x1 = 0, x2 = 0;
        int min_rate = 0;
        for (int i = 1; i < N; i++){
            if (mush[i] < mush[i-1]){
                x1 += mush[i-1] - mush[i];
            }
            min_rate = max(min_rate, mush[i-1] - mush[i]);
        }
        for (int i = 0; i < N - 1; i++){
            x2 += min(mush[i], min_rate);
        }
        printf("%d %d\n", x1, x2);
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

