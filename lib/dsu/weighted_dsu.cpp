#include<bits/stdc++.h>
using namespace std;

// https://atcoder.jp/contests/abc087/submissions/57596792

struct weighted_dsu {
    int n;
    vector<int> par;
    vector<int> rank;
    vector<int> siz;
    vector<int64_t> height_from_par;

    weighted_dsu(int _n) {
        n = _n;
        rank.assign(_n, 0);
        height_from_par.resize(_n, 0);
        par.resize(_n);
        siz.resize(_n, 1);
        iota(par.begin(), par.end(), 0);
    }

    int root(int v) {
        if (par[v] == v) {
            return v;
        } else {
            int r = root(par[v]);
            height_from_par[v] += height_from_par[par[v]];
            return par[v] = r;
        }
    }
    int size(int v) {
        return siz[v];
    }

    bool same(int u, int v) {
        return root(u) == root(v);
    }
    // height[u] = height[v] + w
    bool unite(int u, int v, int64_t w) {
        w -= height(u);
        w += height(v);
        u = root(u);
        v = root(v);
        if (u == v) return false;
        if (rank[v] < rank[u]) {
            swap(u, v);
            w = -w;
        }
        if (rank[u] == rank[v]) rank[v]++;
        par[u] = v;
        siz[v] += siz[u];
        height_from_par[u] = w;
        return true;
    }

    int64_t height(int v) {
        root(v);
        return height_from_par[v];
    }
    // return height[u] - height[v]
    int64_t dist(int u, int v) {
        return height(u) - height(v);
    }
};