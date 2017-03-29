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
#include <string.h>

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

struct Point{
    int x, y;
    Point(int x1 = 0, int y1 = 0) : x(x1), y(y1){ }
    void input(){
        cin >> x >> y;
    }
    Point operator-(const Point &p)const {
        return Point(x-p.x, y-p.y);
    }
};

int sgn(const Point& dir1, const Point& dir2){
    ll t = (dir1.x * (ll)dir2.y) - (dir1.y * (ll)dir2.x);
    return t == 0 ? 0 : ((t > 0) ? 1 : -1);
}

Point to_sort[3000];
int sort_id[3000]; 
int is_down[3000];

bool pcmp(int i, int j){
    int s = sgn(to_sort[i], to_sort[j]);
    return s > 0;
}

struct Problem{
    int N;
    vector<Point> pt;
    void read(){
        cin >> N;
        pt.resize(N);
        for (int i = 0; i < N; i++)
            pt[i].input();
    }

    void center(int c){
        int id = 0;
        Point& f = pt[c];
        int down = 0, up = 0;
        for (int i = 0; i < N; i++){
            if (i != c){
                Point p = pt[i] - f;
                if (p.y < 0 || (p.y == 0 && p.x < 0)){
                    is_down[id] = 1; 
                    p.y = -p.y;
                    p.x = -p.x;
                    down++;
                }else {
                    is_down[id] = 0;
                    up++;
                }
                to_sort[id] = p;
                sort_id[id] = id;
                id++;
            }
        }

        sort(sort_id, sort_id + id, pcmp);

        int cur = sort_id[0];
        int u = 0, d = 0;
        for (int i = 0; i < id; i++){
            int scan_id = sort_id[i];
            if (sgn(to_sort[scan_id], to_sort[cur]) != 0){
                auto &p1 = to_sort[scan_id];
                auto &p2 = to_sort[cur];
                min_cut[c] = min(min_cut[c], min(up - u, down - d));
                up += (d - u);
                down += (u - d);
                cur = scan_id;
                d = u = 0;
            }
            if (is_down[scan_id]) d++;
            else u++;
        }
        min_cut[c] = min(min_cut[c], min(up - u, down - d));
    }

    vector<int> min_cut;
    void solve(int ca){
        printf("Case #%d:\n", ca);
        if (N == 1){
            printf("0\n");
            return;
        }
        min_cut.resize(N);
        fill(min_cut.begin(), min_cut.end(), N);

        for (int i = 0; i < N; i++)
            center(i);
        for (int i = 0; i < N; i++)
            printf("%d\n", min_cut[i]);
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

