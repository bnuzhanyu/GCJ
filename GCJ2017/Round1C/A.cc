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

const static double PI = acos(-1.0);

struct Cake{
    int H, R;
    void input(){
        cin >> R >> H;
    }
    bool operator<(const Cake& c) const{
        return R < c.R;
    }
    long long side(){
        return 2*H*(long long)R;
    }
    long long area(){
        return (long long)R * R;
    }
};
Cake cake[1000];
struct Problem{

    int N, K;
    priority_queue<long long> pq;
    void read(){
        cin >> N >> K;
        for (int i = 0; i < N; i++)
            cake[i].input();
    }

    void solve(int ca){
        sort(cake, cake + N);
        printf("Case #%d: ", ca);

        long long mx = 0;
        long long cur = 0; 
        for (int i = 0; i < K; i++){
            pq.push(-(cake[i].side()));
            cur += cake[i].side();
        }
        mx = cur + cake[K-1].area();

        for (int i = K; i < N; i++){
            auto min_side = -pq.top();
            long long cur_side = cake[i].side();
            mx = max(mx, cur + cake[i].area() + cur_side - min_side);
            if (cur_side > min_side){
                pq.pop();
                pq.push(-cur_side);
                cur -= min_side;
                cur += cur_side;
            }
        }
        printf("%.8f\n", mx *  PI);
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

