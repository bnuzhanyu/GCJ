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

typedef long long ll;

struct Point {
    ll x, y;
    void output() {
        cout << x << " " << y << endl;
    }
};

struct Seg {
    ll st;
    ll ed;
    int p;
    int h;
};

struct SegCmp1 {
    bool operator() (const Seg& s1, const Seg&s2) {
        if (s1.st == s2.st) {
            return s1.ed > s2.ed;
        }
        return s1.st < s2.st;
    }
};

struct SegCmp2 {
    bool operator()(const Seg& s1, const Seg&s2) {
        return s1.p < s2.p;
    }
};

struct Query {
    ll v1, v2, A, B, C, M;
    void input() {
        cin >> v1 >> v2 >> A >> B >> C >> M;
    }
    ll gen(ll x1, ll x2) {
        return (A * x1 + B * x2 + C) % M + 1;
    }
};

struct CombQuery {
    Query q1;
    Query q2;

    void input() {
        q1.input();
        q2.input();
    }

    vector<Point> gen(int n) {
        vector<Point> pts;
        Point p1, p2;
        p1.x = q1.v1, p1.y = q2.v1;
        p2.x = q1.v2, p2.y = q2.v2;
        pts.push_back(p1);
        pts.push_back(p2);
        for (int i = 2; i < n; i++) {
            Point pt;
            pt.x = q1.gen(p2.x, p1.x);
            pt.y = q2.gen(p2.y, p1.y);
            pts.push_back(pt);
            p1 = p2;
            p2 = pt;
        }
        return pts;
    }
};

vector<Seg> build(vector<Point>& ph) {
    vector<Seg> segs;
    for (Point pt:ph) {
        Seg seg;
        seg.st = pt.x - pt.y;
        seg.ed = pt.x + pt.y;
        seg.p = pt.x;
        seg.h = pt.y;
        segs.push_back(seg);
    }
    std::sort(segs.begin(), segs.end(), SegCmp1());
    vector<Seg> seg2;
    for (Seg seg : segs) {
        if (seg2.empty()) {
            seg2.push_back(seg);
        } else {
            if (seg2.back().ed < seg.ed) {
                seg2.push_back(seg);
            }
        }
    }
    return seg2;
}

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int N, K;
    vector<Point> ph;
    vector<Point> xy;
    void read() {
        cin >> N >> K;
        CombQuery tQ, bQ;
        tQ.input();
        bQ.input();

        ph = tQ.gen(N);
        xy = bQ.gen(K);
        /*
        cout << "start--" << endl;
        for (Point pt : ph) {
            pt.output();
        }
        for (Point pt : xy) {
            pt.output();
        }
        */
    }

    bool cover(Seg& seg, int x, int y) {
        if (x <= seg.st || x >= seg.ed) {
            return false; 
        }
        return y <= (seg.h - abs((ll)x - seg.p));
    }

    bool cover(vector<Seg>& segs, int x, int y) {
        if (x <= segs[0].p) {
            return cover(segs[0], x, y); 
        }
        if (x >= segs.back().p) {
            return cover(segs.back(), x, y);
        }
        int l = -1, r = segs.size() - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (segs[mid].p > x) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }

        bool ok = (l >= 0) && cover(segs[l], x, y);
        ok = ok || ((l + 1 < segs.size()) && cover(segs[l + 1], x, y));
        return ok;
    }

    void solve(int ca) {
        read();
        vector<Seg> segs = build(ph);
        int ans = 0;
        for (Point pt : xy) {
            if (cover(segs, pt.x, pt.y)) {
                ans++;
            }
        }
        cout << "Case #" << ca << ": " << ans << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

