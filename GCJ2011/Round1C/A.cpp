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
const int MAXN = 60;

string tile[MAXN];

int main(){
    useFile("A2");

    int T, N, M, D;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        int R, C;
        cin >> R >> C;
        for(int i=0; i<R; i++){
            cin >> tile[i];
        }
        bool flag = true;
        for(int i=0; i<R && flag; i++){
            for(int j=0; j<C && flag; j++){
                if(tile[i][j] == '#') {
                    if(i==R-1 || j==C-1) {
                        flag =false;
                    }else{
                        if(tile[i+1][j] != '#' || tile[i][j+1] != '#' || tile[i+1][j+1]!='#')
                            flag =false;
                        else{
                            tile[i][j] = '/';
                            tile[i][j+1] = '\\';
                            tile[i+1][j] = '\\';
                            tile[i+1][j+1] = '/';
                        }
                    }
                }
            }
        }
        cout << "Case #" << ca << ":" << endl;
        if(flag){
            for(int i=0; i<R; i++)
                cout << tile[i] << endl;
        }else{
            cout << "Impossible" << endl;
        }
    }

}
