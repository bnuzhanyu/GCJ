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
    vector<int> judges;
    int sum_judge;
    void read(){
        sum_judge = 0;
        cin >> N;
        judges.resize(N);
        for (int i = 0; i < N; i++){
            cin >> judges[i];
            sum_judge += judges[i];
        }
    }

    bool satisfy(int c, double s){
        double other_sum = 0;
        double cur_score = judges[c] + s*sum_judge;
        for (int i = 0; i < N; i++){
            if (i != c && cur_score > judges[i]){
                double least = (cur_score - judges[i]) / sum_judge;
                other_sum += least;
            }
        }
        return other_sum + s > 1 - 1e-12;
    }

    void solve(int ca){
        printf("Case #%d:", ca);
        for (int i = 0; i < N; i++){
            double lt = 0, rt = 1;
            while (lt < rt - 1e-9){
                double mid = (lt + rt) / 2;
                if (satisfy(i, mid)){
                    rt = mid;
                }else{
                    lt = mid;
                }
            }
            printf(" %.6f", lt * 100);
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

