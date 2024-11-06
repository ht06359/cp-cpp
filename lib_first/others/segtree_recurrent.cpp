#include<bits/stdc++.h>
using namespace std;

// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/DSL_2_A/judge/9577487/C++17
// https://onlinejudge.u-aizu.ac.jp/status/users/ht06359/submissions/1/DSL_2_B/judge/9577500/C++17
// https://judge.yosupo.jp/submission/230175
// https://judge.yosupo.jp/submission/230178

template<typename T, auto op, auto e>
struct segment_tree {
    int n;
    vector<T> dat;
    segment_tree (int _n, T x = e()) {
        n = __lg(_n) + 1;
        dat.assign(1 << (n+1), x);
    };
    segment_tree (const vector<T> &a) {
        n = __lg((int)a.size()) + 1;
        dat.resize(1 << (n+1));
        for (int i = 0; i < (int)a.size(); i++) {
            dat[i + (1 << n)] = a[i];
        }
        _spread();
    };
    void add(int i, T x) {
        i += (1 << n);
        dat[i] += x;
        while (i > 1) {
            i >>= 1;
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
    void update(int i, T x) {
        i += (1 << n);
        dat[i] = x;
        while (i > 1) {
            i >>= 1;
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
    T get(int i) {
        return dat[i + (1 << n)];
    }
    T prod(int l, int r) {
        return _prod(l, r, 1, 0, 1 << n);
    }
    T prod_all() {
        return dat[1];
    }
private:
    T _prod(int l, int r, int id, int _l, int _r) {
        if (_r <= l || r <= _l) return e();
        if (l <= _l && _r <= r) return dat[id];
        return op(_prod(l, r, id << 1, _l, (_l + _r) >> 1), _prod(l, r, (id << 1) | 1, (_l + _r) >> 1, _r));
    }
    void _spread() {
        for (int i = (1 << n) - 1; i >= 0; i--) {
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
};

int64_t op(int64_t a, int64_t b) {
    return min(a, b);
}
int64_t e() {
    return (int64_t) (1ll << 31) - 1;
}