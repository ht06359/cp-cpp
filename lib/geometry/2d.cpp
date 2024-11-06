#include<bits/stdc++.h>
using namespace std;

const long long mod = 998244353;
#define dump(x) cerr << "line " << __LINE__ << " " << #x << " : " << x << "\n"


struct xy {
  long double x, y;
  xy() {}
  xy(long double _x, long double _y) : x(_x), y(_y) {} 

  const long double eps = 1e-11;

  long double add(long double a, long double b) {
    if (abs(a + b) < eps * (abs(a) + abs(b))) return 0;
    return a + b;
  }

  xy operator+ (xy p) {
    return xy(add(x, p.x), add(y, p.y));
  }
  xy operator- (xy p) {
    return xy(add(x, -p.x), add(y, -p.y));
  }
  xy operator* (long double d) {
    return xy(d * x, d * y);
  }
  xy& operator= (const xy &other) {
    if (this != &other) {
      (*this).x = other.x;
      (*this).y = other.y;
    }
    return *this;
  }
  long double dot(xy p) {
    return add(x * p.x, y * p.y);
  }
  long double det(xy p) {
    return add(x * p.y, -y * p.x);
  }
};

bool on_seg(xy p1, xy p2, xy q) {
  return (p1 - q).det(p2 - q) == 0 && (p1 - q).dot(p2 - q) <= 0;
}

xy intersection(xy p1, xy p2, xy q1, xy q2) {
  return p1 + (p2 - p1) * ((q2 - q1).det(q1 - p1) / (q2 - q1).det(p2 - p1));
}

long double dist(xy p, xy q) {
  return (p - q).dot(p - q);
}

vector<xy> convex_hull(vector<xy> &ps, int n) {
  std::sort(ps.begin(), ps.end(), [&](int i, int j) {
    if (ps[i].x != ps[j].x) return ps[i].x < ps[j].x;
    return ps[i].y < ps[j].y;
  });
  int k = 0;
  vector<xy> qs(n * 2);
  for (int i = 0; i < n; i++) {
    while (k > 1 && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k - 1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  for (int i = n-2, t = k; i >= 0; i--) {
    while (k > t && (qs[k-1] - qs[k-2]).det(ps[i] - qs[k-1]) <= 0) k--;
    qs[k++] = ps[i];
  }
  qs.resize(k - 1);
  return qs;
}


int n;
vector<long double> x(n), y(n), r(n);

bool inside(int i, int j) {
  return hypot(x[i] - x[j], y[i] - y[j]) <= r[j];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<pair<double, int>> events;
  for (int i = 0; i < n; i++) {
    events.emplace_back(x[i] - r[i], i);
    events.emplace_back(x[i] + r[i], i + n);
  }
  sort(events.begin(), events.end());
  set<pair<long double, int>> outers;
  vector<int> res;
  for (int i = 0; i < events.size(); i++) {
    int id = events[i].second % n;
    if (events[i].second < n) {
      set<pair<long double, int>>::iterator it = outers.lower_bound(make_pair(y[id], id));
      if (it != outers.end() && inside(id, it->second)) continue;
      if (it != outers.begin() && inside(id, (--it)->second)) continue;
      res.emplace_back(id);
      outers.insert(make_pair(y[id], id));
    } else {
      outers.erase(make_pair(y[id], id));
    }
  }
  sort(res.begin(), res.end());
  cout << res.size() << "\n";
  for (int i = 0; i < res.size(); i++) {
    cout << res[i] + 1 << (i + 1 == res.size() ? "\n": " ");
  }
}