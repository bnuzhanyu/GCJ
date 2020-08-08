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

struct POS {
    int u, d, l, r;
};


class Problem {
public:
    int T;
    int N;
    bool check(int i, int j) {
        return i >= 0 && i < R && j >= 0 && j < C;
    }

    int fetch(int i, int j) {
        if (check(i, j)) {
            return S[i][j];
        } else {
            return 0;
        }
    }

    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int R, C;
    vector<vector<int>> S;
    vector<vector<POS>> pos;
    vector<pair<int,int>> needCheck;
    long long total;
    void read() {
        cin >>  R >> C;
        S.clear();
        pos.clear();
        total = 0;
        for (int i = 0; i < R; i++) {
            vector<int> d;
            vector<POS> pt;
            int x;
            for (int j = 0; j < C; j++) {
                cin >> x;
                d.push_back(x);
                total += x;
                POS p;
                p.u = i - 1;
                p.l = j - 1;
                p.r = j + 1;
                p.d = i + 1;
                pt.push_back(p);
                needCheck.push_back(make_pair(i, j));
            }
            pos.push_back(pt);
            S.push_back(d);
        }
    }

    bool should_elem(int i, int j) {
        if (S[i][j] == 0) {
            return false;
        }
        POS& p = pos[i][j];
        int s = 0, c = 0;
        int a = fetch(p.u, j); s += a; c += (a > 0);
        a = fetch(p.d, j); s += a; c += (a > 0);
        a = fetch(i, p.l);s += a; c += (a > 0);
        a = fetch(i, p.r);s += a; c += (a > 0);
        return c * S[i][j] < s;
    }

    int toId(int r, int c) {
        return r * C + c;
    }

    pair<int, int> fromId(int id) {
        return make_pair(id / C, id % C);
    }

    void update(unordered_set<int>& next, int i, int j) {
        //cout << "update " << i << " " << j << endl;
        POS& p = pos[i][j];
        S[i][j] = 0;
        if (check(p.u, j)) {
            pos[p.u][j].d = p.d;
            next.insert(toId(p.u, j));
        }
        if (check(p.d, j)) {
            pos[p.d][j].u = p.u;
            next.insert(toId(p.d, j));
        }
        if (check(i, p.l)) {
            next.insert(toId(i, p.l));
            pos[i][p.l].r = p.r;
        }
        if (check(i, p.r)) {
            next.insert(toId(i, p.r));
            pos[i][p.r].l = p.l;
        }
    }

    bool elem(long long& sum, long long& cur_sum) {
        bool e = false;
        vector<pair<int, int> > vec;
        //cout << "elem " << sum << " " << cur_sum<< endl;
        sum += cur_sum;
        for (auto& pr : needCheck) {
            int i = pr.first, j = pr.second;
            if (should_elem(i, j)) {
                vec.push_back(make_pair(i, j));
                cur_sum -= S[i][j];
                e = true;
            } 
        }
        unordered_set<int> uset;
        for (int i = 0; i < vec.size(); i++) {
            update(uset, vec[i].first, vec[i].second);
        }
        needCheck.clear();
        for (auto& id : uset) {
            needCheck.push_back(fromId(id));
        }
        return e;
    }

    void solve(int ca) {
        read();
        long long res = 0;
        while (elem(res, total)) {

        }
        cout << "Case #" << ca << ": " << res << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

