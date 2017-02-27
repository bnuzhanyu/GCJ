#include <vector>
#include <iostream>
using namespace std;

struct Problem{
    int sz[200]; 
    int add[200];
    unsigned long long A;
    int N;

    void read(){
        cin >> A >> N;
        for (int i = 0; i < N; i++){
            cin >> sz[i];
            add[i] = N;
        }
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        if (A == 1){
            printf("%d\n", N);
            return;
        }

        sort(sz, sz + N);
        for (int i = 0; i < N; i++){
            //to eat sz[i], will cost add[i] at current state
            long long cur = A - 1;
            if (A <= sz[i]){
                add[i] = 0;
                while (add[i] < N){
                    A += (A-1);
                    add[i]++;
                    if (A > sz[i]){
                        break;
                    }
                }
                if (add[i] >= N){
                    add[i] = N;
                    break;
                }
            }else{
                add[i] = 0;
            }
            A += sz[i];
        }

        int total_op = 0;
        int ans = N;
        for (int i = 0; i < N; i++){
            total_op += add[i];
            ans = min(ans, total_op + N - i - 1);
        }
        printf("%d\n", ans);
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
