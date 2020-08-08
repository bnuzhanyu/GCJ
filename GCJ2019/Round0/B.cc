#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Problem {
public:
    int T;
    int N;
    string path;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    void read() {
        cin >> N;
        cin >> path;
    }

    void solve(int ca) {
        read();
        for (int i = 0; i < path.size(); i++) {
            path[i] = (path[i] == 'E') ? 'S' : 'E';
        }
        cout << "Case #" << ca << ": " << path << endl;
    }
};

int main() {
    Problem p;
    p.go();
}

