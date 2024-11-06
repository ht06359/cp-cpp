#include<bits/stdc++.h>
using namespace std;

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
        for (;i > 1;) {
            i >>= 1;
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
    void update(int i, T x) {
        i += (1 << n);
        dat[i] = x;
        for (;i > 1;) {
            i >>= 1;
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
    T get(int i) {
        return dat[i + (1 << n)];
    }
    T prod(int l, int r) {
        T res = e();
        l += 1 << n, r += 1 << n;
        for (;l < r;) {
            if (l & 1) res = op(res, dat[l++]);
            if (r & 1) res = op(res, dat[--r]);
            l >>= 1, r >>= 1;
        }
        return res;
    }
    T prod_all() {
        return dat[1];
    }
private:
    void _spread() {
        for (int i = (1 << n) - 1; i >= 0; i--) {
            dat[i] = op(dat[i << 1], dat[(i << 1) | 1]);
        }
    }
};

long long op(long long a, long long b) {
    return min(a, b);
}
long long e() {
    return (long long) (1ll << 31) - 1;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, tt;
    cin >> n >> tt;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    segment_tree<long long, op, e> seg(a);
    for (;tt--;) {
        int a, b;
        cin >> a >> b;
        cout << seg.prod(a, b) << "\n";
    }
}