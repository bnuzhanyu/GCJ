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
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
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

class Problem {
public:
    
    //ofstream out;
    int T;
    void go() {
        cin >> T >> N;
        //out.open("tmp.txt");
        for (int i = 0; i < T; i++) {
            testCase(i);
        }
    }

    int N;
    string readRobot() {
        string x;
        cin >> x;
        return x;
    }

    string randomWord(string hi, string lo) {
        const string A = "AAAAA";
        const string B = "BBBBB";
        const string C = "CCCCC";
        if(hi != A && lo != A) return A;
        if(hi != B && lo != B) return B;
        return C;
    }

    const int NN = 42;
    void testCase(int i) {
        map<string, map<string, int> > ans;
        string myword = "AEJCC";
        map<string,int> cnt;
        
        //out << "case " << i << endl;
        for (int i = 0; i < NN; i++) {
            cout << myword << endl;
            string robot = readRobot();
            if (ans.find(myword) == ans.end()) {
                ans[myword] = map<string, int>();
            }
            cnt[robot]++;
            auto& mp = ans[myword];
            int cnt = mp[robot];
            mp[robot] = cnt + 1;
            //out << "my:" << myword << " ro:" << robot << endl;
            myword = robot;
        }
        //find highest and lowest
        int ccnt = 0;
        int maxCnt = 0;
        string hi;
        for (auto iter = ans.begin(); iter != ans.end(); iter++) {
            auto& x = iter->first;
            auto& mp = iter->second;
            if (mp.size() == 1 && mp.begin()->second >= maxCnt) {
                hi = x;
                maxCnt = mp.begin()->second;
            }
        }
        //out << "hi:" << hi << " cnt:" << maxCnt << endl;
        //cout << "hi:" << hi << endl;
        
        myword = hi;
        for (int i = NN; i < 100; i++) {
            cout << myword << endl;
            string ro = readRobot();
            //out << "my:" << myword << " ro:" << ro << endl;
            if (ans.find(ro) != ans.end()) {
                myword = ans[ro].begin()->first;
            } else {
                myword = hi;
            }
        }
        cout << myword << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}


