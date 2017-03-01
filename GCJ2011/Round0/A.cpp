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

typedef long long ll;

const int MAXN = 200;

int bn;int on;
struct LIGHT{
    int dis;
    int id;
}blue[MAXN], orange[MAXN];

int main(){
    useFile("A2");
    int T, P, Q, M, N;
    cin >> T;

    string color;
    int s;
    for(int ca=1; ca<=T; ca++){
        cin >> N;
        bn = on = 0;
        for(int i=0; i<N; i++){
            cin >> color >> s;
            if(color[0] == 'B') { blue[bn].dis = s; blue[bn++].id = i;}
            else { orange[on].dis = s; orange[on++].id = i;}
        }
        blue[bn].id = N;
        orange[on].id = N;

        int os = 1, bs = 1;
        int oc = 0, bc = 0;
        int ans = 0;
        int odis = orange[0].dis - 1;
        int bdis = blue[0].dis - 1;

        while(oc < on || bc < bn){
            if(orange[oc].id < blue[bc].id) {
                ans += odis + 1;
                bdis = max(0, bdis - odis - 1);
                oc++;
                odis = abs(orange[oc].dis - orange[oc-1].dis);
            }else{
                ans += bdis + 1;
                odis = max(0, odis - bdis - 1);
                bc++;
                bdis = abs(blue[bc].dis - blue[bc-1].dis);
            }
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }

}
