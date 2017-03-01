#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,n) for(int i=0; i<n; i++)

typedef unsigned long long ull;
typedef unsigned long long ll;

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}

int sq(int x) { return x*x;}

int digit_sq_sum(int num, int base)
{
    int x = 0;
    while(num){
        x += sq(num % base);
        num /= base;
    }
    return x;
}


void parse(vector<int>& vec, const string& str)
{
    vec.clear();
    for(int i=0; i<str.size(); i++){
        if(str[i] == ' ') continue;
        else {
            if(i!=str.size()-1 && str[i+1]=='0') {
                vec.push_back(10); i++;
            }
            else vec.push_back(str[i] - '0');
        }
    }
}

const int MAXN = 10000;

bool debug = false;
struct UNION_SET{
    int* fa;
    void us_init(int *_fa, int _n)
    {
        fa = _fa;
        for(int i=0; i<_n; i++)
            fa[i] = i;
    }

    int us_find(int x)
    {
        if(x != fa[x]) fa[x] = us_find(fa[x]);
        return fa[x];
    }

    void us_union(int x, int y)
    {
        int fx = us_find(x), fy = us_find(y);
        if(fx != fy) fa[fx] = fy;
    }

}us[11];

int sets[11][MAXN];

void init()
{
    for(int i=2; i<=10; i++){
        us[i].us_init(sets[i], MAXN);
        for(int j=2; j<MAXN; j++)
        {
            int x = digit_sq_sum(j, i);
            us[i].us_union(x, j);
        }
    }
}

int main(){
    usefile("A2");
    int T;
    string str;
    vector<int> bases;
    init();
    cin >> T;
    getline(cin , str);
    for(int ca=1; ca<=T; ca++)
    {
        getline(cin, str);
        parse(bases, str);
        int ans = -1;
        debug = true;
        for(int n = 2; ; n++){
            bool flg = true;
            for(int i=0; i<bases.size(); i++){
                if (bases[i] == 2 || bases[i] == 4) continue;
                int x = digit_sq_sum(n, bases[i]);
                if( us[bases[i]].us_find(1) != us[bases[i]].us_find(x) ){
                    flg = false;
                    break;
                }
            }
            if(flg == true) { ans = n; break;}
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
}







