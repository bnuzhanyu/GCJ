#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <string.h>
#include <stdio.h>
using namespace std;

void useFile(const string &fname)
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname+".out").c_str(), "w", stdout);
}

map<string, int> mp;

const int MAXN = 110;
const int MAXQ = 1010;


int queries[MAXQ];
const int INF = (1<<28);
bool visited[MAXN];

int calc(int N, int Q)
{
    memset(visited, 0, sizeof(bool)*N);
    int ans = 0;
    int cnt = 0;
    for(int j=0; j<Q; j++){
        int q = queries[j];
        if(q < N && !visited[q]) {
            if(cnt == N-1) {
                ans++;
                memset(visited, 0, sizeof(bool)*N);
                cnt = 0;
            }
            visited[q] = true;
            cnt++;
        }
    }
    return ans;
}


int main()
{
    useFile("A2");
    int T, N, Q;
    string name;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        mp.clear();
        cin >> N;
        getline(cin, name);
        for(int i=0; i<N; i++){
            getline(cin, name);
            mp[name] = i;
        }
        cin >> Q;
        getline(cin, name);
        for(int i=0; i<Q; i++){
            getline(cin, name);
            if(mp.find(name)==mp.end())
                queries[i] = N;
            else queries[i] = mp[name];
        }
        cout << "Case #" << ca << ": " << calc(N, Q) << endl;

    }
    return 0;
}
