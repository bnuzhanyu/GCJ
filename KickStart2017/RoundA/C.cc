#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <cmath>

using namespace std;
struct Problem{
    struct Edge{
        Edge(){
            minX = minY = minZ = 2000000000;
            maxX = maxY = maxZ = -2000000000;
        }

        long long minX, minY, minZ;
        long long maxX, maxY, maxZ;

        long long size(){
            if (minX > maxX){
                return 0;
            }
            auto x = maxX - minX;
            auto y = maxY - minY;
            auto z = maxZ - minZ;
            return max(z, max(x,y));
        }
    };

    struct Box{
        long long X, Y, Z;
        long long R;
        void init(long long _X, long long _Y, long long _Z, long long _R){
            X = _X; Y = _Y; Z = _Z;
            R = _R;
        }
        long long ymax() const{
            return Y + R;
        }
        long long ymin() const{
            return Y;
        }
        long long xmax() const{
            return X + R;
        }
        long long xmin() const{
            return X;
        }
        long long zmax() const{
            return Z + R;
        }
        long long zmin() const{
            return Z;
        }
    };

    struct Ball{
        long long X, Y, Z;
        long long R;
        void input(){
            cin >> X >> Y >> Z >> R;
        }
        void update(Edge& e) const{
            e.minX = min(e.minX, X - R);
            e.minY = min(e.minY, Y - R);
            e.minZ = min(e.minZ, Z - R);
            e.maxX = max(e.maxX, X + R);
            e.maxY = max(e.maxY, Y + R);
            e.maxZ = max(e.maxZ, Z + R);
        }
        bool in(const Box& box){
            return X+R <= box.xmax() && X-R >= box.xmin() 
             && Y+R <= box.ymax() && Y-R >= box.ymin() 
             && Z+R <= box.zmax() && Z-R >= box.zmin();
        }
    };

    int N;
    vector<Ball> balls;
    void read(){
        cin >> N;
        balls.resize(N);
        for (int i = 0; i < N; i++){
            balls[i].input();
        }
    }

    long long sz_to_contain(const vector<Ball>& vec){
        if (vec.size() == 0){
            return 0;
        }
        Edge e;
        for (auto& v : vec){
            v.update(e);
        }
        return e.size();
    }

    bool satisfy(const Box& box, long long R){
        vector<Ball> not_contained;
        for (int i = 0; i < balls.size(); i++){
            if (!balls[i].in(box)){
                not_contained.push_back(balls[i]);
            }
        }
        auto x = sz_to_contain(not_contained);
        return x <= R; 
    }

    bool satisfy(Edge& e, long long R){
        bool flag = false;
        Box box;
        box.init(e.minX, e.minY, e.minZ, R);
        flag = flag || satisfy(box, R); 
        box.init(e.minX, e.minY, e.maxZ-R, R);
        flag = flag || satisfy(box, R); 

        box.init(e.minX, e.maxY-R, e.minZ, R);
        flag = flag || satisfy(box, R); 
        box.init(e.minX, e.maxY-R, e.maxZ-R, R);
        flag = flag || satisfy(box, R); 

        box.init(e.maxX-R, e.minY, e.minZ, R);
        flag = flag || satisfy(box, R); 
        box.init(e.maxX-R, e.minY, e.maxZ-R, R);
        flag = flag || satisfy(box, R); 

        box.init(e.maxX-R, e.maxY-R, e.minZ, R);
        flag = flag || satisfy(box, R); 
        box.init(e.maxX-R, e.maxY-R, e.maxZ-R, R);
        flag = flag || satisfy(box, R); 

        return flag;
    }

    void solve(int ca){
        static long long max_edge = 5000000000LL;
        printf("Case #%d: ", ca);

        Edge e;
        for (auto& v : balls){
            v.update(e);
        }

        long long left = 1, right = e.size() + 1;
        while (left < right){
            long long mid = (left + right) / 2;
            if (satisfy(e, mid)){
                right = mid;
            }else{
                left = mid + 1;
            }
        }
        printf("%lld\n", left);
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

