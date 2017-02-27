#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

struct SegNode{
    int l, r;
    int vmin;
};

struct SegTree{
    vector<SegNode> nodes;
    void init(int N){
        nodes.resize(4 * (N + 1));
        init(1, 1, N);
    }

    void update(int l, int r, int v){
        update(1, l, r, v);
    }

    int min(int l, int r){
        return min(1, l, r);
    }

    void init(int id, int l, int r){
        nodes[id].l = l;
        nodes[id].r = r;
        nodes[id].vmin = 0;
        if (l == r){
            return;
        }
        int mid = (l + r) / 2;
        init(id * 2, l , mid);
        init(id * 2 + 1, mid+1 , r);
    }

    int min(int id, int l, int r){
        if (nodes[id].l == l && nodes[id].r == r){
            return nodes[id].vmin;
        }

        if (nodes[id].vmin > nodes[id*2].vmin){
            nodes[id*2].vmin = nodes[id].vmin;
        }
        if (nodes[id].vmin > nodes[id*2+1].vmin){
            nodes[id*2+1].vmin = nodes[id].vmin;
        }

        int m = (nodes[id].l + nodes[id].r) / 2;
        if (r <= m){
            return min(id * 2, l, r);
        }else if (l > m){
            return min(id * 2 + 1, l, r);
        }else{
            return std::min( min(id * 2, l, m), min(id * 2 + 1, m+1, r));
        }
    }

    void update(int id, int l, int r, int v){

        int up_val = max(v, nodes[id].vmin);
        if (nodes[id].l == l && nodes[id].r == r){
            nodes[id].vmin = up_val;
            return;
        }

        if (nodes[id].vmin > nodes[id*2].vmin){
            nodes[id*2].vmin = nodes[id].vmin;
        }
        if (nodes[id].vmin > nodes[id*2+1].vmin){
            nodes[id*2+1].vmin = nodes[id].vmin;
        }

        int m = (nodes[id].l + nodes[id].r) / 2;
        if (r <= m){
            update(id * 2, l, r, up_val);
        }else if (l > m){
            update(id * 2 + 1, l, r, up_val);
        }else{
            update(id * 2, l, m, up_val);
            update(id * 2 + 1, m+1, r, up_val);
        }
        nodes[id].vmin = std::min(nodes[id*2].vmin, nodes[id*2+1].vmin);
    }
};
struct Tribe{
    int d;
    int n;
    int w, e;
    int s;
    int delta_d;
    int delta_p;
    int delta_s;
    void input(){
        cin >> d >> n >> w >> e >> s >> delta_d >> delta_p >> delta_s;
        e--;
    }
};

struct Day{
    int day;
    int tribe;
    bool operator<(const Day& d) const{
        return day > d.day;
    }
};

struct Problem{

    int N;
    vector<Tribe> tribe;
    void read(){
        cin >> N;
        tribe.resize(N);
        for (int i = 0; i < N; i++){
            tribe[i].input();
        }
    }

    unordered_map<int, int> idx_mp;
    vector<Day> day;

    void make_idx(){
        vector<int> idx_id;
        for (int i = 0; i < N; i++){
            int w = tribe[i].w;
            int e = tribe[i].e;
            for (int j = 0; j < tribe[i].n; j++){
                idx_id.push_back(w);
                idx_id.push_back(e);
                idx_id.push_back(w-1);
                //idx_id.push_back(e-1);
                //idx_id.push_back(w+1);
                idx_id.push_back(e+1);
                w += tribe[i].delta_p;
                e += tribe[i].delta_p;
            }
        }

        sort(idx_id.begin(), idx_id.end());
        int n = unique(idx_id.begin(), idx_id.end()) - idx_id.begin();
        for (int i = 0; i < n; i++){
            idx_mp[idx_id[i]] = i+1; 
        }
        //print_map(idx_mp);
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        std::priority_queue<Day> q;
        for (int i = 0; i < N; i++){
            Day d;
            d.tribe = i;
            d.day = tribe[i].d;
            q.push(d);
        }

        vector<int> count(N, 0);
        make_idx();
        SegTree seg;
        seg.init(idx_mp.size());
        //printf("seg init %d\n", idx_mp.size());

        struct Wall{
            int w, e;
            int h;
        };

        int attack = 0;
        while (!q.empty()){
            int cur_day = q.top().day;
            vector<Wall> wall;
            while (!q.empty() && q.top().day == cur_day){
                auto cur = q.top(); q.pop();
                int t = cur.tribe;
                int w = tribe[t].w + (count[t] * tribe[t].delta_p);
                int e = tribe[t].e + (count[t] * tribe[t].delta_p);
                int strength = tribe[t].s + count[t]*tribe[t].delta_s;
                //printf("day %d, cur tribe %d attack [%d, %d] at %d\n", cur_day, t, w, e, strength);
                w = idx_mp[w];
                e = idx_mp[e];
                int cur_min = seg.min(w, e);
                if (strength > cur_min){
                    attack++;
                    Wall ww;
                    ww.w = w;
                    ww.e = e;
                    ww.h = strength;
                    wall.push_back(ww);
                }
                count[t]++;
                if (count[t] < tribe[t].n){
                    Day d;
                    d.day = tribe[t].d + count[t]*tribe[t].delta_d;
                    d.tribe = t;
                    q.push(d);
                }
            }
            for (auto ww : wall){
                seg.update(ww.w, ww.e, ww.h);
            }
        }

        printf("%d\n", attack);
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

