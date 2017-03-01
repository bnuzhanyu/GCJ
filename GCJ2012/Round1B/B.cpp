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
typedef unsigned long long ull;
const int MAXN = 150;

struct HOLE{
    int c, f;
}hole[MAXN][MAXN];


int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
bool visited[MAXN][MAXN];
int dist[MAXN][MAXN];
int inq[MAXN][MAXN];
typedef pair<int,int> PII;

int getAccess(int H, int t, int i, int j, int x, int y)
{ // time need from [i][j] to [x][y] at time t;
    if(hole[i][j].f > hole[x][y].c - 50 || hole[x][y].f > hole[i][j].c - 50 || hole[x][y].f > hole[x][y].c - 50)
        return 1<<28;
    int curH = H - t;

    if(curH > hole[x][y].c - 50){
        int nxtH = hole[x][y].c - 50;
        return (curH - (hole[x][y].c - 50)) + ((nxtH - hole[i][j].f >= 20) ? 10 : 100);
    }

    if(t == 0) return 0;
    else return (curH - hole[i][j].f) >= 20 ? 10 : 100;
}

int dijkstr(int N, int M, int H)
{
    memset(visited, 0, sizeof(visited));
    memset(inq, 0, sizeof(inq));
    for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
        dist[i][j] = 1<<30;

    dist[0][0] = 0;

    queue<PII> q;
    q.push(make_pair(0,0));
    visited[0][0] = true;
    inq[0][0]++;
    bool end = false;
    while(!q.empty() && !end){
        PII cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        visited[x][y] = false;

        for(int d=0; d<4; d++){
            int i = x + dx[d], j = y + dy[d];
            if(i < 0 || i >= N || j < 0 || j >= M) continue;
            int t = dist[x][y];
            int dis = getAccess(H, t, x, y, i, j);
            if(dist[i][j] > dist[x][y] + dis){
                dist[i][j] = dist[x][y] + dis;
                if(!visited[i][j]){
                    visited[i][j] = true;
                    inq[i][j]++;
                    if(inq[i][j] == N*M+1) { end = true ; break; }
                    q.push(make_pair(i, j));
                }
            }
        }
    }
    return dist[N-1][M-1];
}

int main(){
    useFile("B2");

    int T, N, M, H;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> H >> N >> M;
        for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            cin >> hole[i][j].c;
        for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            cin >> hole[i][j].f;

        cout << "Case #" << ca << ": " << fixed << dijkstr(N, M, H) / 10.0 << endl;
    }
}
