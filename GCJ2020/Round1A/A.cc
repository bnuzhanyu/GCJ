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

struct COMB {
    string first;
    string mid;
    string end;
    void output() {
        //cout << "++" << first << "_" << mid << "_" << end << "++" << endl;
    }
};

COMB make(string x) {
    COMB comb;
    int t1 = x.find_first_of('*');
    int t2 = x.find_last_of('*');
    comb.first = x.substr(0, t1);
    comb.end = x.substr(t2 + 1, x.size());
    comb.mid = x.substr(t1 + 1, t2 - t1);
    return comb;
}

static bool endsWith(const std::string& str, const std::string& suffix)
{
    return suffix.size() == 0 || (str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix));
}

static bool startsWith(const std::string& str, const std::string& prefix)
{
    return prefix.size() == 0 || (str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix));
}


class Problem {
public:
    int T;
    int N;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    vector<COMB> data;
    void read() {
        cin >> N;
        data.clear();
        for (int i = 0; i < N; i++) {
            string t;
            cin >> t;
            data.push_back(make(t));
            data.back().output();
        }
    }

    
    bool find(string& res, vector<string>& v, int type) {
        int max_len = 0;
        string max_str;
        for (int i = 0; i < v.size(); i++) {
            if (v[i].size() > max_len) {
                max_len = v[i].size();
                max_str = v[i];
            }
        }
        for (int i = 0; i < v.size(); i++) {
            if (type == 0 && !startsWith(max_str, v[i])) {
                //cout << "start with " << max_str << " + " << v[i] << " +error" << endl;
                return false;
            }
            if (type == 1 && !endsWith(max_str, v[i])) {
                //cout << "end with " << max_str << " + " << v[i] << " +error" << endl;
                return false;
            }
        }
        res = max_str;
        return true;
    }

    string makeMid(vector<string>&m) {
        string res;
        for (int i = 0; i < m.size(); i++) {
            for (int j = 0; j < m[i].size(); j++) {
                if (m[i][j] != '*') {
                    res.push_back(m[i][j]);
                }
            }
        }
        return res;
    }

    void judge(string& res, vector<COMB>& combs) {
        vector<string> fs;
        vector<string> eds;
        vector<string> mids;
        for (int i = 0; i < N; i++) {
            fs.push_back(combs[i].first);
            eds.push_back(combs[i].end);
            mids.push_back(combs[i].mid);
        }
        string first, ends;
        bool ok1 = find(first, fs, 0);
        bool ok2 = find(ends, eds, 1);
        if (ok1 && ok2) {
            res = first + makeMid(mids) + ends;
        } else {
            res = "*";
        }
        
    }
    void solve(int ca) {
        read();
        cout << "Case #" << ca << ": ";
        string res;
        judge(res, data);
        cout << res << endl;

    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

