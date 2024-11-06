#include<bits/stdc++.h>
using namespace std;

// https://atcoder.jp/contests/abc014/submissions/57017131

// MUST USE IT WITH SEGMENT_TREE

struct euler_tour {
    static constexpr pair<int,int> _op(pair<int,int> a, pair<int,int> b) {
        return min(a, b);
    }
    static constexpr pair<int,int> _e() {
        return {numeric_limits<int>::max(), -1};
    }
    
    int n, c, timer = 0;
    vector<int> in;
    vector<vector<int>> g;
    segment_tree<pair<int, int>, _op, _e> s;

    euler_tour(vector<vector<int>> _g): n((int)_g.size()), c(1 << (__lg(2*n)+1)), in(n), g(_g), s(2*n) {
        _dfs(0, -1, 0);
        for (int i = c - 1; i >= 0; i--) {
            s.dat[i] = _op(s.dat[i << 1], s.dat[(i << 1) | 1]);
        }
    }
    int lca(int u, int v) {
        if (in[u] > in[v]) swap(u, v);
        return s.prod(in[u], in[v]+1).second;
    }
    int dist(int u, int v) {
        return s.dat[c+in[u]].first + s.dat[c+in[v]].first- 2*s.dat[c+in[lca(u, v)]].first;
    }
private:
    void _dfs(int v, int p, int d) {
        in[v] = timer;
        s.dat[c+(timer++)] = {d, v};
        for (auto nv :g[v]) if (nv != p) {
            _dfs(nv, v, d+1);
            s.dat[c+(timer++)] = {d, v};
        }
    }
};
