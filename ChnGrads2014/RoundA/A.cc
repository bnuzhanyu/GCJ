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

string digits[]={
"zero", "one","two", "three", "four", "five", "six", "seven", "eight", "nine"
};

string nums[]={
"", "", "double", "triple", "quadruple",
"quintuple", "sextuple", "septuple", "octuple", "nonuple", "decuple"
};

struct Problem{

    string phone;
    string format;
    void read(){
        cin >> phone >> format;
    }

    string successive(int d, int n){
        string ret;
        if (n > 1 && n <= 10){
            ret = " " + nums[n] + " " + digits[d]; 
        }else{
            for(int i = 0; i < n; i++){
                ret += " " + digits[d];
            }
        }
        return ret;
    }

    string make_read(const string& s){
        if (s.size() == 0){
            return "";
        }
        char cur = s[0];
        int rep = 1;
        string ret;
        for (int i = 1; i < s.size(); i++){
            if (s[i] == cur){
                rep++; 
            }else{
                ret += successive(cur - '0', rep);
                cur = s[i];
                rep = 1;
            }
        }
        ret += successive(cur - '0', rep);
        return ret;
    }

    void solve(int ca){
        printf("Case #%d:", ca);
        int phone_pos = 0;
        string ans;
        int cur_num = 0;
        for (int i = 0; i <= format.size(); i++){
            if (i == format.size() || format[i] == '-'){
                ans += make_read(phone.substr(phone_pos, cur_num));
                phone_pos += cur_num;
                cur_num = 0;
            }else{
                cur_num = cur_num * 10 + format[i] - '0';
            }
        }
        printf("%s\n", ans.c_str());
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

