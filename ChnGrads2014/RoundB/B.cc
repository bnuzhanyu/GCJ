#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
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

    struct Border{
        int x1, y1, x2, y2;
    };
    int N;
    int B;
    int sum;
    map<int, int> mpx;
    map<int, int> mpy;
    map<int, long long> mp_disx;
    map<int, long long> mp_disy;
    vector<Border> borders;

    void read(){
        cin >> B;
        int x1, y1, x2, y2;
        sum = 0;
        for (int i = 0; i < B; i++){
            cin >> x1 >> y1 >> x2 >> y2;
            Border border;
            border.x1 = x1;
            border.y1 = y1;
            border.x2 = x2;
            border.y2 = y2;
            borders.push_back(border);
            for (int i = x1; i <= x2; i++){
                mpx[i] += (y2 - y1 + 1);
            }
            for (int i = y1; i <= y2; i++){
                mpy[i] += (x2 - x1 + 1);
            }
            sum += (y2 - y1 + 1)*(x2 - x1 + 1);
        }
    }

    void get_ans(const map<int, int>& mp, map<int,long long>& mpdis){
        int pre_sum = 0;
        int suf_sum = sum;
        long long total_step = 0;
        auto iter = mp.begin();
        int x = (*iter).first;
        for (auto kv : mp){
            total_step += (kv.first - x) * (long long)kv.second;
        }
        int last_x = x;
        for (auto kv : mp){
            total_step += (kv.first - last_x) * (long long)pre_sum;
            total_step -= (kv.first - last_x) * (long long)suf_sum;
            mpdis[kv.first] = total_step;
            pre_sum += kv.second;
            suf_sum -= kv.second;
            last_x = kv.first;
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        get_ans(mpx, mp_disx); 
        get_ans(mpy, mp_disy); 
        long long min_step = 1LL << 62;
        int fx, fy;
        for (auto& b : borders){
            for (int i = b.x1; i <= b.x2; i++){
            for (int j = b.y1; j <= b.y2; j++){
                long long step = mp_disx[i] + mp_disy[j];
                if (step < min_step){
                    fx = i;
                    fy = j;
                    min_step = step;
                }else if(step == min_step){
                    if (fx > i){
                        fx = i;
                        fy = j;
                    }else if (fx == i && fy > j){
                        fy = j;
                    }
                }
            }
            }
        }
        printf("%d %d %lld\n", fx, fy, min_step);
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

