#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>


using namespace std;

struct Problem{

    void read(){
        cin >> D >> N >> A;
        x.resize(N);
        t.resize(N);
        acc.resize(A);
        for (int i = 0; i < N; i++){
            cin >> t[i];
            cin >> x[i];
        }
        for (int i = 0; i < A; i++){
            cin >> acc[i];
        }
    }

    void solve(int ca){
        cout << "Case #" << ca << ":\n";

        for (auto a : acc){
            printf("%.7f\n", get_acc(a));
        }
    }

    double get_acc(double a){
        double st = 0;
        double mx_delay = 0; 
        for (int i = 0; i < N ;i++){
            if (x[i] >= D) {
                if (i != 0){
                    t[i] = t[i-1] + (D - x[i-1]) / (x[i] - x[i-1]) * (t[i] - t[i-1]);
                    x[i] = D;
                    N = i + 1;
                }else {
                    N = 0;
                }
                break;
            }
        }

        for (int i = 0; i < N; i++){
            double cost_t = sqrt(x[i] * 2 / a);
            mx_delay = max(mx_delay, t[i] - cost_t);
        }
        return mx_delay + sqrt(D * 2 / a);
    }

    double D;
    int N, A;
    vector<double> t;
    vector<double> x;
    vector<double> acc;
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
