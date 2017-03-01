#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

struct PUZZLE{
    int pass[4];
    PUZZLE(){ pass[0] = pass[1] = pass[2] = pass[3] = 0; }
    void set(int d, int v){ pass[d] = v;}
    int res(){
        return pass[2]|(pass[0]<<1)|(pass[3]<<2)|(pass[1]<<3);
    }
};


int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int minx=10010, miny=10010, maxx=-1, maxy=-1;
vector<vector<PUZZLE> > puzzle;
int R, C;

void setPass(int x, int y, int d)
{
     if(x>=0 && x<R && y>=0 && y<C)
        puzzle[x][y].set(d, 1);
}

void getPuzzle(char *path, int sx, int sy, int &ex, int& ey, int &d, bool check = false){
    int len = strlen(path);
    int x = sx, y = sy;
    int i=0;
    while(i<len-1){
        if(path[i] == 'W'){
            if(check) setPass(x, y, d);
            x += dx[d]; y += dy[d];
            maxx = max(x, maxx);
            minx = min(x, minx);
            maxy = max(y, maxy);
            miny = min(y, miny);
        }
        else if(path[i] == 'L'){
            d++; d&=3;
        }
        else if(path[i] == 'R'){
            d--; d&=3;
        }
        i++;
    }
    if(check) setPass(x, y, d);
    ex = x+dx[d]; ey = y+dy[d];
    d=(d+2)&3;
}


const int MAXN = 10010;
char path1[MAXN], path2[MAXN];

void ReadAndSolve(){
    int T;
    scanf("%d", &T);
    for(int ca=1; ca<=T; ca++){
        scanf("%s%s", path1, path2);
        minx=10010, miny=10010, maxx=-1, maxy=-1;
        int ex, ey, d = 0;
        getPuzzle(path1, -1, 0, ex, ey, d);
        getPuzzle(path2, ex, ey, ex, ey, d);
        R = maxx - minx + 1;
        C = maxy - miny + 1;
        puzzle.clear();
        puzzle.resize(R);
        for(int i=0; i<R; i++)
            puzzle[i].resize(C);

        ex = -1, ey = 0 - minx, d = 0;
        getPuzzle(path1, -1, -miny, ex, ey, d, true);
        getPuzzle(path2, ex, ey, ex, ey, d, true);

        printf("Case #%d:\n", ca);
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++)
                printf("%x", puzzle[i][j].res());
            printf("\n");
        }
    }
}

void UseStdIO()
{
    ReadAndSolve();
}

void UseFileIO(){
    freopen("GCJPP-B-large.in", "r", stdin);
    freopen("GCJPP-B-large.out", "w", stdout);
    ReadAndSolve();
}

int main()
{
    //UseStdIO();
    UseFileIO();
    return 0;
}
