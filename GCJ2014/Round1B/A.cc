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

using Seq = vector<pair<char, int> >;

struct Problem{

    int N;
    vector<Seq> vec;
    Seq count(const string& str){
        Seq seq;
        char cur = str[0];
        int cnt = 0;
        for (auto c : str){
            if (c == cur) cnt++;
            else{
                seq.push_back(make_pair(cur, cnt));
                cur = c;
                cnt = 1;
            }
        }
        seq.push_back(make_pair(cur, cnt));
        return seq;
    }

    void read(){
        cin >> N;
        for (int i = 0; i < N; i++){
            string s;
            cin >> s; 
            auto seq = count(s);
            vec.push_back(seq);
        }
    }

    bool check_valid(){
        int len = vec[0].size();
        for (int i = 0; i < vec.size(); i++){
            if (vec[i].size() != len){
                return false;
            }
        }
        for (int c = 0; c < len; c++){
            char ch = vec[0][c].first;
            for (int i = 0; i < vec.size(); i++){
                if (vec[i][c].first != ch){
                    return false;
                }
            }
        }
        return true;
    }

    int find_min_step(vector<int>& num){ //could do in NlogN
        int ret = 1<<30; 
        for (int i = 0; i < num.size(); i++){
            int mid = num[i];
            int sum = 0;
            for (int j = 0; j < num.size(); j++){
                sum += abs(num[j] - mid);
            }
            ret = min(ret, sum);
        }
        return ret;
    }

    int min_step(){
        int len = vec[0].size();
        int sum = 0;
        for (int c = 0; c < len; c++){
            vector<int> num;
            for (int i = 0; i < vec.size(); i++){
                num.push_back(vec[i][c].second);
            }
            sum += find_min_step(num);
        }
        return sum;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        if (!check_valid()){
            printf("Fegla Won\n");
        }else{
            printf("%d\n", min_step());
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

