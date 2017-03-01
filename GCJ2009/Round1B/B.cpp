#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,n) for(int i=0; i<n; i++)

typedef unsigned long long ull;
typedef long long ll;

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}


int main(){
    usefile("B2");
    int T;
    cin >> T;
    string str;
    for(int ca=1; ca<=T; ca++)
    {
        cin >> str;
        if(!next_permutation(str.begin(), str.end())) {
            str.insert(1, "0");
            for(int i=0; i<str.size(); i++){
                if(str[i] != '0') {swap(str[0], str[i]) ; break;}
            }
        }
        cout << "Case #" << ca << ": " << str << endl;
    }
}







