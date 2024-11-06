#include<bits/stdc++.h>
using namespace std;

// https://atcoder.jp/contests/abc353/submissions/57865877

// https://atcoder.jp/contests/abc268/submissions/58010165

struct trie {
    const static int n = 26;
    const static char base = 'a';

    struct trienode {
        int freq, isend;
        vector<int> next;
        trienode() {
            next.assign(n, -1);
            isend = 0;
            freq = 0;
        }
    };

    vector<int> suffix_link, bfs_order, str;
    vector<trienode> tree;

    trie() {
        tree.emplace_back(trienode());
    }

    int insert(const string &s) {
        int p = 0;
        tree[p].freq++;
        for (int i = 0; i < (int)s.size(); i++) {
            if (tree[p].next[s[i]-base] == -1) {
                tree.emplace_back(trienode());
                tree[p].next[s[i]-base] = tree.size() - 1;
            }
            p = tree[p].next[s[i]-base];
            tree[p].freq++;
        }
        tree[p].isend++;
        str.emplace_back(p);
        return p;
    }

    // return node on which char c is added when you are on node v;
    int next_node(int v, char c) {
        while (v != -1) {
            if (tree[v].next[c-base] != -1) return tree[v].next[c-base];
            v = suffix_link[v];
        }
        return 0;
    }

    //Aho-Corasick algorithm 
    void build_suffix_link() {
        suffix_link.assign((int)tree.size(), -1);
        bfs_order.resize((int)tree.size());
        int begin = 0, end = 0;
        bfs_order[end++] = 0;
        for (;begin < end;) {
            int v = bfs_order[begin++];
            for (int i = 0; i < n; i++) {
                if (tree[v].next[i] == -1) continue;
                bfs_order[end++] = tree[v].next[i];
                int pos = suffix_link[v];
                while (pos != -1 && tree[pos].next[i] == -1) pos = suffix_link[pos];
                suffix_link[tree[v].next[i]] = ((pos == -1) ? 0 : tree[pos].next[i]);
            }
            if (v != 0) tree[v].isend += tree[suffix_link[v]].isend;
        }
    }

    bool check_prefix(const string &s) {
        int p = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (tree[p].next[s[i]-base] == -1) return false;
            p = tree[p].next[s[i]-base];
        }
        return true;
    }

    bool check_string(const string &s) {
        int p = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (tree[p].next[s[i]-base] == -1) return false;
            p = tree[p].next[s[i]-base];
        }
        return tree[p].isend > 0;
    }

    void dfs(int v, long long &cnt) {
        if (v != 0) cnt += 1ll*(tree[v].freq)*(tree[v].freq-1)/2;
        for (int nv: tree[v].next) {
            if (nv != -1) {
                dfs(nv, cnt);
            }
        }
    }
};

/*
    int persistent_insert(int head, const string &s) {
        int old = head;
        tree.emplace_back(trienode());
        int now = tree.size() - 1;
        int new_head = now;
        int i, j;
        for (i = 0; i < (int)s.size(); i++) {
            if (old == -1) {
                tree.emplace_back(trienode());
                tree[now].next[s[i]-base] = tree.size() - 1;
                tree[now].freq++;
                now = tree[now].next[s[i]-base];
            } else {
                for (j = 0; j < n; j++) {
                    tree[now].next[j] = tree[old].next[j];
                }
                tree[now].freq = tree[old].freq;
                tree[now].isend = tree[old].isend;
                tree[now].freq++;
                tree.emplace_back(trienode());
                tree[now].next[s[i]-base] = tree.size()-1;
                old = tree[old].next[s[i]-base];
                now = tree[now].next[s[i]-base];
            }
        }
        tree[now].freq++;
        tree[now].isend = true;
        return new_head;
    }

    bool persistent_check_prefix(int head, const string &s) {
        int p = head;
        for (int i = 0; i < (int)s.size(); i++) {
            if (tree[p].next[s[i]-base] == -1) return false;
            p = tree[p].next[s[i]-base];
        }
        return true;
    }

    bool persistent_check_string(int head, const string &s) {
        int p = head;
        for (int i = 0; i < (int)s.size(); i++) {
            if (tree[p].next[s[i]-base] == -1) return false;
            p = tree[p].next[s[i]-base];
        }
        return tree[p].isend;
    }
    */


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> s(n);
    trie T;
    int nh = 0;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        T.insert(s[i]);
    }
    long long ans = 0;
    T.dfs(0, ans);
    cout << ans << "\n";
    return 0;
}