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

struct NODE{
    int a, b, id;
    bool operator<(const NODE& n)const{
        return a < n.a;
    }
    void input(){ cin >> a >> b;}
}node[2000];

bool bcmp(const NODE&lhs, const NODE&rhs){
    return lhs.b < rhs.b;
}

int bit[2000];
struct BITTREE{
    int lowbit(int x){ return x&(-x); }
    int n;
    int *a;
    void init(int _n, int *_a){
        a = _a;
        n = _n;
        memset(a, 0, sizeof(int)*(n+1));
    }
    void add(int p, int v){
        while(p <= n){
            a[p] += v;
            p += lowbit(p);
        }
    }
    int sum(int p){
        int ans = 0;
        while(p>0){
            ans += a[p];
            p -= lowbit(p);
        }
        return ans;
    }
};

int main()
{
    useFile("A2");
    int T, N;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N;
        for(int i=0; i<N; i++)
            node[i].input();
        sort(node, node + N);
        for(int i=0; i<N; i++){
            node[i].id = i+1;
        }
        sort(node, node+N, bcmp);
        BITTREE bt;
        bt.init(N, bit);
        int ans = 0;
        for(int i=N-1; i>=0; i--){
            int id = node[i].id;
            ans += bt.sum(id);
            bt.add(id, 1);
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
    return 0;
}
