#include<bits/stdc++.h>
using namespace std;

// Euler Tour
////////////////////////////////////////////////////////
// Lowest Common Ancestor
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_5_C/judge/9577938/C++17

/*
int root, timer = 0;
vector<int> in, out;
vector<pair<int,int>> depth;

void init(int _n) {
    depth.resize(2*_n);
    in.resize(_n);
    out.resize(_n);
}
void _dfs_et(const vector<vector<int>> &_g, int v, int p, int d) {
    in[v] = timer;
    depth[timer++] = {d, v};
    for (auto nv :_g[v]) if (nv != p) {
        _dfs_et(_g, nv, v, d+1);
        out[v] = timer;
        depth[timer++] = {d, v};
    }
}
pair<int,int> op(pair<int,int> a, pair<int,int> b) {
    return min(a, b);
};
pair<int,int> e() {
    return {(int)1e9, -1};
};
int lca(int u, int v, segment_tree<pair<int,int>, op, e> &_s) {
    return _s.prod(min(in[u], in[v]), max(in[v], in[u]+1)).second;
}
*/

// init(n);
// _dfs_et(g, 0, -1, 0);
// segment_tree<pair<int,int>, op, e> s(depth);
// cout << lca(a, b, s) << endl;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
}

