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

void useFile(const string &fname)
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname+".out").c_str(), "w", stdout);
}

typedef unsigned long long ll;


const int MAXN = 1000001;

struct GOLD{
    int lb;
    int ub;
}gold[MAXN];

void init()
{
    double f = (sqrt(5) - 1) / 2;
    for(int i=1; i<=MAXN; i++){
        gold[i].lb = (f * i);
        gold[i].ub = gold[i].lb + i;
    }
}

/* 1-b 之间，有多少个和f在一起会赢*/
int AWIN(int b, int f)
{
    if(b <= gold[f].lb) return b;
    if(b < gold[f].ub) return gold[f].lb;
    else return gold[f].lb + (b - gold[f].ub);
}


int main()
{
    useFile("C2");
    init();
    int T;
    int A1,A2,B1,B2;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> A1 >> A2 >> B1 >> B2;
        ll ans = 0;
        for(int i=A1; i<=A2; i++){
            ans += AWIN(B2, i) - AWIN(B1 - 1, i);
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
    return 0;
}
