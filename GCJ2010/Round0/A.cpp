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

int main(){
    useFile("A2");
    int T;
    cin >> T;
    int N;
    ll K;
    for(int ca=1; ca<=T; ca++){
        cin >> N >> K;
        N = (1<<N) - 1;
        cout << "Case #" << ca << ": " << ((K&N)==N ? "ON":"OFF") << endl;
    }
}
