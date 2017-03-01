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

typedef long long ll;

const int MAXN = 200;


typedef map< pair<char,char>, char> MP_A;

char comb[30][30];
bool oppo[30][30];

int main(){
    useFile("B2");
    int T, P, Q, M, N;
    cin >> T;

    for(int ca=1; ca<=T; ca++){
        memset(comb, 0, sizeof(comb));
        memset(oppo, 0, sizeof(oppo));
        string str;
        int C, D;
        cin >> C;
        for(int i=0; i<C; i++){
            cin >> str;
            comb[str[0]-'A'][str[1]-'A'] = str[2];
            comb[str[1]-'A'][str[0]-'A'] = str[2];
           // cout << "comb[" << str[0] << str[1] <<"]=" << str[2] << endl;
        }
        cin >> D;
        for(int i=0; i<D; i++){
            cin >> str;
            oppo[str[0]-'A'][str[1]-'A'] = true;
            oppo[str[1]-'A'][str[0]-'A'] = true;
        }

        cin >> N;
        cin >> str;
        int cnt[30] = {0};
        char res[200] = {255};
        int id = 1;
        int last = 26;
        for(int i=0; i<N; i++){

            int cur = str[i] - 'A';
            //cout << "now push: " << str[i] << " : ";
            if(comb[last][cur] != 0) {
                res[id - 1] = comb[last][cur];
                cnt[last]--;
                last = res[id - 1] - 'A';
                cnt[last]++;
                //cout << "comb" << endl;
            }else{
                bool x = false;
                for(int j=0; j<26; j++){
                    if(oppo[j][cur] && cnt[j]!=0 ){
                        id = 1;
                        x = true;
                        last = 26;
                        memset(cnt, 0, sizeof(cnt));
                        //cout << "clear " << endl;
                        break;
                    }
                }
                if(!x){
                    res[id++] = str[i];
                    cnt[cur]++;
                    last = cur;
                    //cout << "push " << endl;
                }
            }
        }

        cout << "Case #" << ca << ": [";
        for(int i=1; i<id; i++){
            cout << res[i] << ((i == id-1)?"":", ");
        }
        cout << "]" << endl;
    }

}
