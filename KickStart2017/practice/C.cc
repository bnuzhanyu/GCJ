#include <iostream>
#include <algorithm>

using namespace std;

long long calc(int n){
    return (long long)n * (n + 1) / 2;
}

int main(){
    int T;
    cin >> T;
    for (int ca = 1; ca <= T; ca++){
        int L, R;
        cin >> L >> R;
        cout << "Case #" << ca << ": " << calc(min(L, R)) << endl;
    }
}
