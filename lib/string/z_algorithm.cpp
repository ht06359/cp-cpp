#include<bits/stdc++.h>
using namespace std;

// verified
// https://atcoder.jp/contests/abc141/submissions/57837795
// https://atcoder.jp/contests/arc055/submissions/57842456

template<typename T = string>
vector<int> z_algorithm(const T &s) {
    int k, j = 0, n = (int)s.size();
    vector<int> res(n);
    res[0] = n;
    for (int i = 1; i < n;) {
        while (i + j < n && s[j] == s[i+j]) j++;
        res[i] = j;
        if (j == 0) {i++; continue;}
        k = 1;
        while (i + k < n && k + res[k] < j) res[i+k] = res[k], k++;
        i += k, j -= k;
    }
    return res;
}

// verified
// https://atcoder.jp/contests/arc055/submissions/56442328
// https://atcoder.jp/contests/abc150/submissions/56450826
// https://atcoder.jp/contests/abc135/submissions/56454951

/*
template<typename T = string>
vector<int> z_algorithm(const T &s) {
    int c = 0, n = (int) s.size();
    vector<int> res(n);
    res[0] = 0;
    for (int i = 1; i < n; i++) {
        if (i + res[i-c] < c + res[c]) {
            res[i] = res[i-c];
        } else {
            int j = max(0, c + res[c] - i);
            for (;i + j < n && s[j] == s[i+j];) j++;
            res[i] = j, c = i;
        }
    }
    res[0] = n;
    return res;
}

*/