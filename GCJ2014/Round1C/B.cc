#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <functional>
#include <cmath>

using namespace std;
using ull = unsigned long long;
using ll = long long;
using db = double;
using PII = pair<int, int>;

template<typename T>
void print_vec(T& container, const std::string& sep = " "){
    for (auto& x: container){
        std::cout << x << sep;
    }
    std::cout << std::endl;
}

template<typename T>
void print_map(T& mp){
    for(auto& x: mp){
        std::cout << x.first << " " << x.second << std::endl;
    }
}

ll fact[120];
const int mod = 1000000007;  
void init(){
    fact[0] = 1;
    for (int i = 1; i <= 101; i++){
        fact[i] = fact[i-1] * i % mod;
    }
}

struct Graph{
    
    vector<vector<int> > adj;
    vector<bool> visited;
    vector<int> node_val;
    int line_count;
    vector<int> in_deg;
    int N;

    void init(int n){
        N = n;
        adj.resize(N);
        visited.resize(N);
        node_val.resize(N);
        in_deg.resize(N);
        fill(in_deg.begin(), in_deg.end(), 0);
        fill(node_val.begin(), node_val.end(), 1);
    }

    bool contain_loop(){
        queue<int> q;
        int cnt = 0;
        auto in = in_deg;
        for (int i = 0; i < N; i++){
            if (in[i] == 0){
                cnt++;
                q.push(i);
            }
        }
        while (!q.empty()){
            int t = q.front();
            q.pop();
            for (auto x : adj[t]){
                in[x]--;
                if (in[x] == 0){
                    cnt++;
                    q.push(x);
                }
            }
        }
        return cnt != N;
    }

    void set_val(int v, int val){
        node_val[v] = val;
    }

    void add_edge(int a, int b){
        in_deg[b]++;
        adj[a].push_back(b);
    }

    int dfs(int fa, int u){
        if (visited[u]){
            return 0;
        }
        visited[u] = true;
        if (adj[u].size() > 1){
            return 0;
        }
        ll val = node_val[u];
        if (adj[u].size() != 0){
            val = val * dfs(u, adj[u][0]) % mod;
        }
        return val;
    }

    int calc(){
        if (contain_loop()){
            return 0;
        }
        fill(visited.begin(), visited.end(), false);
        ll ans = 1;
        for (int i = 0; i < N; i++){
            if (in_deg[i] == 0) ans = ans * dfs(-1, i) % mod;
        }
        ans = ans * fact[line_count] % mod;
        return ans;
    }

};

struct Alpha{
    int all; 
    int all_id;
    int mid; 
    int start_with;
    int start_id;
    int end_id;
    int end_with;
};

struct Problem{

    int N;
    vector<string> vec;
    void read(){
        cin >> N;
        vec.resize(N);
        for (int i = 0; i < N; i++){
            string str;
            cin >> str;
            auto ed = unique(str.begin(), str.end());
            str.erase(ed, str.end());
            vec[i] = str;
        }
    }

    Graph g;
    bool alpha(){
        g.init(N);
        Alpha al[26];
        memset(al, 0, sizeof(al));
        for (int i = 0; i < vec.size(); i++){
            auto& s = vec[i];
            int st = s[0] - 'a';
            int ed = s.back() - 'a';
            if (s.size() == 1){
                al[st].all++;
                al[st].all_id = i;
            }else{
                al[st].start_with++;
                al[st].start_id = i;
                al[ed].end_with++;
                al[ed].end_id = i;
                for (int j = 1; j < s.size() - 1; j++){
                    int m = s[j] - 'a';
                    al[m].mid++;
                }
            }
        }

        int head = 0;
        for (int i = 0; i < 26; i++){
            if (al[i].start_with > 1 || al[i].end_with > 1 || al[i].mid > 1){
                return false;
            }
            if (al[i].mid == 1 && (al[i].end_with !=0 || al[i].start_with != 0 || al[i].all != 0)){
                return false;
            }
            if (al[i].end_with == 0 && (al[i].all > 0 || al[i].start_with > 0)) head++;

            if (al[i].all > 0){
                g.set_val(al[i].all_id, fact[al[i].all]);
                if (al[i].end_with > 0){
                    g.add_edge(al[i].end_id, al[i].all_id);
                }
                if (al[i].start_with > 0){
                    g.add_edge(al[i].all_id, al[i].start_id);
                }
            }else{
                if (al[i].end_with > 0 && al[i].start_with > 0){
                    g.add_edge(al[i].end_id, al[i].start_id);
                }
            }
        }
        g.line_count = head;
        return true;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        
        if (alpha()){
            printf("%d\n", g.calc());
        }else{
            printf("0\n");
        }
    }
};

int main(){
    int T;
    cin >> T;
    init();
    for (int ca = 1; ca <= T; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}

