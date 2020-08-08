#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <stack>
#include <queue>
#include <stdio.h>
#include <cmath>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int START = 1;
const int END = 0;
struct TimePoint {
    TimePoint(int t, int flag, int id) {
        this->t = t;
        this->flag = flag;
        this->id = id;
    }
    int t;
    int flag;
    int id;

    bool operator<(const TimePoint& tp) {
        if (t == tp.t) {
            return flag < tp.flag;
        }
        return t < tp.t;
    }
};

class Problem {
public:
    int T;
    int N;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int assign[1001];

    vector<TimePoint> tps;
    void read() {
        cin >> N;
        int st, ed;
        doing[0] = doing[1] = false;
        tps.clear();
        for (int i = 0; i < N; i++) {
            cin >> st >> ed;
            tps.push_back(TimePoint(st, START, i));
            tps.push_back(TimePoint(ed, END, i));
        }
    }

    bool doing[2];

    void release_work(int id) {
        doing[assign[id]] = false;
    }

    bool assign_work(int id) {
        if (doing[0] && doing[1]) {
            return false;
        }
        if (doing[0]) {
            assign[id] = 1;
        } else {
            assign[id] = 0;
        }
        doing[assign[id]] = true;
        return true;
    }

    string result() {
        string s;
        for (int i = 0; i < N; i++) {
            s.push_back(assign[i] == 0 ? 'C' : 'J');
        }
        return s;
    }

    void solve(int ca) {
        read();
        sort(tps.begin(), tps.end());
        bool ok = true;
        for (int i = 0; i < tps.size(); i++) {
            TimePoint& tp = tps[i];
            if (tp.flag == START) {
                if (!assign_work(tp.id)) {
                    ok = false;
                    break;
                }
            } else {
                release_work(tp.id);
            }
        }
        cout << "Case #" << ca << ": " << (ok ? result() : "IMPOSSIBLE") << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

