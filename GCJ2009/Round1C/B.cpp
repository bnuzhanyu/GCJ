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

typedef long long ll;

double sq(double x) { return x*x; }

int main(){
    useFile("B2");
    int T, N;
    cin >> T;

    for(int ca=1; ca<=T; ca++){
        double vx = 0, vy = 0, vz = 0;
        double ax = 0, ay = 0, az = 0;
        cin >> N;
        int x,y,z,v1,v2,v3;
        for(int i=0; i<N; i++){
            cin >> x >> y >> z >> v1 >> v2 >> v3;
            ax += x, ay += y, az += z;
            vx += v1, vy += v2, vz += v3;
        }
        ax /= N, ay /= N, az /= N;
        vx /= N, vy /= N, vz /= N;
        double m = (vx*vx+vy*vy+vz*vz);
        double n = ax*vx+ay*vy+az*vz;

        double t = 0;
        if(fabs(m) > 1e-7) {
            t = -n / m;
            if(t < 0) t = 0;
        }
        double ans = sq(ax+t*vx) + sq(ay+t*vy) + sq(az+t*vz);
        cout << "Case #" << ca << ": " << fixed << sqrt(ans) << " " << t << endl;
    }

}
