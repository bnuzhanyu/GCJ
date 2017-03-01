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

void useFile(const string &fname , const string& suf = "")
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname + suf +".out").c_str(), "w", stdout);
}

typedef long long ll;
const int MAXN = 10001;

string word[MAXN];

int calc(const string& wd, char c)
{
    int ans = 0;
    for(int i=0; i<wd.size(); i++){
		ans = ans * 2 + (wd[i] == c);
    }
    return ans;
}

int pattern[26][MAXN];

void init(int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<26; j++)
        pattern[j][i] = calc(word[i], j+'a');
    }
}


int cur_letter;
bool pat_cmp(int x, int y){
    return pattern[cur_letter][x] < pattern[cur_letter][y];
}

int ids[MAXN];

void dfs(const char *letter, int* st, int *ed, int dep, int &res, int &id)
{
    if(ed - st == 1){
        if(res < dep) id = *st;
        else if(res == dep && id > *st) id = *st;
        res = max(res, dep);
        return;
    }
    int c = *letter-'a';
    cur_letter = c;
    sort(st, ed, pat_cmp);
    if(pattern[c][*(ed-1)] == 0)
        dfs(letter+1, st, ed, dep, res, id);
    else{
        while(st < ed){
            int *cur = st;
            while(st < ed && pattern[c][*st] == pattern[c][*cur]){
                st++;
            }
            dfs(letter+1, cur, st, dep+(pattern[c][*cur] == 0), res, id);
        }
    }
}

int run(const char *lis, int n){

    vector<int> vec[20];
    int ans = -1;
    int id = -1;
    for(int i=0; i<n; i++){
        vec[word[i].size()].push_back(i);
    }

    for(int i=0; i<=10; i++){
        if(vec[i].size() != 0){
            for(int j=0; j<vec[i].size(); j++){
                ids[j] = vec[i][j];
            }
            dfs(lis, ids, ids+vec[i].size(), 0, ans, id);
        }
    }
    return id;
}


int main(){
    useFile("B");
    int T, N, M;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N >> M;
        for(int i=0; i<N; i++)
            cin >> word[i];
        init(N);
        cout << "Case #" << ca << ":" ;
        string str;
        for(int i=0; i<M; i++){
            cin >> str;
            int id = run(str.c_str(), N);
            cout << " " << word[id];
        }
        cout << endl;
    }

}
