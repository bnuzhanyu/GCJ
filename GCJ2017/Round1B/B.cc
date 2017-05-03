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

struct Problem{

    int N;
    int R, O, Y, G, B, V;
    void read(){
        cin >> N;
        cin >> R >> O >> Y >> G >> B >> V;
    }

    struct Color{
        Color(char _c, char _sub, int _n, int _s){
            c = _c;
            sub = _sub;
            s = _s;
            first = true;
            n = _n - _s;
        }

        bool operator<(const Color& other)const{
            if (n != other.n) return n < other.n;
            else return s < other.s;
        }

        char c, sub;
        int n, s;
        bool first;
        string fetch(){
            string str = "";
            if (first){
                for (int i = 0; i < s; i++){
                    str.push_back(c);
                    str.push_back(sub);
                }
                first = false;
            }
            if (n > 0) {
                str.push_back(c);
                n--;
            }
            return str;
        }
    };

    void solve(int ca){
        printf("Case #%d: ", ca);
        //R Y -> O
        //Y B -> G
        //R B -> V
        Color c1 = Color('R', 'G', R, G);
        Color c2 = Color('B', 'O', B, O);
        Color c3 = Color('Y', 'V', Y, V);

        if (c1 < c2) swap(c1, c2);
        if (c2 < c3) swap(c2, c3);
        if (c1 < c2) swap(c1, c2);
        bool valid = true;
        {
            if (c1.n < 0 || c2.n < 0 || c3.n < 0) valid = false;
            if (c1.n > c2.n + c3.n) valid = false;
            if (c1.n == 0) valid = valid && (c2.s == 0 && c3.s == 0);
            if (c2.n == 0) valid = valid && (c2.s == 0);
            if (c3.n == 0) valid = valid && (c3.s == 0);
        }
        if (!valid){
            printf("IMPOSSIBLE\n");
            return;
        }
        do{
            bool allfetch = (c1.n < c2.n + c3.n);
            string res = c1.fetch();
            if (allfetch) {
                res += c2.fetch(); 
                res += c3.fetch();
            } else {
                if (c2.n) res += c2.fetch();
                else if (c3.n) res += c3.fetch();
            }
            printf("%s", res.c_str());
        }while(c1.n > 0);

        printf("\n");
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

