#include<bits/stdc++.h>
using namespace std;

// verified
// https://atcoder.jp/contests/abc296/submissions/56589427
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_3_C/judge/9571804/C++17
// https://judge.yosupo.jp/submission/229749

struct scc{
    int n;
    vector<bool> seen;
    vector<int> vs, topo_order;
    vector<vector<int>> g, rg, group;

    scc(const vector<vector<int>> &_g) {
        n = (int)_g.size();
        g = _g;
        rg.resize(n + 1);
        seen.assign(n + 1, false);
        topo_order.resize(n + 1);
        for (int v = 0; v < n; v++) {
            for (int nv: _g[v]) {
                rg[nv].push_back(v);
            }
        }
    };

    scc(int _n) {
        n = _n;
        g.resize(n + 1);
        rg.resize(n + 1);
        seen.assign(n + 1, false);
        topo_order.resize(n + 1);
    };
    
    void add_edge(int from, int to) {
        g[from].push_back(to);
        rg[to].push_back(from);
    };

    void dfs(int v) {
        seen[v] = true;
        for (auto nv: g[v]) {
            if (seen[nv] == false) dfs(nv);
        }
        vs.push_back(v);
    };

    void rdfs(int v, int k) {
        seen[v] = true;
        topo_order[v] = k;
        for (auto nv: rg[v]) {
            if (seen[nv] == false) rdfs(nv, k);
        }
        group[k].push_back(v);
    };

    int set() {
        vs.clear();
        for (int v = 0; v < n; v++) {
            if (seen[v] == false) dfs(v);
        }
        seen.assign(n + 1, false);
        int k = 0;
        for (int i = (int) vs.size() - 1; i >= 0; i--) {
            if (seen[vs[i]] == false) {
                group.push_back({});
                rdfs(vs[i], k++);
            }
        }
        return k;
    };
};