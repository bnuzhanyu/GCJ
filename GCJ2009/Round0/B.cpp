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

int ht[110][110];

int W, H;

char mark[110][110];
bool visited[110][110];
int head[110][110];

struct EDGE{
    int i,j,next;
}edge[110*110*4*2];
int en;

void add_edge(int x, int y, int i, int j)
{
    edge[en].i = i, edge[en].j = j;
    edge[en].next = head[x][y];
    head[x][y] = en++;
    edge[en].i = x, edge[en].j = y;
    edge[en].next = head[i][j];
    head[i][j] = en++;
}

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};



bool isValid(int x, int y)
{
    return x>=0 && x<H && y>=0 && y<W;
}

void build_graph()
{
    for(int i=0; i<H; i++)
    for(int j=0; j<W; j++){
        int md = -1, cur_ht = ht[i][j];
        for(int d=0; d<4; d++){
            int x = i + dx[d], y = j + dy[d];
            if(isValid(x, y)){
                if(cur_ht > ht[x][y]) {
                    cur_ht = ht[x][y];
                    md = d;
                }
            }
        }
        if(md != -1) add_edge(i, j, i+dx[md], j+dy[md]);
    }
}

void dfs(int i, int j, char m){
    if(visited[i][j]) return;
    visited[i][j] = true;
    mark[i][j] = m;
    for(int e = head[i][j]; e != -1; e = edge[e].next){
        dfs(edge[e].i, edge[e].j, m);
    }
}


void init(){
    en = 0;
    for(int i=0; i<H; i++)
    for(int j=0; j<W; j++)
        head[i][j] = -1, visited[i][j] = 0;
}

int main(){
    usefile("B2");
    int T;
    cin >> T;
    for(int ca=1; ca<=T; ca++)
    {
        cin >> H >> W;
        for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            cin >> ht[i][j];
        init();
        build_graph();

        char c = 'a';
        for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            if(!visited[i][j]) dfs(i, j, c++);
        cout << "Case #" << ca << ":" << endl;
        for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            cout << mark[i][j] << (j==W-1?"\n":" ") ;
    }
}







