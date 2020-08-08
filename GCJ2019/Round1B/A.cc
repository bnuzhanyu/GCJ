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

struct Person {
    void read() { 
        cin >> x >> y >> dir;
    }
    int x, y;
    string dir;
};


struct TreeArray {

    void init(int _n) {
        c.resize(_n + 2);
        for(int i = 0; i <= _n ; i++) {
            c[i] = 0;
        }
        n = _n;
    }
    vector<int> c;
    int n;
    
    int lb (int x){
        return x & (-x);
    }
    int sum(int x){
        x++;
        int ret=0;
        while(x>0){
            ret+=c[x];
            x-=lb(x);
        }
        return ret;
    }
    void add(int x,int d){
        x++;
        while(x<=n){
            c[x]+=d;
            x+=lb(x);
        }
    }

    int at(int id) {
        id++;
        return sum(id) - sum(id-1);
    }
};

class Problem {
public:
    int T;
    int P, Q;
    vector<Person> person;
    vector<int> xs;
    vector<int> ys;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int ns_n;
    int ew_n;
    void read() {
        xs.clear();
        ys.clear();
        person.clear();
        cin >> P >> Q;
        person.resize(P);
        xs.push_back(0);
        xs.push_back(Q);
        ys.push_back(0);
        ys.push_back(Q);
        for (int i = 0; i < P; i++) {
            person[i].read();
            int x = person[i].x;
            int y = person[i].y;
            xs.push_back(x);
            if (x < Q) xs.push_back(x + 1);
            if (x > 0) xs.push_back(x - 1);
            ys.push_back(y);
            if (y < Q) ys.push_back(y + 1);
            if (y > 0) ys.push_back(y - 1);
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        auto xiter = unique(xs.begin(),xs.end());
        xs.erase(xiter, xs.end());
        auto yiter = unique(ys.begin(),ys.end());
        ys.erase(yiter,ys.end());
    }

    int id(vector<int> v, int x) {
        return std::lower_bound(v.begin(), v.end(), x) - v.begin();
    }

    void solve(int ca) {
        read();
        vector<TreeArray> ew_tree;
        vector<TreeArray> ns_tree;
        ns_tree.resize(xs.size());
        for (int i = 0; i < xs.size(); i++) {
            ns_tree[i].init(ys.size());
        }
        ew_tree.resize(ys.size());
        for (int j = 0; j < ys.size(); j++) {
            ew_tree[j].init(xs.size());
        }
        
        for (int i = 0; i < P; i++) {
            int x = person[i].x;
            int y = person[i].y;
            int x_id = id(xs, x);
            int y_id = id(ys, y);
            char dir = person[i].dir[0];
            if (dir == 'N') {
                for (int j = 0; j < xs.size(); j++) {
                    ns_tree[j].add(y_id+1, 1);
                }
            } else if (dir == 'S') {
                for (int j = 0; j < xs.size(); j++) {
                    //ns_tree[j].add(y_id+1, 1);
                    ns_tree[j].add(0, 1);
                    ns_tree[j].add(y_id, -1);
                }
            } else if (dir == 'W') {
                for (int j = 0; j < ys.size(); j++) {
                    ew_tree[j].add(0, 1);
                    ew_tree[j].add(x_id, -1);
                }
            } else if (dir == 'E') {
                for (int j = 0; j < ys.size(); j++) {
                    ew_tree[j].add(x_id+1, 1);
                }
            }
        }

        int mx = 0;
        int max_i, max_j;
        for (int i = 0; i < xs.size(); i++) {
        for (int j = 0; j < ys.size(); j++) {
            int cur= ns_tree[i].sum(j) + ew_tree[j].sum(i);
            //cout << "i:" << i << " " << j << " (" << xs[i] << " " << ys[j] << "):" << cur << endl;
            if (cur > mx) {
                max_i = i;
                max_j = j;
                mx = cur;
            }
        }
        }
        cout << "Case #" << ca << ": " << xs[max_i] << " " << ys[max_j] << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

