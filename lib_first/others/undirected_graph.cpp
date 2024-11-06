#include<bits/stdc++.h>
using namespace std;


// LowLink (Articulation Points & Bridges)
// can use for Tree or Undirected Graph
// verified with
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_3_A/judge/9571408/C++17
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_3_B/judge/9571418/C++17

vector<int> ord, low;
vector<pair<int,int>> bridge;
vector<bool> articulation_point;
int timer = 0;
void _dfs_lowlink(const vector<vector<int>> &g, int v, int p = -1) {
    ord[v] = low[v] = timer++;
    int cnt = 0;
    for (int nv: g[v]) {
        if (nv == p) {
            continue;
        } else if (ord[nv] == 1e9) {
            _dfs_lowlink(g, nv, v);
            low[v] = min(low[v], low[nv]);
            if (ord[v] <= low[nv] && p != -1) articulation_point[v] = true;
            cnt++;
        } else {
            low[v] = min(low[v], ord[nv]);
        }
        if (ord[v] < low[nv]) {
            bridge.emplace_back(min(v, nv), max(v, nv));
        }
    }
    if (p == -1 && cnt > 1) articulation_point[v] = true;
};
void lowlink(vector<vector<int>> const &g) {
    int n = g.size();
    ord.assign(n, 1e9);
    low.assign(n, 1e9);
    articulation_point.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (ord[i] == 1e9) {
            _dfs_lowlink(g, i);
        }
    }
};

// use on weighted-edge Tree
// return diameter and vertexes on diameter
// diameter is verified by https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/GRL_5_A/judge/9571507/C++17
// vertexes are not verified


vector<int> on_diameter;
int _diameter(const vector<vector<pair<int,int>>> &g) {
    int n = g.size();
    int res = -1, id = -1;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    vector<int> dist(n, 1e9);
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [d, v] = q.top();q.pop();
        if (dist[v] <= d) continue;
        dist[v] = d;
        if (res < dist[v]) {
            res = dist[v];
            id = v;
        }
        for (auto [nv, D]: g[v]) {
            if (dist[nv] <= dist[v] + D) continue;
            q.emplace(dist[v] + D, nv);
        }
    }
    // free(&q);
    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    dist.assign(n, 1e9);
    pq.emplace(0, id, -1);
    vector<int> prv(n, -1);
    res = -1;
    while (!pq.empty()) {
        auto [d, v, p] = pq.top();pq.pop();
        if (dist[v] <= d) continue;
        dist[v] = d;
        prv[v] = p;
        if (res < dist[v]) {
            res = dist[v];
            id = v;
        }
        for (auto [nv, D]: g[v]) {
            if (dist[nv] <= dist[v] + D) continue;
            pq.emplace(dist[v] + D, nv, v);
        }
    }
    while (id != -1) {
        on_diameter.emplace_back(id);
        id = prv[id];
    }
    return res;
};