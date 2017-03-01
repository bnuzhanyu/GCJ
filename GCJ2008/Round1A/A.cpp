#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <string.h>
#include <stdio.h>
using namespace std;

void useFile(const string &fname)
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname+".out").c_str(), "w", stdout);
}

int num[1000];
int num2[1000];

int main()
{
    useFile("A2");
    int T, N, Q;
    string name;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N;

        for(int i=0; i<N; i++) cin >> num[i];
        for(int i=0; i<N; i++) cin >> num2[i];

        sort(num, num+N);
        sort(num2, num2+N, greater<int>());
        long long ans = 0;
        for(int i=0; i<N; i++) ans += num[i] * (long long)num2[i];

        cout << "Case #" << ca << ": " << ans << endl;
    }
    return 0;
}
