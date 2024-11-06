#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct matrix {

    vector<vector<T>> dat;

    matrix(int n, int m) {
        a.resize(n, vector<T> (m));
    }

    int64_t mod_mat = 998244353;

    inline void operator*=(const matrix &a, const matrix &b) {
        assert((int)a[0].size() == (int)b.size());
        vector<vector<T>> res((int)a.size(), vector<T> ((int)b[0].size(), 0));
        for (T i = 0; i < (int)a.size(); i++) {
            for (T j = 0; j < (int)b.size(); j++) {
                for (T k = 0; k < (int)b[0].size(); k++) {
                    res[i][k] = (res[i][k] + a[i][j] * b[j][k]) % mod_mat;
                }
            }
        }
        return res;
    } 

    inline matrix operator*(const matrix &a, const matrix &b) {
        assert((int)a[0].size() == (int)b.size());
        vector<vector<T>> res((int)a.size(), vector<T> ((int)b[0].size(), 0));
        for (T i = 0; i < (int)a.size(); i++) {
            for (T j = 0; j < (int)b.size(); j++) {
                for (T k = 0; k < (int)b[0].size(); k++) {
                    res[i][k] = (res[i][k] + a[i][j] * b[j][k]) % mod_mat;
                }
            }
        }
        return res;
    }

    inline matrix operator+(const matrix &a, const matrix &b) {
        assert((int)a[0].size() == (int)b.size());
        vector<vector<T>> res((int)a.size(), vector<T> ((int)b[0].size(), 0));
        for (T i = 0; i < (int)a.size(); i++) {
            for (T j = 0; j < (int)b.size(); j++) {
                for (T k = 0; k < (int)b[0].size(); k++) {
                    res[i][k] = (res[i][k] + a[i][j] + b[j][k]) % mod_mat;
                }
            }
        }
        return res;
    }

    vector<vector<T>> mat_mul(const vector<vector<T>> &a, const vector<vector<T>> &b) {
        assert((int)a[0].size() == (int)b.size());
        vector<vector<T>> res((int)a.size(), vector<T> ((int)b[0].size(), 0));
        for (T i = 0; i < (int)a.size(); i++) {
            for (T j = 0; j < (int)b.size(); j++) {
                for (T k = 0; k < (int)b[0].size(); k++) {
                    res[i][k] = (res[i][k] + a[i][j] * b[j][k]) % mod_mat;
                }
            }
        }
        return res;
    }

    vector<vector<T>> mat_pow(vector<vector<T>> &a, T p) {
        assert((int)a.size() == (int)a[0].size());
        vector<vector<T>> res((int)a.size(), vector<T> ((int)a.size(), 0));
        for (int i = 0; i < (int)a.size(); i++) {
            res[i][i] = 1;
        }
        for (; p > 0; p >>= 1, a = mat_mul(a, a)) {
            if ((p & 1) == 1) res = mat_mul(res, a);
        }
        return res;
    }
};

/*
int main() {
    ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
}
*/