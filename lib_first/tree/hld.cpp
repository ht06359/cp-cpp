#include<bits/stdc++.h>
using namespace std;

template<typename T, auto op, auto e>
struct segment_tree {
    int n;
    vector<T> dat;

    segment_tree (int _n, T x = e()) {
        n = __lg(_n) + 1;
        dat.assign(1 << (n+1), x);
    };
    segment_tree (const vector<T> &a) {
        n = __lg((int)a.size()) + 1;
        dat.resize(1 << (n+1));
        for (int i = 0; i < (int)a.size(); i++) {
            dat[i + (1 << n)] = a[i];
        }
        _spread();
    };

    void add(int i, T x) {
        i += (1 << n);
        dat[i] += x;
        for (;i > 1;) {
            i >>= 1;
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
    void update(int i, T x) {
        i += (1 << n);
        dat[i] = x;
        for (;i > 1;) {
            i >>= 1;
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
    T get(int i) {
        return dat[i + (1 << n)];
    }
    T prod(int l, int r) {
        T res = e();
        l += 1 << n, r += 1 << n;
        for (;l < r;) {
            if (l & 1) res = op(res, dat[l++]);
            if (r & 1) res = op(res, dat[--r]);
            l >>= 1, r >>= 1;
        }
        return res;
    }
    T prod_all() {
        return dat[1];
    }
private:
    void _spread() {
        for (int i = (1 << n) - 1; i >= 0; i--) {
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
};


// https://atcoder.jp/contests/abc294/submissions/57021935
// MUST USE IT WITH SEGMENT_TREE

template<typename T = typeof(1ll)>
struct heavy_light_decomposition {
    static constexpr T _op(T a, T b) {
        return a + b;
    }
    static constexpr T _e() {
        return 0;
    }

    int n, timer = 0;
    vector<int> siz, in, out, par, leader;
    vector<vector<pair<int, T>>> g;
    segment_tree<T, _op, _e> s_edge, s_weight;

    heavy_light_decomposition(int _n) : n(_n), siz(n, 0),in(n, 0), out(n), 
                par(n, -1), leader(n, 0), g(_n), s_edge(n, _e()), s_weight(n, _e())  {
    }

    void update_edge(int u, int v, T w = 1) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        if (in[u] > in[v]) swap(u, v);
        s_edge.update(in[v], w);
    }
    void update_weight(int v, T w = 0) {
        s_weight.update(in[v], w);
    }
    void build() {
        _dfs_sz();
        _dfs_hld();
        for (int i = (1 << (__lg(n) + 1)) - 1; i >= 0; i--) {
            s_edge.dat[i] = _op(s_edge.dat[i << 1], s_edge.dat[(i << 1) | 1]);
            s_weight.dat[i] = _op(s_weight.dat[i << 1], s_weight.dat[(i << 1) | 1]);
        }
    }
    int lca(int u, int v) {
        for (;; v = par[leader[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (leader[u] == leader[v]) return u;
        }
    }
    T prod_path(int u, int v) {
        T res = _e();
        for (;;res = _op(res, _op(s_edge.prod(in[leader[v]], in[v]+1), s_weight.prod(in[leader[v]],in[v]+1))), v = par[leader[v]]) {
            if (in[u] > in[v]) swap(u, v);
            if (leader[u] == leader[v]) return _op(res, _op(s_edge.prod(in[u]+1, in[v]+1), s_weight.prod(in[u], in[v]+1)));
        }
    }
    T prod_subtree(int i) {
        return _op(s_edge.prod(in[i]+1, out[i]), s_weight.prod(in[i], out[i]));
    }
private:
    void _dfs_sz(int v = 0) {
        siz[v] = 1;
        if ((int)g[v].size() > 1 && g[v][0].first == par[v]) swap(g[v][0], g[v].back());
        for (size_t i = 0; i < g[v].size(); i++) if (g[v][i].first != par[v]) {
            par[g[v][i].first] = v;
            _dfs_sz(g[v][i].first);
            siz[v] += siz[g[v][i].first];
            if (siz[g[v][i].first] > siz[g[v][0].first]) swap(g[v][i], g[v][0]);
        }
    }
    void _dfs_hld(int v = 0) {
        in[v] = timer++;
        for (size_t i = 0; i < g[v].size(); i++) if (g[v][i].first != par[v]) {
            leader[g[v][i].first] = (g[v][i].first == g[v][0].first? leader[v]: g[v][i].first);
            _dfs_hld(g[v][i].first);
        }
        out[v] = timer;
    }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    heavy_light_decomposition hld(n);
    for (int i = 0; i < n - 1; i++) {
        long long w;
        cin >> a[i] >> b[i] >> w;
        a[i]--, b[i]--;
        hld.update_edge(a[i], b[i], w);
    }
    hld.build();
    int tt;
    cin >> tt;
    for (;tt--;) {
        int t, u, v, i;
        long long w;
        cin >> t;
        if (t == 1) {
            cin >> i >> w;
            hld.update_edge(a[i], b[i], w);
        } else {
            cin >> u >> v;
            u--;v--;
            cout << hld.prod_path(u, v) << "\n";
        }
    }
}