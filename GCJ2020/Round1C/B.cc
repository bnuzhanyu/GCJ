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
using namespace std;

struct LETTER {
    char x;
    int cnt;
    LETTER(char _x, int _c) {
        x = _x;
        cnt = _c;
    }
    bool operator<(const LETTER& le) {
        return cnt > le.cnt;
    }
};

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    int U;

    void solve(int ca) {
        cin >> U;
        map<char, int> mp;
        set<char> st;
        for (int i = 0; i < 10000; i++) {
            long long q; cin >> q;
            string r; cin >> r;
            for (char c : r) {
                st.insert(c);
            }
            mp[r[0]]++;
        }

        vector<LETTER> letters;
        for (auto iter = mp.begin(); iter != mp.end(); iter++) {
            char x = iter->first;
            int y = iter->second;
            st.erase(x);
            letters.push_back(LETTER(x, y));
        }

        char zero = *(st.begin());
        std::sort(letters.begin(), letters.end());

        cout << "Case #" << ca << ": ";
        cout << zero;
        for (auto& l : letters) {
            cout << l.x;
        }
        cout << endl;
    }
};

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);
    Problem p;
    p.go();
    return 0;
}


