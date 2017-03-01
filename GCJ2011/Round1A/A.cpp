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
using namespace std;

void useFile(const string &fname , const string& suf = "")
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname + suf +".out").c_str(), "w", stdout);
}

typedef long long ll;
const int MAXN = 1001;

int main(){
    useFile("A2");
    int T;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        ll N;
        int pd, pg;
        cin >> N >> pd >> pg;

        bool ans = false;

        if(pg == 100 && pd < 100 || pg == 0 && pd > 0) {
            ans = false;
        }else{
            if(N > 100) N = 100;
            for(int i=1; i<=N; i++)
              if(i * pd % 100 == 0) ans = true;
        }
        cout << "Case #" << ca << ": " << (ans ? "Possible" : "Broken") << endl;
    }

}
