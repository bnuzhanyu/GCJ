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
const int MAXN = 85;

struct CARD{
    int id;
    int c, s, t;
    void input(int i){
        id = i;
        cin >> c >> s >> t;
    }
}card[MAXN], card_t[MAXN], card_c1[MAXN], card_c2[MAXN], card_c0[MAXN];


int HAND, TURN, TN, C1N, C2N, C0N;

int GetLastPoint(int pn, int idx){ //get most score that <= idx && play_n <= pn
    int sc = 0;
    int p = 0;
    for(int i=0; i<C0N && p < pn; i++){
        if(card_c0[i].id < idx ){
            sc += card_c0[i].s;
            p++;
        }
    }
    return sc;
}

int C0_Score[MAXN][MAXN];
void init_c0_score(int n){
    for(int i=0; i<=n; i++)
    for(int j=0; j<=n; j++)
        C0_Score[i][j] = GetLastPoint(i, j);
}

bool score_greater(const CARD& lhs, const CARD& rhs)
{
    return lhs.s > rhs.s;
}

int GetNode(int h, int t, int tid, int c1, int c2)
{
    int fc1 = max(C2N+1, 1);
    int ftid = fc1*max(C1N+1, 1);
    int ft = ftid*max(TN+1, 1);
    int fh = ft*(TURN+1);
    return h*fh + t*ft + tid*ftid + c1*fc1 + c2;
}

map<int, int> score_map;

void init(int n){
    HAND = n;
    TURN = TN = C1N = C2N = C0N = 0;
    for(int i=0; i<n; i++){
        if(card[i].t > 0){
            card_t[TN++] = card[i];
            TURN += card[i].t;
        }else{
            if(card[i].c == 0) card_c0[C0N++] = card[i];
            else if(card[i].c == 1) card_c1[C1N++] = card[i];
            else if(card[i].c == 2) card_c2[C2N++] = card[i];
        }
    }
    TURN = min(TURN + 1, n);
    sort(card_c0, card_c0 + C0N, score_greater);
    init_c0_score(n);
    score_map.clear();
}

//h  last_id in in hand + 1
//t  left turns
//tid  next T cards
//c1 next C1 cards
//c2 next C2 cards
int dfs(int h, int t, int tid, int c1, int c2){
    if(h == 0 || t == 0) return 0;
    if(t < 0){
        cout << "never reach here" << endl;
        while(1);
    }
    int id = GetNode(h,t,tid,c1,c2);
    if (score_map.find(id) != score_map.end()){
        return score_map[id];
    }

    int sc = C0_Score[t][h]; //do not play
    if(tid < TN && card_t[tid].id < h){
        sc = max(sc, card_t[tid].s + dfs(min(HAND, h + card_t[tid].c), min(HAND, t + card_t[tid].t - 1), tid + 1, c1, c2));
    }else{
        if(c1 < C1N && card_c1[c1].id < h){
            sc = max(sc, card_c1[c1].s + dfs(min(HAND, h + 1), t - 1, tid, c1 + 1, c2)); //play it
            sc = max(sc, dfs(h, t, tid, c1 + 1, c2));
        }
        if(c2 < C2N && card_c2[c2].id < h){
            sc = max(sc, card_c2[c2].s + dfs(min(HAND, h + 2), t - 1, tid, c1, c2 + 1)); //play it
            sc = max(sc, dfs(h, t, tid, c1, c2 + 1));
        }
    }
    score_map[id] = sc;
    return sc;
}

int main(){
    useFile("C2");
    int T, N, M;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N;
        for(int i=0; i<N; i++)
            card[i].input(i);
        cin >> M;
        for(int i=N; i<N+M; i++)
            card[i].input(i);
        init(N+M);
        cout << "Case #" << ca << ": " << dfs(N, 1, 0, 0, 0) << endl;
    }

}
