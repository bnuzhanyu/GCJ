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
int dx[] = {0, -1, 0, 1 };
int dy[] = {1, 0, -1, 0 };
struct Problem{

    int N, M;
    int maze[110][110];
    int sx, sy, ex, ey;
    int dist[110][110];
    int value[110][110];
    bool in_q[110][110];
    void read(){
        cin >> N >> M;
        cin >> sx >> sy >> ex >> ey;
        for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> maze[i][j];
            dist[i][j] = N*M;
            value[i][j] = 0;
            in_q[i][j] = false;
        }
        }
    }

    bool valid(int x, int y){
        return 0 <= x && x < N && 0 <= y && y < M && maze[x][y] != -1;
    }

    void solve(int ca){
        printf("Case #%d: ", ca);
        queue<pair<int, int> > q;
        dist[sx][sy] = 0;
        value[sx][sy] = maze[sx][sy];
        in_q[sx][sy] = true;
        q.push(make_pair(sx, sy));
        while (!q.empty()){
            auto cur_pos = q.front(); q.pop();
            int x = cur_pos.first, y = cur_pos.second;
            for (int d = 0; d < 4; d++){
                int nx = x + dx[d], ny = y + dy[d];
                if (valid(nx, ny)){
                    if (dist[nx][ny] >= dist[x][y] + 1){
                        dist[nx][ny] = dist[x][y] + 1;
                        value[nx][ny] = max(value[nx][ny], value[x][y] + maze[nx][ny]);
                        if (!in_q[nx][ny]){
                            q.push(make_pair(nx, ny));
                            in_q[nx][ny] = true;
                        }
                    }
                }
            }
        }
        if (dist[ex][ey] == N*M){
            printf("Mission Impossible.\n");
        }else{
            printf("%d\n", value[ex][ey]);
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

