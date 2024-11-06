#include<bits/stdc++.h>
using namespace std;

template<typename T = int64_t>
struct fenwick_tree {
    static constexpr T _op(T a, T b) { return a + b; }
    static constexpr T _inv_op(T a, T b) { return a - b; }
    static constexpr T _e() { return (T) 0; }

    int n;
    vector<T> dat;
    fenwick_tree(int _n) : n(_n), dat(_n + 1, _e()) {};

    // add X to dat[id] (0-indexed)
    void add(int id, T x) {
        int i = id + 1;
        while (i <= n) {
            dat[i] = _op(dat[i], x);
            i += i & -i;
        }
    }
    // return sum of [0, id) (0-indexed)
    T sum(int id) {
        int i = id;
        T res = 0;
        while (i > 0) {
            res = _op(res, dat[i]);
            i -= i & -i;
        }
        return res;
    }
    // return sum of [l, r) (0-indexed)
    T sum(int l, int r) {
        assert(0 <= l && l <= n);
        assert(0 <= r && r <= n);
        if (l <= r) return _inv_op(sum(r), sum(l));
        else return _op(sum(r), sum(l, n));
    }
    // return the smallest index which "sum of [0, ??) >= input" is correct  
    // return -1 or n when there's no index needed
    int lower_bound(T x) {
        int res = 0;
        T t = x;
        int k = 1;
        while (k << 1 <= n) k <<= 1;
        for (; k > 0; k >>= 1) {
            if (res + k <= n && dat[res + k] < t) {
                t -= dat[res + k];
                res = _op(res, k);
            }
        }
        return res;
    }
};

/*
// return the smallest index which "sum of [0, ??) > input" is correct  
// return siz+1 when there's no index needed
int upper_bound(T x) {
    int res = 0;
    T t = x;
    for (int k = __lg(siz); k > 0; k >>= 1) {
        if (res + k <= siz && b[res + k] <= t) {
            t -= b[res + k];
            res += k;
        }
    }
    cout << siz << endl;
    return res;
}
// add X to the elements of [l, r)
void imos(int l, int r, T x) {
    this->add(l, x);
    this->add(r, -x);
}
*/

