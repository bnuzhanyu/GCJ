#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,n) for(int i=0; i<n; i++)

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}

template<typename T>
void print(const vector<T>& vec){
    FOR(i, vec.size()){
        cout << vec[i] << ((i==vec.size()-1)?'\n':' ');
    }
}

template<typename T>
void print(T vec[], int n){
    FOR(i, n){
        cout << vec[i] << ((i==n-1)?'\n':' ');
    }
}

template<typename T>
int input(T vec[]){
    int n;
    cin >> n;
    FOR(i,n) cin >> vec[i];
    return n;
}

template<typename T>
int input(vector<T>& vec){
    int n;
    cin >> n;
    vec.clear(); vec.resize(n);
    FOR(i,n) cin >> vec[i];
    return n;
}


/****--------------题目部分-------------****/

int queries[110];

const int MAXN = 1000010;

int num_at_pos[MAXN];
int pos_of_num[MAXN];

struct NODE{
    int l, r, cnt;
}node[MAXN*3];

int idx[MAXN];
void build(int i, int l, int r)
{
    node[i].l = l, node[i].r = r;
    if(l == r){
        idx[l] = i;
        node[i].cnt = 1;
        return;
    }
    int mid = (l+r)/2;
    build(i*2, l, mid);
    build(i*2+1, mid+1, r);
    node[i].cnt = node[i*2].cnt + node[i*2+1].cnt;
}

void remove_at(int i)
{
    int id = idx[i];
    while(id){
        node[id].cnt--;
        id>>=1;
    }
}

int query(int i, int l, int r)
{
    if(node[i].l == l && node[i].r == r) return node[i].cnt;
    int mid = (node[i].l + node[i].r) / 2;
    if(r <= mid) return query(i*2, l, r);
    else if(l > mid) return query(i*2+1, l, r);
    else return query(i*2, l, mid) + query(i*2+1, mid+1, r);
}

int next_pos(int i, int v, int n) //start_from i
{
    int q = query(1, i, n-1);
    if(q < v) {
        i = 0, v -= q;
    }

    int id = idx[i];
    int actual_cnt = node[id].cnt;
    while(actual_cnt < v){
        if(!(id & 1)) { //left child
            actual_cnt = actual_cnt + node[id|1].cnt;
        }
        id >>= 1;
    }
    v += (node[id].cnt - actual_cnt);

    while(1){
        if(node[id].l == node[id].r){
            if(v!=1 || node[id].cnt != 1) { cout << "never happen" << endl;}
            return node[id].l;
        }
        id *= 2;
        if(node[id].cnt < v){
            v -= node[id].cnt;
            id++;
        }
    }
    cout << "never return -1" << endl;
    return -1;
}

int main(){
    usefile("C2");
    int T, K;
    cin >> T;

    for(int ca=1; ca<=T; ca++)
    {
        cin >> K;
        int N = input(queries);
        build(1, 0, K-1);

        int cur_pos = 0;
        for(int i=0; i<K; i++){
            cur_pos = next_pos(cur_pos, i%(K-i) + 1, K); //剩余K-i个，count i+1次，所以是count i次的下一个
            pos_of_num[i] = cur_pos;
            remove_at(cur_pos);
        }

        for(int i=0; i<K; i++){
            num_at_pos[pos_of_num[i]] = i;
        }

        cout << "Case #" << ca << ":";
        for(int i=0; i<N; i++){
            cout << " " << num_at_pos[queries[i]-1] + 1;
        }
        cout << endl;
    }
}
