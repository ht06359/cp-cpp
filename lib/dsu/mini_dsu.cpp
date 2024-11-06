#include<bits/stdc++.h>
using namespace std;


struct dsu {
    int n;
    vector<int> par, siz;

    dsu(int _n) {
        n = _n;
        par.resize(_n);
        siz.assign(_n, 0);
        iota(par.begin(), par.end(), 0);
    }

    inline int root(int v) {
        if (par[v] == v) {
            return v;
        } else {
            return par[v] = root(par[v]);
        }
    }

    inline int size(int v) {
        return siz[root(v)];
    }
    
    inline bool same(int u, int v) {
        return root(u) == root(v);
    }

    // parent is u, child is v
    inline bool unite(int u, int v) {
        u = root(u);
        v = root(v);
        if (u != v) {
            if (siz[u] < siz[v]) {
                swap(u, v);
            }
            par[v] = u;
            siz[u] += siz[v];
            return true;
        } else {
            return false;
        }
    }
};