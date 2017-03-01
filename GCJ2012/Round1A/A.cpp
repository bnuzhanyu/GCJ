#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <limits>
using namespace std;

void useFile(const string &fname , const string& suf = "")
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname + suf +".out").c_str(), "w", stdout);
}

typedef long long ll;
typedef unsigned long long ull;
const int MAXN = 100010;

int parse_float(string &s){
    int x = s[0] - '0';
    if(s.size() != 1){
        x = x * 10 + s[2] - '0';
    }
    return x;
}

double typed[MAXN];

double solve(int A, int B)
{
    double min_ans = B + 2;
    for(int i=0; i<=A; i++){
        double cur = typed[A-i] * (2*i + B - A + 1) + (1 - typed[A-i]) * (2*i + B*2 - A + 2);
        min_ans = min(cur, min_ans);
    }
    return min_ans;
}

int main(){
    useFile("A2");

    int T, A, B;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> A >> B;
        typed[0] = 1;
        for(int i=1; i<=A; i++){
            cin >> typed[i];
            typed[i] *= typed[i-1];
        }
        cout << "Case #" << ca << ": " << fixed << solve(A, B) << endl;
    }
}
