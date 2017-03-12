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

    vector<int> pos[2];
    int N;
    vector<int> vec[2];
    vector<int> s;
    void read(){
        cin >> N;
        s.resize(N);
        for (int i = 0; i < N; i++){
            cin >> s[i];
            pos[s[i] & 1].push_back(i);
            vec[s[i] & 1].push_back(s[i]);
        }
    }

    void solve(int ca){
        printf("Case #%d:", ca);
        sort(vec[0].begin(), vec[0].end(), greater<int>());
        sort(vec[1].begin(), vec[1].end());
        for (int i = 0; i < 2; i++){
            int k = 0;
            for (auto p : pos[i]){
                s[p] = vec[i][k++];
            }
        }
        for (auto d : s){
            printf(" %d", d);
        }
        printf("\n");
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

