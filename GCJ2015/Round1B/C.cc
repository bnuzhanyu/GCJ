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

struct RunTime{
    double t;
    int minute;
    int d;
    int meet;
    bool operator< (const RunTime& r) const{
        if (fabs(t - r.t) < 1e-9){
            return meet > r.meet;
        }
        else return t > r.t;
    }
};

double calc_cost(int t, int st, int n) {
    return (n + 1 - st / 360.0) * t; //(360.0 - st + 360 * n) / 360 * t;
}

void update(RunTime& r){
    r.meet = r.meet + 1;
    r.t = calc_cost(r.minute, r.d, r.meet);
}

struct Group{
    int d;
    int h;
    int m;
    void input(){
        cin >> d >> h >> m;
    }
};
struct Problem{
    int N;
    int total;
    priority_queue<RunTime> q;
    vector<Group> group;
    void read(){
        cin >> N;
        group.resize(N);
        for (int i = 0; i < N; i++){
            group[i].input();
        }
    }

    void init(){
        total = 0;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < group[i].h; j++){
                int m = group[i].m + j;
                RunTime r;
                r.meet = -1;
                r.d = group[i].d;
                r.minute = group[i].m + j;
                update(r);
                q.push(r);
                total++;
            }
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        init();
        int ans = total; 
        int left = total;
        int meet = total;
        while (true){
            auto cur_t = q.top().t;
            while (!q.empty() && fabs(q.top().t - cur_t) < 1e-9){
                auto r = q.top(); q.pop();
                if (r.meet == 0) {
                    meet--;
                    left--;
                }else{
                    meet++;
                }
                update(r);
                q.push(r);
            }
            ans = min(ans, meet);
            if (meet - left >= ans) break;
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

