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

const int MAXN = 2020;
const int MAXE = 3010;
int head[MAXN*2];

struct EDGE{
    int v, next;
    int id;
}edge[MAXE*2];

int en;
int cust_left[MAXN];
int malted[MAXN];
bool inqueue[MAXN*2];

vector<pair<int,int> > cust_like[MAXN];

void init(int m)
{
    memset(head, -1, sizeof(head));
    memset(cust_left, 0, sizeof(cust_left));
    memset(malted, -1, sizeof(malted));
    for(int i=0; i<m; i++){
        cust_like[i].clear();
    }
    en = 0;
}


void add_edge(int type, int t, int cust)
{
    int u = (type | t);
    edge[en].v = cust;
    edge[en].next = head[u];
    cust_like[cust].push_back(make_pair(type | t, 1));
    edge[en].id = cust_like[cust].size() - 1;
    head[u] = en++;
}

int main()
{
    useFile("B2");
    int T, N, M;
    string name;
    cin >> T;
    for(int ca=1; ca<=T; ca++){

        cin >> N >> M;
        init(M);

        for(int i=0; i<M; i++) {
            int L;
            cin >> L;
            cust_left[i] = L;
            int a, b;
            while(L--){
                cin >> a >> b;
                a--;
                add_edge(a*2, b, i);
            }
        }

        queue<pair<int,int> > q;
        for(int i=0; i<M; i++){
            if(cust_left[i] == 1) {
                cust_left[i] = 0;
                int x = cust_like[i].back().first;
                cust_like[i].back().second = 0;
                if(!inqueue[x]){
                    q.push(make_pair(i, x));
                }
            }
        }

        bool isOk = true;
        while(!q.empty()){
            pair<int,int> c = q.front(); q.pop();

            int cust = c.first, type = c.second /2 , is_malt = c.second & 1;
            if(malted[type] != -1){
                if(malted[type] != is_malt) {
                    isOk = false;
                    break;
                }
            }else{
                malted[type] = is_malt;
                type = (type*2) | (1 - is_malt);
                for(int i=head[type]; i!=-1; i=edge[i].next){
                    int v = edge[i].v;
                    int id = edge[i].id;
                    cust_left[v]--;
                    cust_like[v][id].second = 0;
                    if(cust_left[v] == 1){
                        cust_left[v] = 0;
                        for(int j=0; j<cust_like[v].size(); j++){
                            if(cust_like[v][j].second){
                                int x = cust_like[v][j].first;
                                if(!inqueue[x])
                                    q.push(make_pair(v, x));
                            }
                        }
                    }
                }
            }
        }

        cout << "Case #" << ca << ":";
        if(!isOk) cout << " IMPOSSIBLE" << endl;
        else{
            for(int i=0; i<N; i++)
                cout << " " << (malted[i] == 1);
            cout << endl;
        }
    }
    return 0;
}
