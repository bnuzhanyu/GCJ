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
typedef unsigned long long ll;

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}

const int MAXN = 5010;
string words[MAXN];

void construct_pat(vector<vector<bool> >& pat, const string& str)
{
    for(int i=0; i<str.size(); i++){
        vector<bool> b(26, false);
        if(str[i] == '(') {
            i++;
            while(str[i] != ')') {
                b[str[i] - 'a'] = true;
                i++;
            }
        }else{
            b[str[i] - 'a'] = true;
        }
        pat.push_back(b);
    }
}

bool match(const string& w, const vector<vector<bool> >& pat)
{
    for(int i=0; i<w.size(); i++){
        if(pat[i][w[i]-'a'] == false) return false;
    }
    return true;
}

int main(){
    usefile("A2");
    int T, L, D, N;
    //cin >> T;
    for(int ca=1; ca<=1; ca++)
    {
        cin >> L >> D >> N;
        for(int i=0; i<D; i++)
            cin >> words[i];
        string x;
        for(int i=0; i<N; i++){
            cin >> x;
            vector<vector<bool> > pat;
            construct_pat(pat, x);
            int ans = 0;
            for(int j=0; j<D; j++)
                if(match(words[j], pat)) ans++;
            cout << "Case #" << i+1 << ": " << ans << endl;
        }
    }
}







