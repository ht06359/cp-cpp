#include <bits/stdc++.h>
using namespace std;


int main() {

  int n, tt;
/////////////////////////////////////////////////////
  vector<int> col(n);
  vector<int> l(tt), r(tt);

  const int M = max(1, int(n/sqrt(tt)));
  int x = 0, y = 0, temp = 0;
  vector<int> id(tt), ans(tt);
  vector<int> even(n, 0);
  
  iota(id.begin(), id.end(), 0);
  sort(id.begin(), id.end(), [&](int i, int j) {
    if (l[i] / M != l[j] / M) return l[i] < l[j];
    if (l[i] / M & 1) return r[j] < r[i];
    return r[i] < r[j];
  });
  auto add = [&] (int i) {
    if (!even[col[i]]++) temp++;
    even[col[i]] = !even[col[i]];
  };
  auto del = [&] (int i) {
    if (even[col[i]]--) temp--;
  };
  for (int i = 0; i < tt; i++) {
    while (x > l[id[i]]) add(--x);
    while (y > r[id[i]]) del(--y);
    while (y < r[id[i]]) add(y++);
    while (x < l[id[i]]) del(x++);
    ans[id[i]] = temp;
  }
/////////////////////////////////////////////////////
}