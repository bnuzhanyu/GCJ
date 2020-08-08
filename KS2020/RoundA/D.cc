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

struct TrieNode {
    TrieNode() {
        depth = 0;
        remain = 0;
    }

    ~TrieNode() {
        for (auto iter = children.begin(); iter != children.end(); iter++) {
            delete iter->second;
        }
    }

    TrieNode(int d) {
        depth = d;
        remain = 0;
    }
    int depth;
    int remain;
    unordered_map<char, TrieNode*> children;
};

void build(TrieNode& father, string& s, int d) {
    if (d == s.size()) {
        father.remain++;
        return;
    }
    auto &ch = father.children;
    char key = s[d];
    if (ch.find(key) == ch.end()) {
        TrieNode* node = new TrieNode(d + 1);
        ch[key] = node;
    }
    TrieNode* node = ch[key];
    build(*node, s, d+1);
}

struct Trie {
    TrieNode root;
    void add(string& s) {
        build(root, s, 0);
    }
};

int dfs(TrieNode& node, int& remain, int k) {
    auto &ch = node.children;
    if (ch.size() == 0) {
        remain = node.remain % k;
        return node.remain / k * node.depth;
    }

    remain = 0;
    int ret = 0;
    for(auto iter = ch.begin(); iter != ch.end(); iter++) {
        int r = 0;
        int sc = dfs(*(iter->second), r, k);
        ret += sc;
        remain += r;
    }
    int f = (node.remain + remain) / k;
    remain = (node.remain + remain) % k;
    return ret + f * node.depth;
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

    int K;
    void read() {
        cin >> N >> K;
    }

    void solve(int ca) {
        read();
        Trie trie;
        for (int i = 0; i < N; i++) {
            string s;
            cin >> s;
            trie.add(s);
        }
        int remain = 0;
        int score = dfs(trie.root, remain, K);
        cout << "Case #" << ca << ": " << score << endl;
    }
};

int main() {
    Problem p;
    p.go();
    return 0;
}

