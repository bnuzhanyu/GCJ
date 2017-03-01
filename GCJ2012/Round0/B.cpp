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
const int MAXN = 60;


int main(){
    useFile("B2");
    int T, N, M, Q, S, P;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N >> S >> P;
        int t;
        int ans = 0;
        for(int i=0; i<N; i++){
            cin >> t;
            int x;

            switch(t % 3){
                case 0: x = t / 3; break;
                case 1: x = (t-1) / 3 + 1; break;
                case 2: x = (t-2) / 3 + 1; break;
            }
            if(x >= P) { ans++; continue; }
            if(S <= 0) continue;
            if(t%3 == 1) continue;
            if(t%3 == 0 && x == 0) continue;
            if(x == P-1) S--, ans++;
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
}
