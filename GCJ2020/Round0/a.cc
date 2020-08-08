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
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Problem {
public:
    int T;
    int N;
    int mat[100][100];
    int trace;

    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    bool repeat(vector<int> arr) {
        bool ex[100] = { false };
        for (int x : arr) {
            if (ex[x-1]) return true;
            ex[x-1] = true;
        }
        return false;
    }

    void read() {
        trace = 0;
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> mat[i][j];
                if (i == j) {
                    trace += mat[i][j];
                }
            }
        }
    }

    void solve(int ca) {
        
        read();
        int repeat_col = 0;
        int repeat_row = 0;
        for (int i = 0; i < N; i++) {
            vector<int> row;
            vector<int> col;
            for (int j = 0; j < N; j++) {
                row.push_back(mat[i][j]);
                col.push_back(mat[j][i]);
            }
            if (repeat(row)) repeat_row++;
            if (repeat(col)) repeat_col++;
        }
        cout << "Case #" << ca << ": " << trace << " " << repeat_row << " " << repeat_col << "\n";
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

