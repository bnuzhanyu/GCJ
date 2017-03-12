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
    int sudoku[36][36];
    void read(){
        cin >> N;
        for (int i = 0; i < N*N; i++){
        for (int j = 0; j < N*N; j++){
            cin >> sudoku[i][j];
            sudoku[i][j]--;
        }
        }
    }

    bool is_ok(int x){
        return x >= 0 && x < N*N;
    }

    bool judge(const vector<int>& vec){
        vector<bool> exist(N*N, false);
        for (auto v : vec){
            if (!is_ok(v) || exist[v]){
                return false;
            }
            exist[v] = true;
        }
        return true;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        bool is_ok = true;
        for (int i = 0; i < N*N && is_ok; i++){
            vector<int> vec;
            vector<int> vec2;
            vector<int> vec3;
            int st_x = i / N * N, st_y = i % N * N;
            for (int j = 0; j < N*N; j++){
                vec.push_back(sudoku[i][j]);
                vec2.push_back(sudoku[j][i]);
                vec3.push_back(sudoku[st_x + j / N][st_y + j % N]);
            }

            is_ok = is_ok && judge(vec);
            is_ok = is_ok && judge(vec2);
            is_ok = is_ok && judge(vec3);

        }
        printf("%s\n", is_ok ? "Yes":"No");
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

