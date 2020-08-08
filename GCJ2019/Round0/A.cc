#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Problem {
public:
    int T;
    void go() {
        cin >> T;
        for (int ca = 1; ca <= T; ca++) {
            solve(ca);
        }
    }

    string num; 
    void read() {
        cin >> num;
    }

    string a, b;
    
    static string remove_leading_zero(string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '0') {
                return s.substr(i, s.size());
            }
        }
    }

    void solve(int ca) {
        read();
        a = num;
        b = num;
        for (int i = 0; i < num.size(); i++) {
            if (num[i] == '4') {
                a[i] = '1'; b[i] = '3';
            } else {
                a[i] = num[i];
                b[i] = '0';
            }
        }
        b = remove_leading_zero(b);
        cout << "Case #" << ca << ": " << a << " " << b << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

