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


struct Train{
    int t;
    int other;
    bool operator<(const Train&tr) const{
        if(t == tr.t) return other > tr.other;
        else return t < tr.t;
    }
};


void push(vector<Train>& train, int t, int other)
{
    Train x;
    x.t = t; x.other = other;
    train.push_back(x);
}

int solve(vector<Train>& train)
{
    int cnt = 0;
    int other = 0;
    for(int i=0; i<train.size(); i++){
        if(train[i].other == 1) {
            other++;
        }else{
            if(other == 0) cnt++;
            else other--;
        }
    }
    return cnt;
}
int main()
{
    useFile("B2");
    int T, N, Q;
    string name;
    scanf("%d", &T);
    for(int ca=1; ca<=T; ca++){
        int delay, na, nb;
        scanf("%d%d%d", &delay, &na, &nb);
        vector<Train> trainA, trainB;
        Train tr;
        int h, m;
        for(int i=0; i<na; i++){
            scanf("%d:%d", &h, &m);
            push(trainA, h*60+m, 0);
            scanf("%d:%d", &h, &m);
            push(trainB, h*60+m+delay, 1);
        }
        for(int i=0; i<nb; i++){
            scanf("%d:%d", &h, &m);
            push(trainB, h*60+m, 0);
            scanf("%d:%d", &h, &m);
            push(trainA, h*60+m+delay, 1);
        }

        sort(trainA.begin(), trainA.end());
        sort(trainB.begin(), trainB.end());

        cout << "Case #" << ca << ": " << solve(trainA)  << " " << solve(trainB) << endl;

    }
    return 0;
}
