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

struct Task{
    int st;
    int ed;
    int type;
    void input(int t){
        cin >> st >> ed;
        type = t;
    }

    bool operator<(const Task& t)const{
        return st < t.st;
    }

    int period(){
        return ed - st;
    }
};
struct Problem{

    int N;
    int Ac, Aj;
    Task task[402];
    void read(){
        cin >> Ac >> Aj;
        for (int i = 0; i < Ac; i++){
            task[i].input(0);
        }
        for (int i = 0; i < Aj; i++){
            task[i + Ac].input(1);
        }
    }

    int get_sum(const vector<int>& v){
        int sum = 0;
        for (auto x : v){
            sum += x;
        }
        return sum;
    }
    void solve(int ca){
        printf("Case #%d: ", ca);
        sort(task, task + Ac + Aj);
        task[Ac + Aj] = task[0];
        task[Ac + Aj].st += 1440;  

        int work_time[2] = {0};
        for (int i = 0; i < Ac + Aj; i++){
            int t = task[i].type;
            work_time[t] += task[i].period();
        }

        int free_time = 0;
        vector<int> interval_list[2];
        int pre_type = task[0].type;  
        int swap_num = 0;
        for (int i = 1; i < Ac + Aj + 1; i++){
            int t = task[i].type;
            int interval = task[i].st - task[i-1].ed; 
            if (pre_type == t){
                if (interval != 0)
                    interval_list[t].push_back(interval);
            }else{
                free_time += interval;
                swap_num += 1;
            }
            pre_type = t;
        }

        int ss[2];
        ss[0] = get_sum(interval_list[0]) + work_time[0];
        ss[1] = get_sum(interval_list[1]) + work_time[1];
        
        int idx = (ss[0] < ss[1]) ? 0 : 1;
        int wt = ss[idx] + free_time;
        if (wt < 720){
            int idx_big = 1 - idx; 
            sort(interval_list[idx_big].begin(), interval_list[idx_big].end(), greater<int>());
            for (auto t : interval_list[idx_big]){
                wt += t;
                swap_num += 2;
                if (wt >= 720){
                    break;
                }
            }
        }
        printf("%d\n", swap_num);
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

