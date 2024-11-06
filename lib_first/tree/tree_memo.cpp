#include<bits/stdc++.h>
using namespace std;


int _n;
vector<int> centroid, siz;
void _dfs(const vector<vector<int>> &_g, int _v, int _p = -1) {
    bool iscentroid = true;
    for (int _nv: _g[_v]) if (_nv != _p) {
        _dfs(_g, _nv, _v);
        if (siz[_nv] > _n / 2) iscentroid = false;
        siz[_v] += siz[_nv];
    }
    if (_n - siz[_v] > _n / 2) iscentroid = false;
    if (iscentroid) centroid.emplace_back(_v);
};



// LowLink (Articulation Points & Bridges)
// can use for Tree or Undirected Graph
// verified with
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_3_A/judge/9571408/C++17
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_3_B/judge/9571418/C++17

vector<int> ord, low;
vector<pair<int,int>> bridge;
vector<bool> articulation_point;
int timer = 0;
void _dfs_lowlink(const vector<vector<int>> &_g, int _v, int _p = -1) {
    ord[_v] = low[_v] = timer++;
    int cnt = 0;
    for (int _nv: _g[_v]) {
        if (_nv == _p) {
            continue;
        } else if (ord[_nv] == 1e9) {
            _dfs_lowlink(_g, _nv, _v);
            low[_v] = min(low[_v], low[_nv]);
            if (ord[_v] <= low[_nv] && _p != -1) articulation_point[_v] = true;
            cnt++;
        } else {
            low[_v] = min(low[_v], ord[_nv]);
        }
        if (ord[_v] < low[_nv]) {
            bridge.emplace_back(min(_v, _nv), max(_v, _nv));
        }
    }
    if (_p == -1 && cnt > 1) articulation_point[_v] = true;
};
void lowlink(vector<vector<int>> const &_g) {
    int _n = _g.size();
    ord.assign(_n, 1e9);
    low.assign(_n, 1e9);
    articulation_point.assign(_n, false);
    for (int i = 0; i < _n; i++) {
        if (ord[i] == 1e9) {
            _dfs_lowlink(_g, i);
        }
    }
};

// use on weighted-edge Tree
// return diameter and vertexes on diameter
// diameter is verified by https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_5_A/judge/9571507/C++17
// vertexes are not verified


vector<int> on_diameter;
int _diameter(const vector<vector<pair<int,int>>> &_g) {
    int _n = _g.size();
    int res = -1, id = -1;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    vector<int> dist(_n, 1e9);
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [d, _v] = q.top();q.pop();
        if (dist[_v] <= d) continue;
        dist[_v] = d;
        if (res < dist[_v]) {
            res = dist[_v];
            id = _v;
        }
        for (auto [_nv, D]: _g[_v]) {
            if (dist[_nv] <= dist[_v] + D) continue;
            q.emplace(dist[_v] + D, _nv);
        }
    }
    // free(&q);
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    dist.assign(_n, 1e9);
    pq.emplace(0, id, -1);
    vector<int> prv(_n, -1);
    res = -1;
    while (!pq.empty()) {
        auto [d, _v, _p] = pq.top();pq.pop();
        if (dist[_v] <= d) continue;
        dist[_v] = d;
        prv[_v] = _p;
        if (res < dist[_v]) {
            res = dist[_v];
            id = _v;
        }
        for (auto [_nv, D]: _g[_v]) {
            if (dist[_nv] <= dist[_v] + D) continue;
            pq.emplace(dist[_v] + D, _nv, _v);
        }
    }
    while (id != -1) {
        on_diameter.emplace_back(id);
        id = prv[id];
    }
    return res;
};
