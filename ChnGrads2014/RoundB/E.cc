#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
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

char text[100100];

enum State{
    NONE = 0, CMT_B1, CMT_B2, CMT_E1, CMT_E2, CMT_CHG_B2
};

struct StateChange{
    State st[4][3];
    // '/' -> 0
    // '*' -> 1
    // 'other' -> 2
    void init(){
        st[NONE][0] = CMT_B1; 
        st[NONE][1] = NONE; 
        st[NONE][2] = NONE;

        st[CMT_B1][0] = CMT_B1;
        st[CMT_B1][1] = CMT_CHG_B2;
        st[CMT_B1][2] = NONE;

        st[CMT_B2][0] = CMT_B1;
        st[CMT_B2][1] = CMT_E1;
        st[CMT_B2][2] = CMT_B2;

        st[CMT_E1][0] = CMT_E2;
        st[CMT_E1][1] = CMT_E1;
        st[CMT_E1][2] = CMT_B2;
    }

    State next(State cur, char c){
        int d = 2;
        if (c == '*'){
            d = 1;
        }else if (c == '/'){
            d = 0;
        }
        return st[cur][d];
    }
};

struct Problem{

    StateChange st;

    void read(){
        int pos = 0;
        string str;
        while (getline(cin, str)){
            for (auto c : str){
                text[pos++] = c;
            }
            text[pos++] = '\n';
        }
        text[pos++] = 0;
    }

    void solve(int ca){
        printf("Case #%d:\n", ca);
        st.init();
        State cur = NONE;

        int i = 0, j = 0;
        stack<int> comment_start;
        while (text[i]){
            text[j++] = text[i];
            cur = st.next(cur, text[i]); 
            if (cur == CMT_CHG_B2){
                comment_start.push(j - 2);
                cur = CMT_B2;
            }else if(cur == CMT_E2){
                j = comment_start.top(); 
                comment_start.pop();
                cur = NONE;
            }
            if (cur == NONE && !comment_start.empty()){
                cur = CMT_B2;
            }
            i++;
        }
        text[j++] = 0;
        printf("%s\n", text);
    }
};

int main(){
    for (int ca = 1; ca <= 1; ca++){
        Problem p;
        p.read();
        p.solve(ca);
    }
}

