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

int sign[4][3] = {
   {1,1,1},
   {-1,1,1},
   {1,1,-1},
   {-1,1,-1}
};

struct POS{
    double x, y, z, p;
    void input(){
        cin >> x >> y >> z >> p;
    }
    double calc(int i){
        return x * sign[i][0] + y * sign[i][1] + z*sign[i][2];
    }
};

struct Problem{

    int N;
    vector<POS> vec;
    void read(){
        cin >> N;
        vec.resize(N);
        for (int i = 0; i < N; i++){
            vec[i].input();
        }
    }

    double power_need(const POS& pos, double x, double y, double z){
        return (fabs(pos.x - x)  + fabs(pos.y - y) + fabs(pos.z - z))/ pos.p;
    }

    bool is_enough(double power){
        double left[4], right[4];
        for (int i = 0; i < 4; i++)
            left[i] = -(1e50), right[i] = 1e50;
        for (auto & v : vec){
            double P = v.p * power;
            for (int i = 0; i < 4; i++){
                left[i] = max(left[i], v.calc(i) - P);
                right[i] = min(right[i], v.calc(i) + P);
                if (left[i] > right[i]) return false;
            }
        }

        double l = (left[0] - right[1]) / 2;
        double r = (right[0] - left[1]) / 2;
        l = max(l, (left[2] - right[3]) / 2);
        r = min(r, (right[2] - left[3]) / 2);
        if (l > r) return false;
        return true;
    }

    double calc_power(double x, double y, double z){
        double need = 0;
        for (auto& v : vec){
            need = max(need, power_need(v, x, y, z));
        }
        return need;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        double left = 0, right = calc_power(0, 0, 0);
        while (left < right - 1e-8){
            double mid = (left + right) / 2;
            if (is_enough(mid)){
                right = mid;
            }else{
                left = mid;
            }
        }
        printf("%.8f\n", left);
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

