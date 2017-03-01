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
const int MAXN = 2100;

vector<pair<int, bool> > edge[MAXN];
int color[MAXN];
stack<int> stk;

void add(int u, int v)
{
    edge[u].push_back(make_pair(v, true));
    edge[v].push_back(make_pair(u, true));
}

void init(int n)
{
    while(!stk.empty()) stk.pop();

    for(int i=0; i<n; i++){
        edge[i].clear();
        color[i] = 0;
    }
    for(int i=0; i<n; i++){
        add(i, (i+1)%n);
    }

}

struct PAIRCMP{
    int x, n;
    bool operator()(const pair<int, bool> &lhs, const pair<int, bool>&rhs){
        return (lhs.first-x+n)%n < (rhs.first-x+n)%n ;
    }
};



void preprocess(int n)
{
    PAIRCMP cmp;
    cmp.n = n;
    for(int i=0; i<n; i++){
        cmp.x = i;
        sort(edge[i].begin(), edge[i].end(), cmp);
//        cout << "i="<<i <<":";
//        for(int j=0; j<edge[i].size(); j++)
//            cout << " " << edge[i][j].first;
//        cout << endl;
    }
}


int get_a_diffcolor(int c1, int c2, int cn)
{
    if(c1 > c2) swap(c1, c2);
    int x = c2 + 1;
    if(x > cn) x = 1;
    if(x == c1) x++;
    return x;
}

bool color_used[MAXN] = {0};
int dfs(int i, int fa, int root, int n, int &min_wall, queue<pair<int, int> > & q){

    PAIRCMP pcmp;
    pcmp.n = n, pcmp.x = i;
    int lb = lower_bound(edge[i].begin(), edge[i].end(), make_pair(fa, true), pcmp) - edge[i].begin();
    int v = edge[i][lb-1].first;
    if(edge[i][lb].second && (i - fa + n)%n != 1 ) q.push(make_pair(i, lb));
    edge[i][lb - 1].second = false;

    if(i != root){
        stk.push(i);
        return dfs(v, i, root, n, min_wall, q);
    }else{
        vector<int> vec;
        min_wall = min(min_wall, (int)stk.size());
        while(!stk.empty()){
            int x = stk.top(); stk.pop();
            vec.push_back(x);
            if(color[x] != 0){
                color_used[color[x]] = true;
            }
        }
        int id = 1;
        for(int i=0; i<vec.size(); i++){
            int x = vec[i];
            if(color[x] == 0){
                while(color_used[id]) id++;
                if(id <= min_wall){
                    color[x] = id;
                    color_used[id] = true;
                }else{
                    int y = vec[(i+1) % vec.size()];
                    int z = vec[(i-1+vec.size()) % vec.size()];
                    color[x] = get_a_diffcolor(color[y], color[z], min_wall);
                }
            }
        }
        for(int i=0; i<vec.size(); i++){
            int x = vec[i];
            color_used[color[x]] = false;
        }
    }
}


int work(int N, int &res)
{
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));

    while(!q.empty()){
        int ei = q.front().first;
        int ej = q.front().second;
        q.pop();
        stk.push(ei);
        edge[ei][ej].second = false;
        int root = ei;
        int f = edge[ei][ej].first;
        dfs(f, root, root, N, res, q);
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<edge[i].size(); j++){
            edge[i][j].second = true;
        }
    }
    return res;
}

int uu[MAXN], vv[MAXN];

int main(){
    useFile("C2");

    int T, N, M, D;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N >> M;
        init(N);
        int u, v;
        for(int i=0; i<M; i++){
            cin >> uu[i];
        }
        for(int i=0; i<M; i++){
            cin >> vv[i];
        }
        for(int i=0; i<M; i++){
            if(uu[i] == vv[i]-1 || uu[i] == 1 && vv[i] == N) continue;
            add(uu[i]-1, vv[i]-1);
        }
        preprocess(N);
        int res = N;
        work(N, res);
        memset(color, 0, sizeof(color));
        work(N, res);

        cout << "Case #" << ca << ": " << res << endl;
        for(int i=0; i<N; i++)
            cout << (color[i] = max(color[i], 1)) << ((i==N-1)?"\n":" ");
    }

}
