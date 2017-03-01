#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <string.h>
#include <stdio.h>
#include <cmath>
using namespace std;

void useFile(const string &fname)
{
    if(fname == "std") return;
    freopen((fname+".in").c_str(), "r", stdin);
    freopen((fname+".out").c_str(), "w", stdout);
}

const int MAXN = 110;
const int MAXQ = 1010;

typedef double db;

db sq(db x){ return x*x;}

struct Point{
    db x,y;
    Point(db _x=0, db _y=0):x(_x),y(_y){}
    db len2() const{
        return x*x + y*y;
    }
};

Point operator+(const Point& p1, const Point&p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator-(const Point& p1, const Point&p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}

db operator^(const Point& p1, const Point&p2)
{
    return p1.x*p2.x + p1.y*p2.y;
}

db operator*(const Point& p1, const Point&p2)
{
    return p1.x*p2.y - p2.x*p1.y;
}


struct Circle{
    Point o;
    db r;
};

bool InCircle(const Point& p, const Circle& c)
{
    return p.len2() < sq(c.r);
}


db ArcArea(const Circle& c, const Point& p1, const Point& p2)
{
    double len = sqrt((p1-p2).len2()) / 2;
    double _sin = len / c.r;
    double _cos = sqrt(1 - sq(_sin));
    double theta = asin(_sin);
    //cout << "arc " << (theta - _sin*_cos) * sq(c.r) << endl;
    return (theta - _sin*_cos) * sq(c.r);
}

db PolyArea(vector<Point>& ps)
{
    int n = ps.size();
    ps.push_back(ps[0]);
    db area = 0;
    for(int i=0; i<n; i++){
      //  cout << "--  " << ps[i].x << " " << ps[i].y << endl;
        area += ps[i]*ps[i+1];
    }
    //cout << "poly " << area/2 << endl;
    return area / 2;
    ps.pop_back();
}


db getCross(const Circle& c, db x)
{
    return sqrt(sq(c.r) - sq(x));
}

/* p1-pk-pd
 pk|      |
   |      |pj
   p --pj p2
*/
db SqCircleArea(const Point& p, db sz, const Circle& c)
{
    if(!InCircle(p, c)) return 0;
    Point pd = p + Point(sz, sz);
    if(InCircle(pd,c)) return sq(sz);
    Point p1 = p + Point(0, sz);
    Point p2 = p + Point(sz, 0);
    bool b1 = InCircle(p1, c);
    bool b2 = InCircle(p2, c);
    db xk, yk, xj, yj;

    if(b1) xk = getCross(c, p1.y), yk = p1.y;
    else yk = getCross(c, p1.x), xk = p1.x;
    if(b2) yj = getCross(c, p2.x), xj = p2.x;
    else xj = getCross(c, p2.y), yj = p2.y;

    Point pj(xj, yj), pk(xk, yk);

    vector<Point> poly;
    poly.push_back(p);
    if(b2) poly.push_back(p2);
    poly.push_back(pj);
    poly.push_back(pk);
    if(b1) poly.push_back(p1);
    return PolyArea(poly) + ArcArea(c, pj, pk);
}


int main()
{
    useFile("C2");
    int T, N, Q;
    string name;
    cin >> T;
    double f, R, t, r, g;
    const double PI = acos(-1.0);
    for(int ca=1; ca<=T; ca++){
        cin >> f >> R >> t >> r >> g;
        Circle c;
        c.r = R - t - f;
        Point p(r+f, r+f);
        double sz = g - 2*f;
        g = g + r*2;

        double res = 0;
        if(!(sz < 1e-7)){
            for(;p.x < R; p.x += g){
                p.y = r + f;
                for(;p.y < R; p.y += g){
                    res += SqCircleArea(p, sz, c);
                }
            }
            res = res * 4;
        }
        printf("Case #%d: %.8f\n", ca, 1 - (res / (PI*sq(R))) );
    }
    return 0;
}
