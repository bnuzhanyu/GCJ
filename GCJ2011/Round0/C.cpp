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

int main(){
    useFile("C2");
    int T, P, Q, M, N;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N;
        int min_v = 10000000;
        int sum = 0;
        int xor_sum = 0;
        int a;
        for(int i=0; i<N; i++){
            cin >> a;
            xor_sum ^= a;
            sum += a;
            min_v = min(a, min_v);
        }

        cout << "Case #" << ca << ": ";
        if(xor_sum == 0) cout << sum - min_v << endl;
        else cout << "NO" << endl;
    }

}
