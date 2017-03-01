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
const int MAXN = 2000010;

ll pow_10[20] = {1};
void init()
{
    for(int i=1; i<10; i++){
        pow_10[i] = pow_10[i-1] * 10;
    }
}

bool visited[MAXN];

int digit_n(int x)
{
    int dn = 0;
    while(x){
        dn++;
        x /= 10;
    }
    return dn;
}

int circle(int x, int A, int B)
{
    int dn = digit_n(x);
    int n = 0;
    for(int i = 0; i < dn; i++){
        int last = x % 10;
        x = x / 10 + pow_10[dn-1] * last;
        if(last != 0 && x >= A && x <= B){
            if(!visited[x]) n++;
            visited[x] = true;
        }
    }
    return n * (n - 1) / 2;
}

int main(){
    init();
    useFile("C2");
    int T, A, B;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> A >> B;
        memset(visited, 0, sizeof(visited));
        int ans = 0;
        for(int i=A; i<=B; i++){
            if(visited[i]) continue;
            ans += circle(i, A, B);
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
}
