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

    int N;
    int R, C, M;
    int left;
    bool reverted;
    char mp[60][60];
    bool success;
    void read(){
        cin >> R >> C >> M;
        reverted = false;
        if (R > C){
            swap(R, C);
            reverted = true;
        }
        left = R*C-M;
        success = true;
    }

    void init(){
        for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            mp[i][j] = '*';
    }

    void fill(int c, int n){ //fill n dots with column num c
        int r = (n+c-1)/c;
        for (int i = 0; i < r; i++){
            for (int j = 0; n > 0 && j < c; j++){
                n--;
                mp[i][j] = '.';
            }
        }
    }

    void solve1(){
        fill(left, left);
    }

    void solve2(){
        if (left == 1){
            fill(1, 1); 
        } else if ((left & 1) || left < 4){
            success = false;
        }else{
            fill(left/2, left);
        }
    }


    void solve3(){
        if (left == 2 || left == 3 || left == 5 || left == 7){
            success = false;
        }else if (left == 1 || left == 4 || left == 6){
            fill ((left+1)/2, left);
        }else if (left == 8 || left == 9){
            fill (3, left);
        }else if (left > 3*C){
            fill (C, left);
            if (left % C == 1){
                mp[left/C][1] = '.';
                mp[left/C-1][C-1] = '*';
            }
        }else if (left <= 3*C){
            fill (C - (3*C - left)/3, left);
        }
    }

    char get(int i, int j){
        if (reverted){
            return mp[j][i]; 
        }else{
            return mp[i][j];
        }
    }

    void print_map(){
        if (reverted){
            swap(R, C);
        }
        for (int i = 0; i < R; i++){
            for (int j = 0; j < C; j++){
                printf("%c", get(i, j));
            }
            printf("\n");
        }
    }

    void solve(int ca){
        printf("Case #%d:\n", ca);
        init();
        if (R==1){
            solve1();
        }else if (R==2){
            solve2();
        }else{
            solve3();
        }
        if (success){
            mp[0][0] = 'c';
            print_map();
        }else{
            printf("Impossible\n");
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

