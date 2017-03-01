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

char board[60][60];
char board2[60][60];

void rotate(int n)
{
    for(int i=0; i<n; i++)
    for(int j=0; j<n; j++){
        board2[i][j] = board[n-j-1][i];
    }

    for(int j=0; j<n; j++){
        int x = n-1;
        for(int i=n-1; i>=0; i--){
            if(board2[i][j] != '.'){
                board2[x--][j] = board2[i][j];
            }
        }
        while(x>=0) {
            board2[x--][j] = '.';
        }
    }
}

char seq[150];

bool has_consective_k(char s[], int n, char c, int k)
{
    int cnt = 0;
    for(int i=0; i<n; i++){
        if(s[i] == c) {
            cnt++;
            if(cnt == k) return true;
        }
        else cnt = 0;
    }
    return false;
}


bool startfrom(int i, int j, int di, int dj, int n, char c, int k){
    int x = i, y = j;
    int id = 0;
    while(0<=x && 0<=y && x<n && y<n){
        seq[id++] = board2[x][y];
        x+=di , y+=dj;
    }
    return has_consective_k(seq, id, c, k);
}


bool win(int n, int k, char c)
{
    bool ans = false;
    //horizontal
    for(int i=0; i<n; i++){
        ans = ans || startfrom(i, 0, 0, 1, n, c, k); //horizontal
        ans = ans || startfrom(0, i, 1, 0, n, c, k); //vertical
        ans = ans || startfrom(i, 0, 1, 1, n, c, k);
        ans = ans || startfrom(i, 0, -1, 1, n, c, k);
        ans = ans || startfrom(i, n-1, 1, -1, n, c, k);
        ans = ans || startfrom(i, n-1, -1, -1, n, c, k);
        if(ans) return true;
    }
    return false;
}


int main()
{
    useFile("A2");
    string wins[4] = {"Neither", "Red", "Blue", "Both"};
    int T;
    cin >> T;
    for(int ca=1; ca<=T; ca++){
        int N, K;
        cin >> N >> K;
        for(int i=0; i<N; i++)
            cin >> board[i];
        rotate(N);
        bool winB = win(N, K, 'B');
        bool winR = win(N, K, 'R');
        cout << "Case #" << ca << ": " << wins[(winB<<1) | (winR)]  << endl;
    }
    return 0;
}
