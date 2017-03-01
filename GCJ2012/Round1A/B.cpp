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
const int MAXN = 1010;

struct GAME{
    int a, b;
    void input(){ cin >> a >> b; }
    bool operator<(const GAME& g)const{
        return b < g.b;
    }
}games[MAXN];

bool sort_by_a(int i, int j)
{
    if(games[i].a == games[j].a) return games[i].b > games[j].b;
    else return games[i].a < games[j].a;
}

bool sort_by_b(int i, int j)
{
    if(games[i].b == games[j].b) return games[i].a > games[j].a;
    else return games[i].b < games[j].b;
}

int need[2][MAXN];
int played[MAXN];

int find_one_star(int n, int cur_score)
{
    int ret = -1;
    for(int i=0; i<n; i++)
    {
        if(played[i] == 0 && cur_score >= games[i].a){
            if( ret == -1 || games[i].b > games[ret].b) ret = i;
        }
    }
    return ret;
}


int solve(int n)
{
    sort(games, games+n);
    for(int i=0; i<n; i++) {
        played[i] = 0;
    }

    int cur_star = 0;
    int pn = 0;
    int i = 0, j = 0;

    while(i < n){
        if(games[i].b <= cur_star){
            cur_star += (2 - played[i]);
            pn++;
            played[i] = 2;
            i++;
        }else{
            int ret = find_one_star(n, cur_star);
            if(ret == -1) return -1;
            played[ret] = 1;
            cur_star++;
            pn++;
        }
    }
    return pn;
}



int main(){
    useFile("B2");

    int T, N;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N;
        for(int i=0; i<N; i++)
            games[i].input();
        int ans = solve(N);

        cout << "Case #" << ca << ": ";
        if(ans == -1) cout << "Too Bad" << endl;
        else cout << ans << endl;
    }
}
