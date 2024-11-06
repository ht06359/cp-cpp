#include<bits/stdc++.h>
using namespace std;

vector<int> on_diameter(const vector<vector<int>> &g) {
    int n = g.size();
    int d = -1, id = -1;
    queue<int> q;
    vector<int> dist(n, -1);
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int nv: g[v]) {
            if (dist[nv] != -1) continue;
            dist[nv] = dist[v] + 1;
            q.push(nv);
            if (d < dist[nv]) {
                d = dist[nv];
                id = nv;
            }
        }
    }
    dist.assign(n, -1);
    q.push(id);
    d = -1;
    vector<int> prv(n);
    prv[id] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int nv: g[v]) {
            if (dist[nv] != -1) continue;
            dist[nv] = dist[v] + 1;
            prv[nv] = v;
            q.push(nv);
            if (d < dist[nv]) {
                d = dist[nv];
                id = nv;
            }
        }
    }
    vector<int> res;
    while (id != -1) {
        res.emplace_back(id);
        id = prv[id];
    }
    return res;
};