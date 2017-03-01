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

const int MAXN = 50;

ll dist[MAXN*2][MAXN*2];
bool visited[MAXN*2][MAXN*2];

const int NS = 0;
const int WE = 1;

struct LIGHT{
    int t, s, w;
    void input(){ cin >> s >> w >> t;}
    ll walk(int d, ll t0){
        ll bg, fact = s + w;
        if(d == NS) bg = t + s;
        else bg = t;
        ll x = (t0>=bg)?(t0-bg+fact)/fact:(t0-bg+1)/fact;

        ll start = bg + fact * x;
        start -= (d==NS?s:w);
        return max(start + 1, t0 + 1);
    }

    ll brute(int d, ll t0){
        ll bg, fact = s + w;
        if(d == NS) bg = t + s;
        else bg = t;
        ll l = -(1<<30), r = 1<<30;
        while(l < r){
            ll mid = l + (r - l)/2;
            if(bg + mid * fact <= t0) l = mid + 1;
            else r = mid;
        }
        ll start = bg + fact * l;
        start -= (d==NS?s:w);
        return max(start+1, t0+1);
    }

}light[MAXN][MAXN];

ll dijkstra(int r, int c)
{
    int sx = r*2 - 1, sy = 0;
    for(int i=0; i<2*r; i++)
    for(int j=0; j<2*c; j++)
        dist[i][j] = 1LL<<60;
    memset(visited, 0, sizeof(visited));
    dist[sx][sy] = 0;
    while(1){
        int mx = -1, my = -1;
        ll min_dis = 1LL<<60;
        for(int x=0; x<r*2; x++)
        for(int y=0; y<c*2; y++){
            if(!visited[x][y] && min_dis > dist[x][y]){
                min_dis = dist[x][y];
                mx = x, my = y;
            }
        }
        if(mx == -1) break;
        visited[mx][my] = true;
        //cout << "dist[" << mx << "," << my << "]: " << dist[mx][my] << endl;
        //update surround point
        int cx, cy;
        //right
        cx = mx, cy = my + 1;
        if(cy != 2*c) {
            if(my/2 == cy/2) {
                dist[cx][cy] = min(dist[cx][cy], light[cx/2][cy/2].walk(WE, dist[mx][my]));
            }else dist[cx][cy] = min(dist[mx][my] + 2, dist[cx][cy]);
            //cout << "dist[" << cx << "," << cy << "]: " << dist[cx][cy] << endl;
        }

        //left
        cx = mx, cy = my - 1;
        if(cy != -1) {
            if(my/2 == cy/2) {
                dist[cx][cy] = min(dist[cx][cy], light[cx/2][cy/2].walk(WE, dist[mx][my]));
            }else dist[cx][cy] = min(dist[mx][my] + 2, dist[cx][cy]);
            //cout << "dist[" << cx << "," << cy << "]: " << dist[cx][cy] << endl;
        }


        //up
        cx = mx - 1, cy = my;
        if(cx != -1) {
            if(mx/2 == cx/2) {
                dist[cx][cy] = min(dist[cx][cy], light[cx/2][cy/2].walk(NS, dist[mx][my]));
            }else dist[cx][cy] = min(dist[mx][my] + 2, dist[cx][cy]);
            //cout << "dist[" << cx << "," << cy << "]: " << dist[cx][cy] << endl;
        }

        //down
        cx = mx + 1, cy = my;
        if(cx != 2*r) {
            if(mx/2 == cx/2) {
                dist[cx][cy] = min(dist[cx][cy], light[cx/2][cy/2].walk(NS, dist[mx][my]));
            }else dist[cx][cy] = min(dist[mx][my] + 2, dist[cx][cy]);
            //cout << "dist[" << cx << "," << cy << "]: " << dist[cx][cy] << endl;
        }
    }
    return dist[0][2*c-1];
}

int main(){
    usefile("B2");
    int T;
    cin >> T;
    for(int ca=1; ca<=T; ca++)
    {
        int m, n;
        cin >> m >> n;
        for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            light[i][j].input();

        cout << "Case #" << ca << ": " << dijkstra(m, n) << endl;
    }
}







