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

void useFile(const string &fname, const string& suf="")
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname + suf + ".out").c_str(), "w", stdout);
}

typedef unsigned long long ll;



template<typename T>
struct MAXHEAP{ //最大堆
    T* content;  //外部容器
    int *hp_pos; //pos[i]表示外部的下标为i的数在堆中的下标
    int *out_pos; //pos_in[i]表示处于堆中第i位的，在外部的下标
    int n;
    void init(T* arr, int *hp, int *out){
        n = 0;
        content = arr;
        hp_pos = hp;
        out_pos = out;
    }

    void change(int hp, int op){
        //将堆中的hp下标的指向外部的op
        out_pos[hp] = op;
        hp_pos[op] = hp;
    }

    void sift_down(int p){//将外部下标为p的元素进行down操作
        int i = hp_pos[p];
        T& cur = content[p];
        while ( 2*i <= n ){
            int t = 2*i;
            if(t+1<=n && content[out_pos[t]] < content[out_pos[t+1]]){
                t++;
            }
            if(cur < content[out_pos[t]]) {
                change(i, out_pos[t]);
                i = t;
            } else {
                break;
            }
        }
        change(i, p);
    }

    void sift_up(int p){ //将外部下标为p的元素进行up操作
        int i = hp_pos[p];
        T& cur = content[p];
        while(i > 1){
            if(content[out_pos[i/2]] < cur){
                change(i, out_pos[i/2]);
                i/=2;
            }else {
                break;
            }
        }
        change(i, p);
    }

    int top(){
        if(n == 0) return -1;
        return out_pos[1];
    }

    void push(int p){//插入外部下标为p的内容
        n++;
        change(n, p);
        sift_up(p);
    }

    void del(int p){
        if(hp_pos[p] == -1){
            return;
        }
        int x = out_pos[n];
        if(x == p) return;
        change(hp_pos[p], x);
        hp_pos[p] = -1;
        n--;
        sift_down(x);
        sift_up(x);
    }
    int size(){ return n;}
};

const int MAXN = 520;

struct NODE{
    int v;
    int x, y;
    bool operator<(const NODE& n)const{
        if(v == n.v) {
            return x == n.x ? (y > n.y): x > n.x;
        }
        return v < n.v;
    }
}node[MAXN*MAXN];

MAXHEAP<NODE> heap;

int ori_board[MAXN][MAXN];
int pos1[MAXN*MAXN], pos2[MAXN*MAXN];

int dp[MAXN][MAXN];
int cnt[MAXN];

void DP2(int H, int W, int sx, int sy, int sz, int new_del)
{
    for(int i=sx; i<sx + sz && i<=H; i++){
        for(int j=sy; j<sy + sz && j<=W; j++){
            if(ori_board[i][j] == -1) dp[i][j] = 0;
            else{
                if(ori_board[i-1][j-1] == -1 || ori_board[i-1][j] == -1 || ori_board[i][j-1] == -1) dp[i][j] = 1;
                else{
                    dp[i][j] = (ori_board[i][j] == ori_board[i-1][j-1] &&
                                ori_board[i][j] != ori_board[i-1][j] &&
                                ori_board[i][j] != ori_board[i][j-1]) ? min(dp[i-1][j-1], min(dp[i-1][j],dp[i][j-1])) + 1 : 1;
                }
            }
            int pos = (i-1)*W + j-1;
            node[pos].x = i - dp[i][j] + 1, node[pos].y = j - dp[i][j] + 1;
            node[pos].v = dp[i][j];

            if(new_del & 1) { //需要删除
                heap.del(pos);
            }
            if(new_del & 2){ //需要插入
                if(ori_board[i][j] != -1)
                    heap.push(pos);
            }
        }
    }
}

int solve(int H, int W){
    memset(cnt, 0, sizeof(cnt));
    int rem = H*W;
    int mx = 1;
    memset(pos1, -1, sizeof(pos1));
    memset(pos2, -1, sizeof(pos2));
    heap.init(node, pos1, pos2);

    DP2(H, W, 1, 1, max(W, H), 2);

    while(1){
        int cur_max_id = heap.top();
        if(cur_max_id == -1) break;
        int v = node[cur_max_id].v;
        mx = max(v, mx);
        int x = node[cur_max_id].x;
        int y = node[cur_max_id].y;
        if(v <= 1) break;
        cnt[v]++;
        rem -= v*v;
        for(int i=x; i< x + v; i++)
        for(int j=y; j< y + v; j++)
            ori_board[i][j] = -1;
        DP2(H, W, x, y, v, 1);
        DP2(H, W, x+v, y, v, 3);
        DP2(H, W, x, y+v, v, 3);
        DP2(H, W, x+v, y+v, v, 3);
    }
    cnt[1] = rem;
    return mx;
}


int main()
{
    useFile("C2");
    int T;
    for(int i=0; i<MAXN; i++) ori_board[i][0] = ori_board[0][i] = -1;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        int H, W;
        cin >> H >> W;
        string str;
        for(int i=1; i<=H; i++){
            cin >> str;
            int c = 1;
            for(int j=0; j<W/4; j++){
                int m = (str[j]<='9')?str[j]-'0':str[j]-'A'+10;
                for(int k=0; k<4; k++)
                    ori_board[i][c++] = ((m>>(3-k))&1);
            }
        }
        int style = 0;
        int mx = solve(H, W);
        for(int i=1; i<=mx; i++)
            if(cnt[i]) style++;

        cout << "Case #" << ca << ": " << style << endl;
        for(int i=mx; i>=1; i--){
            if(cnt[i]) cout << i << " " << cnt[i] << endl;
        }
    }
    return 0;
}
