#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <set>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,n) for(int i=0; i<n; i++)

typedef unsigned long long ull;
typedef long long ll;

void usefile(const string& a){
    if(a!="std" && a!="s"){
        freopen( (a + ".in").c_str(), "r", stdin);
        freopen( (a + ".out").c_str(), "w", stdout);
    }
}

const int MAXN = 1000;
struct TreeNode{
    int l, r;
    string feature;
    double w;
}tree[MAXN];


void skip(const string& str, int& st){
    while(st < str.size() && str[st] == ' ') st++;
}


string parse_feature(const string& str, int& st){
    string ans;
    while(st<str.size() && (isalpha(str[st]) || isdigit(str[st]) || str[st] == '.') ) ans.push_back(str[st++]);
    return ans;
}

double parse_double(const string& str, int& st){
    double ans;
    stringstream ss (parse_feature(str, st));
    ss >> ans;
    return ans;
}

int parse_tree_node(const string& str, int &st, int & id){

    int x = id;
    skip(str, st);
    st++;
    skip(str, st);
    tree[x].w = parse_double(str, st);
    skip(str, st);
    if(str[st] == ')') {
        tree[x].feature = "";
        //cout << "(" << x << ":" << tree[x].w << ")";
        st++;
    }else{
        tree[x].feature = parse_feature(str, st);
        //cout << "(" << x << ": " << tree[x].feature  << " " << tree[x].w ;
        id++;
        tree[x].l = parse_tree_node(str, st, id);
        id++;
        tree[x].r = parse_tree_node(str, st, id);
        //cout << ")" ;
        skip(str, st);
        st++;
    }
    return x;
}

double prob(set<string>& st){
    int id = 0;
    double ret = 1;
    while(1){
        ret *= tree[id].w;
        if(tree[id].feature == "") break;
        if(st.count(tree[id].feature)) id = tree[id].l;
        else id = tree[id].r;
    }
    return ret;
}

int main(){
    usefile("A2");
    int T, A, Q;
    cin >> T;


    for(int ca=1; ca<=T; ca++)
    {
        string str_tree;
        string str;
        cin >> A;
        getline(cin, str);
        for(int i=0; i<A; i++){
            getline(cin, str);
            str_tree.push_back(' ');
            str_tree.append(str);
        }
        int id = 0, st = 0;
        parse_tree_node(str_tree, st, id);

        cin >> Q;
        cout << "Case #" << ca << ":" << endl;
        for(int i=0; i<Q; i++){
            int n;
            cin >> str >> n;
            set<string> st;
            for(int j=0; j<n; j++){
                cin >> str;
                st.insert(str);
            }
            cout << fixed << prob(st) << endl;
        }
    }
}







