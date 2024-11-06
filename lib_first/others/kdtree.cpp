#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct kdtree {
  kdtree *l = nullptr, *r = nullptr;
  int xmin = 1e8, xmax = -1e8, ymin = 1e8, ymax = -1e8, siz = 0;
  kdtree(vector<pair<int,int>>::iterator bgn, vector<pair<int,int>>::iterator nd, bool by_x = true) {
    for (auto p = bgn; p != nd; p++) {
      auto [x, y] = *p;
      xmin = min(xmin, x);xmax = max(xmax, x);
      ymin = min(ymin, y);ymax = max(ymax, y);
    }
    siz = int(nd-bgn);
    if (siz <= 1) return;
    auto cen = bgn + siz / 2;
    if (by_x) {
      nth_element(bgn, cen, nd, [](pair<int,int> a, pair<int,int> b) {
        return a.first < b.first;
      });
    } else {
      nth_element(bgn, cen, nd, [](pair<int,int> a, pair<int,int> b) {
        return a.second < b.second;
      });
    }
    l = new kdtree(bgn, cen, !by_x);
    r = new kdtree(cen, nd, !by_x);
  }
  int count(int x1, int x2, int y1, int y2) const {
    if (x2 < xmin || xmax < x1 || y2 < ymin || ymax < y1) return 0;
    if (x1 <= xmin && xmax <= x2 && y1 <= ymin && ymax <= y2) return siz;
    int count_l = (l != nullptr) ? l->count(x1, x2, y1, y2) : 0;
    int count_r = (r != nullptr) ? r->count(x1, x2, y1, y2) : 0;
    return count_l + count_r;
  }
};