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


struct BitTree {
    vector<int> arr;
    int n;
    void init(int _n) {
        arr.clear();
        n = _n;
        arr.resize(n+1);
        for (int i = 0; i < n+1; i++) {
            arr[i] = 0;
        }
    }
    int lowbit(int x) {
        return x & -x;
    }

    void add(int pos, int v) {
        while(pos <= n) {
            arr[pos] += v;
            pos += lowbit(pos);
        }
    }

    int query(int pos) {
        int ans = 0;
        while(pos > 0) {
            ans += arr[pos];
            pos -= lowbit(pos);
        }
        return ans;
    }
};

struct PT_POS {
    int up;
    int down;
    PT_POS() {
        up = 0;
        down = 0;
    }
};

struct PT {
    int v, h;
    int id;

    bool operator<(const PT& other) {
        return v < other.v;
    }
};

class Problem {
public:
    int T;
    int V1, H1, A, B, C, D, E, F, M;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    vector<PT> pts;
    vector<PT_POS> left;
    vector<PT_POS> right;
    int N;
    int calc(int a, int b, int c, int m, int v, int h) {
        return ((long long)a * v + (long long)b * h + c) % m;
    }

    void read() {
        cin >> N >> V1 >> H1 >> A >> B >> C >> D >> E >> F >> M;
        pts.resize(N);
        left.clear(); left.resize(N);
        right.clear(); right.resize(N);
        pts[0].v = V1;
        pts[0].h = H1;
        pts[0].id = 0;
        for (int i = 1; i < N; i++) {
            pts[i].v = calc(A, B, C, M, pts[i-1].v, pts[i-1].h);
            pts[i].h = calc(D, E, F, M, pts[i-1].v, pts[i-1].h);
            pts[i].id = i;
        }
    }

    
    void calc(vector<PT_POS>& pos, vector<PT> pts) {
        BitTree bt;
        bt.init(M);
        int sz = pts.size();
        int begin = 0;
        int i = 0;
        while (begin < sz) {
            int v = pts[begin].v;
            while(i < sz && pts[i].v == v) {
                i++;
            }
            for (int j = begin; j < i; j++) {
                int id = pts[j].id;
                pos[id].up = bt.query(pts[j].h);
                pos[id].down = begin - bt.query(pts[j].h + 1);
                //printf("pos[%d]: up:%d, down:%d\n", id, pos[id].up, pos[id].down);
            }
            for (int j = begin; j < i; j++) {
                bt.add(pts[j].h+1, 1);
            }
            begin = i;
        }
    }

    void solve(int ca) {
        read();
        sort(pts.begin(), pts.end());
        calc(left, pts);
        reverse(pts.begin(), pts.end());
        calc(right, pts);
        long long total = (long long)N*(N-1)*(N-2) / 6;
        for (int i = 0; i < pts.size(); i++) {
            total -= left[i].up * (long long)right[i].down;
            total -= left[i].down * (long long)right[i].up;
        }
        cout << "Case #" << ca << ": " << total << endl;;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

