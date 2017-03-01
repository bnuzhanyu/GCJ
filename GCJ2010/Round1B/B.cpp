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

const int MAXN = 100;
struct CHICKEN{
    int dis, v;
}chicken[MAXN];

int main()
{
    useFile("B2");
    int T;
    cin >> T;
    int N , K, B, TIME;
    for(int ca=1; ca<=T; ca++){
        cin >> N >> K >> B >> TIME;

        for(int i=N-1; i>=0; i--){
            int x;
            cin >> x;
            chicken[i].dis = B - x;
        }
        for(int i=N-1; i>=0; i--){
            int v;
            cin >> v;
            chicken[i].v = v;
        }
        int cannot_reach = 0;
        int can_reach = 0;
        int ans = 0;
        for(int i=0; i<N && can_reach < K; i++){
            if(chicken[i].dis <= chicken[i].v * TIME) {
                can_reach++;
                ans += cannot_reach;
            }else{
                cannot_reach++;
            }
        }

        cout << "Case #" << ca << ": ";
        if(can_reach == K) cout << ans << endl;
        else cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}
