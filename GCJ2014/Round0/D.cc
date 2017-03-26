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
    vector<double> aa; 
    vector<double> bb; 
    void read(){
        cin >> N;
        aa.resize(N);
        bb.resize(N);
        for (int i = 0; i < N; i++){
            cin >> aa[i];
        }
        for (int i = 0; i < N; i++){
            cin >> bb[i];
        }
    }

    int optimal(const vector<double>& a, 
                const vector<double>& b){
        //a knows b 
        int i = 0, j = 0;
        int awin = 0, bwin = 0;
        while (awin + bwin < N){
            if (a[i] < b[j]){
                bwin++;
                i++;
            }else{
                awin++;
                i++;
                j++;
            }
        }
        return awin;
    }

    void solve(int ca){
        sort(aa.begin(), aa.end());
        sort(bb.begin(), bb.end());
        printf("Case #%d: %d %d\n", ca, optimal(aa, bb), N-optimal(bb, aa));
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

