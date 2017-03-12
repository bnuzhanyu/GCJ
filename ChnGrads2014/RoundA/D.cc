#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;

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

int dx[] = {0, -1, 0, 1};
int dy[] = {-1, 0, 1, 0};
char dir[] = "WNES";
struct Problem{

    int N;
    char maze[110][110];
    int sx, sy, ex, ey;
    int cur_dir;
    string path;
    void read(){
        scanf("%d", &N);
        for (int i = 1; i <= N; i++){
            scanf("%s", &maze[i][1]);
        }
        scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
        if (sy == 1) cur_dir = 1;
        else cur_dir = 3;
    }

    bool can_reach(int x, int y){
        return 1 <= x && x <= N && 1 <= y && y <= N && maze[x][y] == '.';
    }

    bool next(int& x, int &y){
        int nxt_dir = cur_dir + 3;
        for (int d = 0; d < 4; d++){
            nxt_dir = nxt_dir % 4;
            if (can_reach(x + dx[nxt_dir], y + dy[nxt_dir])){
                cur_dir = nxt_dir;
                path.push_back(dir[nxt_dir]);
                x += dx[nxt_dir];
                y += dy[nxt_dir];
                return true;
            }
            nxt_dir++;
        }
        return false;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        int count = 0;
        bool flag = false;
        while (count < 10000){
            if (next(sx, sy)){
                count++;
                if (sx == ex && sy == ey){
                    flag = true;
                    break;
                }
            }else{
                break;
            }
        }
        if (flag){
            printf("%lu\n%s\n", path.size(), path.c_str());
        }else{
            printf("Edison ran out of energy.\n");
        }
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

