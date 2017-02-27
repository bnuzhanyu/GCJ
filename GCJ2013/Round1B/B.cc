#include <vector>
#include <iostream>
using namespace std;

const int MAX_N = 1500;
double prob[MAX_N][MAX_N] = { 0 };
int LV[MAX_N] = { 0 };
int SUM_LV[MAX_N] = { 0 };

void init(){
    prob[0][0] = 1.0;
    for (int i = 1; i < MAX_N; i++){
        prob[i][0] = prob[i-1][0] * 0.5;
        for (int j = 1; j < i; j++){
            prob[i][j] = (prob[i-1][j] + prob[i-1][j-1]) * 0.5;
        }
        prob[i][i] = prob[i-1][i-1] * 0.5;
    }

    for (int i = 1; i < MAX_N; i++){
        LV[i] = 4 * (i-1) + 1; 
        SUM_LV[i] = SUM_LV[i-1] + LV[i]; 
    }
}

struct Problem{
    int X, Y, N;
    int y;
    void read(){
        cin >> N >> X >> Y; 
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int y = 1;
        while(1) {
            if (SUM_LV[y] >= N){
                break;
            }
            y++;
        }
        //reach y level

        int topy = 2*(y - 1);
        if (X + Y < topy && Y - X < topy){
            printf("1.0\n");
            return;
        }else if (X + Y > topy || Y - X > topy){
            printf("0.0\n");
            return;
        }else if (X + Y == topy && Y - X == topy){
            printf("%d\n", N == SUM_LV[y] ? 1 : 0);
            return;
        }

        //all situation will be on the two lines exclude top
        //each line contains topy 's diamond [0 , topy-1]
        if (N == SUM_LV[y]){
            printf("1.0\n");
            return;
        }
        int left = N - SUM_LV[y-1];
        int CMN_C = 0;
        int CMN_M = 0; 
        if (left <= topy){
            CMN_C = left;
            CMN_M = Y + 1;
        }else{
            int must_fill = left - topy;
            if (must_fill > Y){
                printf("1.0\n");
                return;
            }
            CMN_C = left - 2 * must_fill;
            CMN_M = Y - must_fill + 1;
        }

        double p = 0;
        for (int i = 0; i < CMN_M; i++){
            p += prob[CMN_C][i];
        }
        printf("%.7f\n", 1 - p);
    }

};
int main(){
    init();
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }

}
