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


vector<vector<int> > valid_list;
void init(){
    for(int i=0; i<9; i++){
        for(int j=i; j<9; j++){
            for(int k=j; k<9; k++){
                if(  (i/3 + j/3 + k/3) % 3 == 0
                   &&(i%3 + j%3 + k%3) % 3 == 0 )
                {
                   vector<int> a;
                   a.push_back(i); a.push_back(j); a.push_back(k);
                   valid_list.push_back(a);
                }
            }
        }
    }
}

long long comb(long long n, int k)
{
    if(k == 0) return 1;
    if(k == 1) return n;
    if(k == 2) return n*(n-1) / 2;
    if(k == 3) return n*(n-1)*(n-2) / 6;
}


long long calc(int pn[])
{
    int cnt[9];
    long long ans = 0;
    for(int i=0; i<valid_list.size(); i++){
        memset(cnt, 0, sizeof(cnt));
        for(int j=0; j<3; j++)
            cnt[valid_list[i][j]]++;

        long long cur = 1;
        for(int j=0; j<9; j++)
            cur *= comb(pn[j], cnt[j]);
        ans += cur;
    }
    return ans;
}

void read(int pn[]){
    int n, a, b, c, d, x, y, m;
    cin >> n >> a >> b >> c >> d >> x >> y >> m;
    memset(pn, 0, sizeof(int)*9);
    do{
        int p = x % 3 * 3 + y % 3;
        pn[p]++;
        x = ((long long)a*x + b) % m;
        y = ((long long)c*y + d) % m;
    }while(--n);

}

int main()
{
    usefile("A2");
    init();
    int p[9];
    int T;
    cin >> T;
    FOR(ca, T){
        read(p);
        cout << "Case #" << ca + 1 << ": " << calc(p) << endl;
    }
    return 0;
}
