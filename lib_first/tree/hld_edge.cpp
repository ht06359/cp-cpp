#include<bits/stdc++.h>
using namespace std;

// https://atcoder.jp/contests/abc294/submissions/57021935
// https://atcoder.jp/contests/abc235/submissions/57426386
// MUST USE IT WITH SEGMENT_TREE

template<typename T = long long>
struct heavy_light_decomposition_edge {
    static constexpr T _op(T a, T b) {
        return a + b;
    }
    static constexpr T _e() {
        return 0;
    }

    int n, timer = 0;
    vector<int> siz, in, out, par, leader;
    vector<vector<pair<int, T>>> g;
    segment_tree<T, _op, _e> s_edge;

    heavy_light_decomposition_edge(const vector<vector<pair<int,T>>> _g)
    : n((int)_g.size()), siz(n, 0), in(n, 0), out(n), par(n, -1), leader(n, 0), g(_g), s_edge(n) {
        _dfs_sz_edge();
        _dfs_hld_edge();
        for (int i = (1 << (__lg(n) + 1)) - 1; i >= 0; i--) {
            s_edge.dat[i] = _op(s_edge.dat[i << 1], s_edge.dat[(i << 1) | 1]);
        }
    }
    int lca(int u, int v) {
        for (;; v = par[leader[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (leader[u] == leader[v]) return u;
        }
    }
    void update(int u, int v, T w) {
        if (in[u] > in[v]) swap(u, v);
        s_edge.update(in[v], w);
    }
    T prod_path(int u, int v) {
        T res = _e();
        for (;;res = _op(res, s_edge.prod(in[leader[v]], in[v]+1)), v = par[leader[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (leader[u] == leader[v]) return _op(res, s_edge.prod(in[u]+1, in[v]+1));
        }
    }
    T prod_subtree(int i) {
        return s_edge.prod(in[i]+1, out[i]);
    }
private:
    void _dfs_sz_edge(int v = 0) {
        siz[v] = 1;
        if ((int)g[v].size() > 1 && g[v][0].first == par[v]) swap(g[v][0], g[v].back());
        for (size_t i = 0; i < g[v].size(); i++) if (g[v][i].first != par[v]) {
            par[g[v][i].first] = v;
            _dfs_sz_edge(g[v][i].first);
            siz[v] += siz[g[v][i].first];
            if (siz[g[v][i].first] > siz[g[v][0].first]) swap(g[v][i], g[v][0]);
        }
    }
    void _dfs_hld_edge(int v = 0) {
        in[v] = timer++;
        for (size_t i = 0; i < g[v].size(); i++) if (g[v][i].first != par[v]) {
            leader[g[v][i].first] = (g[v][i].first == g[v][0].first? leader[v]: g[v][i].first);
            _dfs_hld_edge(g[v][i].first);
            s_edge.dat[(1 << (__lg(n) + 1)) + in[g[v][i].first]] = g[v][i].second;
        }
        out[v] = timer;
    }
};


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// the in[vertexes] in heavy path are in [in[v], in[leader[v]] 
// the in[vertexes] in subtree are in [in[v], out[v])

//   val \ id      |  0  1  2  3  4  5  6  7  8  9 10 11 12
//    in[id]       |  0  9 10 11 12  7  8  1  2  5  6  3  4 
//    out[id]      | 13 13 12 12 13  9  9  7  7  7  7  5  5 
//   leader[id]    |  0  1  1  1  4  5  5  0  0  9  9  0  0 

//   val \ id      |  0  1  2  3  4  5  6  7  8  9 10 11 12
// in[leader[id]]  |  0  9  9  9 12  7  7  0  0  5  5  0  0 
//    in[id]       |  0  9 10 11 12  7  8  1  2  5  6  3  4 

//     in[id]      |  0  1  2  3  4  5  6  7  8  9 10 11 12 
//     out[id]     | 13  7  7  5  5  7  7  9  9 13 12 12 13 
//    leader[id]   |  0  0  0  0  0  9  9  5  5  1  1  1  4 
//  in[leader[id]] |  0  0  0  0  0  5  5  7  7  9  9  9 12 

//  for monoid
//     in[id]      |  0  1  2  3  4  5  6  7  8  9 10 11 12
//      edge       |  e  7  8 11 12  9 10  5  6  1  2  3  4
// edges in subtree [in[v]+1, out[v])
// path from u to v(in[u] < in[v]) [in[u]+1, in[v]+1)

//     in[id]      |  0  1  2  3  4  5  6  7  8  9 10 11 12
//     vertex      |  0  7  8 11 12  9 10  5  6  1  2  3  4
// vertexes in subtree [in[v],out[v])

//                      0(0)
//                    / | \\
//                   /  |  \\
//                  /   |   \\
//                 1(9)  5(7) 7(1)
//               // \   ||    \\
//              //   \  ||     \\
//             //    |  ||      8(2)
//             2(10) 4(12)6(8) / \\
//             ||             /   \\
//             ||            /     \\
//             3(11)        9(5)    11(3)
//                          ||      ||
//                          10(6)   12(4)

/*
template<typename T>
struct heavy_light_decomposition {
    static constexpr pair<int,int> _op(pair<int,int> a, pair<int,int> b) {
        return min(a, b);
    }
    static constexpr pair<int,int> _e() {
        return {numeric_limits<int>::max(), -1};
    }
    int n;
    vector<int> siz, in, out, inv, par, leader;
    vector<vector<int>> g;
    segment_tree<T, _op, _e> s;

    heavy_light_decomposition(const vector<vector<int>> &_g)
    : n((int)_g.size()), siz(n, 0), in(n, 0), out(n), 
    inv(n), par(n, -1), leader(n, 0), g(_g), s(n) {
        _dfs_sz();
        _dfs_hld();
    }
    void set_wtov(const vector<T> &w) {
        for (int i = 0; i < n; i++) {
            s.dat[in[i]] = w[i];
        }
        s._spread();
    }
    T dist(int u, int v) {
        T res = 0;
    }
    void update(const segtree<T, op, e> &_s, int i, int j, T x, bool edge = true) {
        if(edge) _s.update(i, x);
        else _s.update((in[i] < in[j]? j: i), x);
    }
    void add(int i, T x, bool edge = true) {
        _s.add(i, x);
    }
    T prod(int u, int v, bool edge = true) {
        T res = e();
        for (;;) {
            if (in[u] < in[v]) swap(u, v);
            if (in[leader[u]] == in[leader[v]]) return op(res, _s.prod(in[v]+edge, in[u]+1));
            if (leader[u] != u) {
                res = op(res, _s.prod(in[leader[u]], in[u]+1));
            } else {
                res = op(res, _s.get(in[u]));
                u = par[u];
            }
        }
    }
    T prod_subtree(int i, bool edge = true) {
        return _s.prod(in[i]+edge, out[i]);
    }
// the in[vertexes] in heavy path are in [in[v], in[leader[v]] 
// the in[vertexes] in subtree are in [in[v], out[v])
};

*/