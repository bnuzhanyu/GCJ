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


int nid;
struct NODE{

    void clear(){ mp.clear();}
    map<string, int> mp;
    int find(const string& str){
        if(mp.find(str)!=mp.end()){
            return mp[str];
        }
        return -1;
    }
    bool insert(const string& str, int &id){
        id = find(str);
        if(id==-1) {
            mp[str] = nid;
            id = nid++;
            return true;
        }
        return false;
    }
};

const int MAXN = 50000;
NODE node[MAXN];

void init(){
    for(int i=0; i<MAXN; i++)
        node[i].clear();
    nid = 1;
}

int build(string& str){ //构建str花了几个mkdir
    str.push_back('/');
    int id = 0;
    int ans = 0;
    int last_i = 0;
    for(int i=1; i<str.size(); i++){
        if(str[i] == '/'){
            string s = str.substr(last_i + 1, i - last_i - 1);
            ans += node[id].insert(s, id);
            last_i = i;
        }
    }
    return ans;
}

int main()
{
    useFile("A2");
    int T;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        init();
        int en, qn;
        cin >> en >> qn;
        string dir;
        for(int i=0; i<en; i++){
            cin >> dir;
            build(dir);
        }
        int ans = 0;
        for(int i=0; i<qn; i++){
            cin >> dir;
            ans += build(dir);
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
    return 0;
}
