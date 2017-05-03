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

double prob[60][60];
double calc_prob(vector<double>& p, int N, int K){
    //at least K machine work right
    prob[0][0] = 1 - p[0];
    prob[0][1] = p[0];
    for (int i = 1; i < N; i++){
        prob[i][0] = prob[i-1][0] * (1 - p[i]);
        for (int j = 1; j <= i; j++){
            prob[i][j] = prob[i-1][j] * (1 - p[i]) 
                       + prob[i-1][j-1] * p[i];
        }
        prob[i][i+1] = prob[i-1][i] * p[i];
    }
    double ret = 0;
    for (int i = K; i <= N; i++){
        ret += prob[N-1][i];
    }
    return ret;
}

struct Problem{

    int N, K;
    double U;
    vector<double> p;
    void read(){
        cin >> N >> K;
        cin >> U;
        for (int i = 0; i < N; i++){
            double x;
            cin >> x;
            p.push_back(x);
        }
    }

    double fill(int id){
        double left = U;
        vector<double> pp = p;
        pp.push_back(1.0);
        double cur_p = pp[id];
        int c = 1;
        for (int i = id; i < N; i++){
            if ((pp[i + 1] - cur_p) * c > left){
                break;
            }else{
                left -= (pp[i + 1] - cur_p) * c;
                cur_p = pp[i + 1];
                c++;
            }
        }

        if (cur_p == 1.0 && id != 0){
            pp[id - 1] = min(pp[id - 1] + left, 1.0);
        }else{
            cur_p += left / c;
        }
        for (int i = id; i < id + c; i++){
            pp[i] = cur_p;
        }
        return calc_prob(pp, N, K);
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        sort(p.begin(), p.end());

        double max_p = 0;
        for (int i = 0; i < N; i++){
            max_p = max(max_p, fill(i));
        }
        printf("%.8f\n", max_p);
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

