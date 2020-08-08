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

struct PAIR {
    PAIR(int _x, int _y, int _id) {
        x = _x;
        y = _y;
        id = _id;
    }

    int x,y, id;
    void swap() {
        x ^= 1;
        y ^= 1;
    }

    int type() {
        return x ^ y;
    }
};

class Problem {
public:
    int T;
    int B;

    void go() {
        cin >> T >> B;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int receive(int id) {
        string x;
        cout << id << endl;
        cin >> x;
        if (x[0] == 'N') {
            exit(1);
        }
        return x[0] - '0';
    }

    vector<PAIR> pairs;

    vector<int> query(vector<int>& q) {
        vector<int> ans;
        for (int i = 0; i < q.size(); i++) {
            ans.push_back(receive(q[i]));
        }
        return ans;
    }

    void emptyQuery(int q) {
        for (int i = 0; i < q; i++) {
            receive(1);
        }
    }


    vector<int> findType(int type) {
        vector<int> q;
        for (int i = 0; i < B / 10; i++) {
            for (int j = 0; j < 5; j++) {
                PAIR p = pairs[i * 5 + j]; 
                if (p.type() == type) {
                    q.push_back(p.id);
                    break;
                } 
            }
        }
        return q;
    }

    
    void swap10(vector<int>& q, vector<int>& r, int type) {
        for (int i = 0; i < q.size(); i++) {
            int x = q[i] - 1;
            PAIR base = pairs[x];
            if (base.x == r[i]) {
                continue;
            }
            int st = x / 5 * 5; 
            swapRange(type, st, st + 5);
        }
    }

    void swapRange(int type, int l, int r) {
        for (int i = l; i < r; i++) {
            if (pairs[i].type() == type) {
                pairs[i].swap();
            }
        }
    }

    void swapAll(int id, int r, int type) {
        PAIR base = pairs[id - 1];
        if (base.x == r) {
            return;
        }
        swapRange(type, 0, pairs.size());
    }

    void print(vector<int> v) {
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }
        cout << endl;
    }

    void qlarge() {
        pairs.clear();
        for (int i = 1; i <= B / 2; i++) {
            int x = receive(i);
            int y = receive(B + 1 - i);
            pairs.push_back(PAIR(x, y, i));
        }

        vector<int> q0 = findType(0);
        vector<int> q1 = findType(1);

        int q01 = -1;
        if (q0.size() != 0) {
            vector<int> v0 = query(q0);
            emptyQuery(10 - q0.size());
            swap10(q0, v0, 0);
            q01 = q0[0];
        }

        int q11 = -1;
        if (q1.size() != 0) {
            vector<int> v1 = query(q1);
            emptyQuery(10 - q1.size());
            swap10(q1, v1, 1);
            q11 = q1[0];
        }

        if (q01 != -1) {
            int x = receive(q01);
            swapAll(q01, x, 0);
        }

        if (q11 != -1) {
            int x = receive(q11);
            swapAll(q11, x, 1);
        }
    }

    void output() {
        string ans;
        for (int i = 0; i < pairs.size(); i++) {
            ans.push_back(pairs[i].x + '0');
        }
        for (int i = pairs.size() - 1; i >= 0; i--) {
            ans.push_back(pairs[i].y + '0');
        }
        cout << ans << endl;
        string resp;
        cin >> resp;
        if (resp[0] == 'N') {
            exit(1);
        }
    }

    void read() {
        qlarge();
    }

    void solve(int ca) {
        read();
        output();
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

