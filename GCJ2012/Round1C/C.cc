#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Problem{

int N, M;

std::vector<int> toy;
std::vector<long long> tn;
std::vector<int> box;
std::vector<long long> bn;

void read(){
    cin >> N >> M;
    toy.resize(N + 1);
    tn.resize(N + 1);
    box.resize(M + 1);
    bn.resize(M + 1);

    for (int i = 1; i <= N; i++){
        cin >> tn[i] >> toy[i];
    }
    for (int i = 1; i <= M; i++){
        cin >> bn[i] >> box[i];
    }
}

struct RECORD{
    RECORD(){
        iup_pos = 0;
        iup_res = 0;
        jup_pos = 0;
        jup_res = 0;
    }
    long long iup_pos;
    long long iup_res;
    long long jup_pos;
    long long jup_res;
};

void solve(int ca){
    //printf("Case #%d: ");
    cout << "Case #" << ca << ": ";

    static RECORD rec[200][200];

    for (int i = 1; i <= N; i++){
    for (int j = 1; j <= M; j++){
        if (toy[i] == box[j]){
            
            //i , j-1
            long long fwd = min(tn[i] - rec[i][j-1].jup_pos, bn[j]);
            rec[i][j].jup_pos = rec[i][j-1].jup_pos + fwd;
            rec[i][j].jup_res = rec[i][j-1].jup_res + fwd;

            fwd = min(bn[j] - rec[i-1][j].iup_pos, tn[i]);
            rec[i][j].jup_pos = rec[i-1][j].jup_pos + fwd;
            rec[i][j].jup_res = rec[i-1][j].jup_res + fwd;

        }else{
            rec[i][j].iup_pos = rec[i-1][j].iup_pos;
            rec[i][j].
            rec[i][j].iup_res = rec[i-1][j].iup_res;
            rec[i][j].jup_pos = rec[i][j-1].jup_pos;
            rec[i][j].jup_res = rec[i][j-1].jup_res;
        }
        
    }
    }

    cout << max(rec[N][M].iup_res, rec[N][M].jup_res);

}

};

int main(){
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}
