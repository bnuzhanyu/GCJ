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
const int MAXN = 120;

string match_table[MAXN];
pair<int,int> win_game[MAXN];
double WP[MAXN], OWP[MAXN], OOWP[MAXN];

double calcWP(int f, int n){
    int win = 0;
    int total = 0;
    for(int i=0; i<n; i++){
        switch(match_table[f][i]){
            case '1' : win++;
            case '0' : total++;
            default : break;
        }
    }
    win_game[f] = make_pair(win, total);
    return win*1.0 / total;
}

double calcOWP(int f, int n){
    double owp = 0;
    for(int i=0; i<n; i++){
        int w = win_game[i].first;
        int t = win_game[i].second;
        switch(match_table[f][i]) {
            case '1': owp += (w)*1.0/(t-1); break;
            case '0': owp += (w-1)*1.0/(t-1); break;
        }
    }
    return owp / win_game[f].second;
}

double calcOOWP(int f, int n){
    double oowp = 0;
    for(int i=0; i<n; i++){
        if(match_table[f][i] != '.') {
            oowp += OWP[i];
        }
    }
    return oowp / win_game[f].second;
}


int main(){
    useFile("A2");

    int T, N, M;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        cin >> N;

        for(int i=0; i<N; i++){
            cin >> match_table[i];
        }

        for(int i=0; i<N; i++) WP[i] = calcWP(i, N);
        for(int i=0; i<N; i++) OWP[i] = calcOWP(i, N);
        for(int i=0; i<N; i++) OOWP[i] = calcOOWP(i, N);

        cout << "Case #" << ca << ":" << endl;
        for(int i=0; i<N; i++)
            cout << fixed << 0.25*WP[i] + 0.5*OWP[i] + 0.25*OOWP[i] << endl;
    }

}
