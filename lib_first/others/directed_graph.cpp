#include<bits/stdc++.h>
using namespace std;

// SCC(strongly connected components)
// verified by
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_3_C/judge/9571723/C++17

vector<int> ord, low, cc, _s;
vector<vector<int>> group;
vector<bool> in_s;
int timer = 0;
int _num = 0;
void _dfs(const vector<vector<int>> &g, int v, int p = -1) {
    _s.emplace_back(v);
    in_s[v] = true;
    ord[v] = low[v] = timer++;
    for (int nv: g[v]) {
        if (ord[nv] == 1e9) {
            _dfs(g, nv, v);
            low[v] = min(low[v], low[nv]);
        } else if (in_s[nv] == true) {
            low[v] = min(low[v], ord[nv]);
        }
    }
    if (ord[v] == low[v]) {
        group.emplace_back();
        while (true) {
            int _v = _s.back(); 
            _s.pop_back();
            group[_num].emplace_back(_v);
            cc[_v] = _num;
            in_s[_v] = false;
            if (_v == v) break;
        }
        _num++;
    }
};

void scc(vector<vector<int>> const &g) {
    int n = g.size();
    ord.assign(n, 1e9);
    low.assign(n, 1e9);
    cc.assign(n, -1);
    in_s.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (ord[i] == 1e9) {
            _dfs(g, i);
        }
    }
};
