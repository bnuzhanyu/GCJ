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

ll solve(const string& str){
    int bs = 2;
    map<char, int> mp;
    mp[str[0]] = 1;
    for(int i=1; i<str.size(); i++)
        if(str[i]!=str[0]) mp[str[i]]= -1;

    bs = max(bs, (int)mp.size());
    int id = 0;
    ll ans = 0;
    for(int i=0; i<str.size(); i++){
        if(mp[str[i]] == -1) {
            if(id == 1) id++;
            mp[str[i]] = id++;
        }

        ans = ans * bs + mp[str[i]];
    }
    return ans;
}

int main(){
    useFile("A2");

    int T;
    cin >> T;
    string str;
    for(int ca=1; ca<=T; ca++){
        cin >> str;
        cout << "Case #" << ca << ": " << solve(str) << endl;
    }

}
