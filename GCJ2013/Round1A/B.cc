#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

struct Problem{

    int N, E, R;
    vector<int> gain;
    void read(){
        cin >> E >> R >> N;
        gain.resize(N);
        for (int i = 0; i < N; i++){
            cin >> gain[i];
        }
    }

    struct Cost{
        int use;
        int gain;
    };

    void solve(int ca){
        printf("Case #%d: ", ca);
        vector<Cost> stk;
        int curE = E;
        for (int i = 0; i < N; i++){
            Cost cost;
            cost.use = curE;
            cost.gain = gain[i]; 
            while (true){
                if (stk.empty()){
                    break;
                }
                auto& b = stk.back();
                if (b.gain <= cost.gain){
                    int give = min(b.use, E - cost.use);
                    b.use -= give;
                    cost.use += give;
                    if (b.use == 0){
                        stk.pop_back();
                    }else{
                        break;
                    }
                }else{
                    break;
                }
            }
            stk.push_back(cost);
            curE = min(E, R);
        }

        long long ans = 0;
        for (auto& c : stk){
            ans += c.gain * (long long)c.use; 
        }
        printf("%lld\n", ans);
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

