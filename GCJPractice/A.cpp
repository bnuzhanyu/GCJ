#include <iostream>
#include <string.h>
#include <algorithm>
#include <cstdio>
using namespace std;

/*简单的进制转换问题*/

int getNum(char *num, char *src){

    int sn = strlen(src);
    int ret = 0;
    for(int i=0; num[i]; i++){
        for(int j=0; j<sn; j++){
            if(num[i] == src[j]){
                ret = ret * sn + j;
                break;
            }
        }
    }
    return ret;
}
void setTar(char *dst, char *tar, int num)
{
    int tn = strlen(tar);
    int i = 0;
    while(num){
        int x = num % tn;
        dst[i++] = tar[x];
        num /= tn;
    }
    reverse(dst, dst+i);
    dst[i] = 0;
}

char aln[1000];
char src[100];
char tar[100];


void ReadAndSolve(){
    int T;
    scanf("%d", &T);
    for(int ca=1; ca<=T; ca++){
        scanf("%s%s%s", aln, src, tar);
        int num = getNum(aln, src);
        setTar(aln, tar, num);
        printf("Case #%d: %s\n", ca, aln);
    }
}

void UseStdIO()
{
    ReadAndSolve();
}

void UseFileIO(){
    freopen("GCJPP-A-large.in", "r", stdin);
    freopen("GCJPP-A-large.out", "w", stdout);
    ReadAndSolve();
}

int main()
{
    //UseStdIO();
    UseFileIO();
    return 0;
}
