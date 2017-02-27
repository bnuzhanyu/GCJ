#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

bool vowel[26] = { 0 };

void init(){
    std::string s = "aeiou";
    for (auto c : s){
        vowel[c - 'a'] = true;
    }
}

struct Problem{

    int n;
    std::string str;
    void read(){
        cin >> str >> n;
    }

    bool is_vowel(char s){
        return vowel[s-'a']; 
    }
    
    void solve(int ca){
        printf("Case #%d: ", ca);
        long long ans = 0;
        int pre = 0;
        int count = 0;
        for (int i = 0; i < str.size(); i++){
            if (!is_vowel(str[i])){
                count++;
                if (count >= n){
                    pre = i - n + 2;
                    //printf("get at %d, pre=%d\n", i, pre);
                }
            }else{
                count = 0;
            }
            ans += pre; 
        }
        printf("%lld\n", ans);
    }
};

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

