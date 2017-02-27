#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

struct Problem{

    int X, Y;
    string dir;
    void read(){
        cin >> X >> Y;
    }

    long long nstep_reach(int n){
        return  n * (long long)(n + 1) / 2;
    }

    int calc_steps(){
        if (X == 0 && Y == 0){
            return 0;
        }
        int sum = abs(X) + abs(Y);
        int st = sum % 2 ? 1 : 3;

        while (true){
            if (nstep_reach(st) >= sum){
                break;
            }
            st++;
            if (nstep_reach(st) >= sum){
                break;
            }
            st+=3;
        }
        return st;
    }

    void update(int& c, int s){
        if (c > 0) c -= s;
        else c += s;
    }

    void route(int s){
        while (s > 0){
            if (abs(X) > abs(Y)){
                dir.push_back(X>0 ? 'E' : 'W');
                update(X, s);
            }else{
                dir.push_back(Y>0 ? 'N' : 'S');
                update(Y, s);
            }
            s--;
        }
        //printf("final: X=%d Y=%d,  ", X, Y);
        reverse(dir.begin(), dir.end());
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int min_step = calc_steps();
        route(min_step);
        printf("%s\n", dir.c_str());
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

