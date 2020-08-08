#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <stack>
#include <queue>
#include <stdio.h>
#include <cmath>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void rmq_init(vector<int> arr, int maxn[][20])
{
	int n = arr.size();
    int tem = (int)floor(log2((double)n));
    for(int i=1;i<=n;i++)  
        maxn[i][0] = arr[i-1];
    for(int j=1;j<=tem;j++)
    for(int i=1;i+(1<<j)-1<=n;i++)
    {
         maxn[i][j] = max(maxn[i][j-1],maxn[i+(1<<(j-1))][j-1]);
    }
}

int query(int a,int b, int maxn[][20])
{
    a++, b++;
   int k = log2(b-a+1);
   return max(maxn[a][k],maxn[b-(1<<k)+1][k]);
}

class Problem {
public:
    int T;
    int N, K;
    vector<int> charles;
    vector<int> delila;
    
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int charles_rmq[200][20];
    int delila_rmq[200][20];
    void read() {
        cin >> N >> K;
        charles.clear();
        charles.resize(N+1);
        delila.clear();
        delila.resize(N+1);
        for (int i = 0; i < N; i++) {
            cin >> charles[i];
        }
        for (int i = 0; i < N; i++) {
            cin >> delila[i];
        }

        rmq_init(charles, charles_rmq);
        rmq_init(delila, delila_rmq);

    }

    void solve(int ca) {
        read();
        int ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i; j < N; j++) {
                int c = query(i, j, charles_rmq);
                int d = query(i, j, delila_rmq);
                if (abs(c - d) <= K) {
                    ans++;
                }
            }
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

