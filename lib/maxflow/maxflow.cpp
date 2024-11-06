#include<bits/stdc++.h>
using namespace std;

const long long mod = 998244353;
const long long inf = 1e18;
#define dump(x) cerr << "line " << __LINE__ << " " << #x << " : " << x << "\n"

struct ford_fulkerson {

  struct flow_edge {
    int to;
    long long cap;
    int rev;
  };

  int n;
  vector<vector<flow_edge>> g;
  vector<bool> seen;

  ford_fulkerson(int _n): n(_n), g(_n), seen(_n, false) {
  };

  void add_edge(int from, int to, long long cap) {
    g[from].push_back((flow_edge) {to, cap, (int)g[to].size()});
    g[to].push_back((flow_edge){from, 0ll, (int)g[from].size()-1});
  }

  long long dfs(int v, int sink, long long f) {
    if (v == sink) return f;
    seen[v] = true;
    for (auto &e: g[v]) {
      if (seen[e.to]) continue;
      if (e.cap <= 0) continue;
      int d = dfs(e.to, sink, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        g[e.to][e.rev].cap += d;
        return d;
      }
    }
    return 0;
  }

  long long max_flow(int source, int sink) {
    long long flow = 0;
    for (;;) {
      seen.assign(n, false);
      long long f = dfs(source, sink, inf);
      if (f == 0) return flow;
      flow += f;
    }
  }

};

class dinic {
  struct _edge {
    int to;
    long long cap;
    int rev;
  };

  const long long inf_flow = 1e18;

  int n;
  vector<vector<_edge>> g;
  vector<long> level;
  vector<int> itr;

  void bfs(int _source) {
    level.assign(n, -1);
    queue<int> que;
    level[_source] = 0;
    que.emplace(_source);
    while (!que.empty()) {
      int v = que.front(); que.pop();
      for (_edge &e: g[v]) {
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          que.emplace(e.to);
        }
      }
    }
  }

  long long dfs(int v, int _sink, long long f) {
    if (v == _sink) return f;
    for (_edge &e: g[v]) {
      if (e.cap > 0 && level[v] < level[e.to]) {
        long long d = dfs(e.to, _sink, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          g[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

public:
  dinic(int _n): n(_n), g(_n), itr(_n) {
  };

  void add_edge(int from, int to, long long cap) {
    g[from].emplace_back(to, cap, (int)g[to].size());
    g[to].emplace_back(from, 0, (int)g[from].size()-1);
  }

  long long max_flow(int _source, int _sink) {
    long long flow = 0;
    for (;;) {
      bfs(_source);
      if (level[_sink] < 0) return flow;
      itr.assign(n, 0);
      long long f;
      while ((f = dfs(_source, _sink, inf_flow)) > 0) {
        flow += f;
      }
    }
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  /////////////////////////
  int n, m;
  cin >> n >> m;
  dinic d(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    long long c;
    cin >> a >> b >> c;
    a--;b--;
    d.add_edge(a, b, c);
  }
  cout << d.max_flow(0, n-1) << "\n";
}