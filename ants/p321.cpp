#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
// #include<bits/stdc++.h>
using namespace std;

int n, k, ans;
vector<bool> centroid;
vector<int> subtree_size;

int compute_subtree_size(const vector<vector<pair<int,int>>> &_g, int _v, int _p = -1) {
    int c = 1;
    for (auto [_nv, l]: _g[_v]) {
        if (_nv == _p || centroid[_nv]) continue;
        c += compute_subtree_size(_g, _nv, _v);
    }
    return subtree_size[_v] = c;
}

pair<int,int> search_centroid(const vector<vector<pair<int,int>>> &_g, int t, int _v, int _p = -1) {
    pair<int,int> res = make_pair(n, -1);
    int s = 1, m = 0;
    for (auto [_nv, l]: _g[_v]) {
        if (_nv == _p || centroid[_nv]) continue;
        res = min(res, search_centroid(_g, t, _nv, _v));
        m = max(m, subtree_size[_nv]);
        s += subtree_size[_nv];
    }
    m = max(m, t-s);
    res = min(res, make_pair(m, _v));
    return res;
}

void enumerate_paths(const vector<vector<pair<int,int>>> &g, int v, int p, int d, vector<int> &ds) {
    ds.emplace_back(d);
    for (auto [nv, l]: g[v]) {
        if (nv == p || centroid[nv]) continue;
        enumerate_paths(g, nv, v, d+l, ds);
    }
}

int count_pairs(vector<int> &ds) {
    int res = 0, j = ds.size();
    sort(ds.begin(), ds.end());
    for (int i = 0; i < (int) ds.size(); i++) {
        while (j > 0 && ds[i] + ds[j-1] > k) j--;
        res += j - (j > i ? 1: 0);
    }
    return res / 2;
}

void solve_subproblem(const vector<vector<pair<int,int>>> &g, int v) {
    compute_subtree_size(g, v);
    int s = search_centroid(g, subtree_size[v], v).second;
    centroid[s] = true;
    for (auto [nv, l]: g[s]) {
        if (centroid[nv]) continue;
        solve_subproblem(g, nv);
    }
    vector<int> ds;
    ds.emplace_back(0);
    for (auto [nv, l]: g[s]) {
        if (centroid[nv]) continue;
        vector<int> tds;
        enumerate_paths(g, nv, s, l, tds);
        ans -= count_pairs(tds);
        ds.insert(ds.end(), tds.begin(), tds.end());
    }
    ans += count_pairs(ds);
    centroid[s] = false;
}

void solve() {
    ans = 0;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 0; i < n-1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--;b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    centroid.assign(n, false);
    subtree_size.assign(n, 0);
    solve_subproblem(g, 0);
    printf("%d\n", ans);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (true) {
        cin >> n >> k;
        if (n == 0 && k == 0) break;
        solve();
    }
}