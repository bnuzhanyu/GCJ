#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>
#include <stack>
#include <queue>
#include <stdio.h>
#include <cmath>
#include <math.h>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

using ll = long long;
using VI = vector<int>;
using VLL = vector<ll>;
using VVI = vector<VI>;
#define FOR(i,a,b) for( int i=(a); i<(b); ++i)
#define RANGE(i,n) for( int i=0; i<(n); ++i)

template<typename T>
using VEC = vector<T>;

template<typename T>
using MAT = vector<vector<T> >;

template<typename T>
void print(const VEC<T>& vec) {
    for (const auto& e : vec) cout << e << " ";
    cout << endl;
}

template<typename T>
void print_with_idx(const VEC<T>& vec) {
    FOR(i,0,vec.size()) {
        cout << i << ":" << vec[i] << endl;
    }
}

template<typename T>
void read_vec(VEC<T>& vec, int n, bool need_clear = true) {
    if (need_clear) vec.clear();
    FOR(i,0,n){
        T x; cin >> x;
        vec.push_back(x);
    }
}

template<typename T>
void read_mat(MAT<T>& mat, int r, int c) {
    mat.resize(r);
    FOR(i,0,r) {
        mat[i].resize(c);
        FOR(j,0,c) {
            cin >> mat[i][j];
        }
    }
}

ll gcd(ll a, ll b) {
    return b>0 ? gcd(b,a%b):a;
}

struct Node{
    int l, r;
    ll v;
    int mid() {
        return (l + r) / 2;
    }
}node[2000020];


struct SegTree {
    
    int n;
    void init(int _n) {
        n = _n;
        build(1, 1, n);
    }

    void build(int id, int l, int r) {
        node[id].l = l;
        node[id].r = r;
        node[id].v = 0;
        if (l == r) {
            return;
        }
        else {
            int mid = (l + r) / 2;
            build(id * 2, l, mid);
            build(id * 2 + 1, mid + 1, r);
        }
    }

    void update(int id, int w, ll a) {
        if (node[id].l == node[id].r) {
            node[id].v = a;
            return;
        }
        int mid = node[id].mid();
        if (w <= mid) {
            update(id * 2, w, a);
        } else {
            update(id * 2 + 1, w, a);
        }
        node[id].v = gcd(node[id*2].v, node[id*2+1].v);
    }

    ll query(int id, int l, int r) {
        r = min(r, n);
        if (node[id].l == l && node[id].r == r)
            return node[id].v;
        int mid = node[id].mid();
        if (r <= mid) {
            return query(id * 2, l, r);
        } else if (l > mid) {
            return query(id * 2 + 1, l, r);
        } else {
            ll v1 = query(id * 2, l, mid);
            ll v2 = query(id * 2 + 1, mid + 1, r);
            return gcd(v1, v2);
        }
    }
};

struct Gnode {
    int v;
    int load;
    ll charge;
};

struct Graph {
    MAT<Gnode> edges;
    void init(int n) {
        edges.clear();
        edges.resize(n);
    }

    void add(int a, int b, int load, ll charge) {
        Gnode node;
        node.v = b;
        node.load = load;
        node.charge = charge;
        edges[a].push_back(node);
        Gnode node2;
        node2.v = a;
        node2.load = load;
        node2.charge = charge;
        edges[b].push_back(node2);
    }

    const VEC<Gnode>& getEdges(int i) {
        return edges[i];
    }
};

SegTree st;
Graph graph;

struct QueryNode {
    int c;
    int w;
    ll ans;
    void input() {
        cin >> c >> w;
    }
};

VEC<QueryNode> query;
VVI queryIdx;

void dfs(int v, int fa, int load, ll charge) {
    if (fa != -1) st.update(1, load, charge);

    for (int q : queryIdx[v]) {
        QueryNode& qn = query[q];
        qn.ans = st.query(1, 1, qn.w); 
    }

    for (const Gnode& node: graph.getEdges(v)) {
        if (node.v != fa) {
            dfs(node.v, v, node.load, node.charge);
        }
    }
    if (fa != -1) st.update(1, load, 0);
}

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            read();
            solve(ca);
        }
    }

    int N, Q;
    void read() {
        cin >> N >> Q;
        graph.init(N+1);

        int a, b, load;
        ll charge;
        int max_load = 0;
        for (int i = 0; i < N - 1; i++) {
            cin >> a >> b >> load >> charge;
            graph.add(a, b, load, charge);
            max_load = max(max_load, load);
        }

        st.init(max_load);
        query.clear();
        query.resize(Q);
        queryIdx.clear();
        queryIdx.resize(N + 1);
        for (int i = 0; i < Q; i++) {
            query[i].input();
            queryIdx[query[i].c].push_back(i);
        }
    }

    void solve(int ca) {
        cout << "Case #" << ca << ":";
        dfs(1, -1, 0, 0);
        for (int i = 0; i < Q; i++) {
            cout << " " << query[i].ans;
        }
        cout << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

