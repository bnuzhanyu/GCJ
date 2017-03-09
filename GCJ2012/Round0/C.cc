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
void print_vec(T& container){
    for (auto& x: container){
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void print_map(T& mp){
    for(auto& x: mp){
        std::cout << x.first << " " << x.second << std::endl;
    }
}

bool str_cmp(const string& s1, const string& s2){
    if (s1.size() < s2.size()){
        return true;
    }else if (s1.size() > s2.size()){
        return false;
    }else{
        return s1 < s2;
    }
}

vector<std::string> table;
struct Problem{

    std::string s1, s2;

    void read(){
        cin >> s1 >> s2;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        auto p1 = lower_bound(table.begin(), table.end(), s1, str_cmp);
        auto p2 = upper_bound(table.begin(), table.end(), s2, str_cmp);
        int ans = p2 - p1;
        printf("%d\n", ans);

    }
};

string sq(const vector<int>& s){
    vector<int> mul(s.size() * 2 - 1, 0);
    for (int i = 0; i < s.size(); i++){
    for (int j = 0; j < s.size(); j++){
        mul[i+j] += s[i]*s[j];
    }
    }
    string ret;
    for (auto x : mul){
        ret.push_back(x + '0');
    }
    return ret;
}

void make_palidrom(vector<int> x, bool need_mid, int mid){
    auto y = x;
    if (need_mid){
        x.push_back(mid);
    }
    reverse(y.begin(), y.end());
    for (auto m : y){
        x.push_back(m);
    }
    //print_vec(x);
    table.emplace_back(sq(x));
}

void generate(vector<int>& vec, int cur_i, int width, int pre_sum){
    static vector<int> bak {0,1,2};
    if (cur_i == width){
        make_palidrom(vec, false, 0);
        for (auto x : bak){
            if (pre_sum*2 + x*x <= 9){
                make_palidrom(vec, true, x);
            }
        }
    }else{
        for (auto x : bak){
            if ((pre_sum + x*x)*2 <= 9){
                vec[cur_i] = x;
                generate(vec, cur_i+1, width, pre_sum + x*x);
            }
        }
    }
}

void gen(int sz){
    vector<int> vec(sz, 0);
    vec[0] = 1;
    generate(vec, 1, sz, 1);
    vec[0] = 2;
    generate(vec, 1, sz, 4);
}

void init(){
    table.push_back("1");
    table.push_back("4");
    table.push_back("9");

    for (int sz = 1; sz <= 25; sz++){
        gen(sz);
    }
    sort(table.begin(), table.end(), str_cmp);
    /*
    for (auto s : table){
        cout << s << endl;
    }
    */
}


int main(){
    init();
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}

