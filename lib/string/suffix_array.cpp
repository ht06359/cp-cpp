#include<bits/stdc++.h>
using namespace std;

// https://atcoder.jp/contests/abc362/submissions/57921480

// https://atcoder.jp/contests/practice2/submissions/57923167

// https://atcoder.jp/contests/abc362/submissions/57940373


// https://yukicoder.me/submissions/1012640

// return suffix array (size: n+1) beginning with the empty string
template<typename T>
vector<int> suffix_array(const T &s) {
    int t = 1, n = (int) s.size();
    vector<int> tmp(n+1), rank(n+1), sa(n+1);

    auto comp = [&] (int i, int j) -> bool {
        if (rank[i] != rank[j]) {
            return rank[i] < rank[j];
        } else {
            return (i + t <= n ? rank[i + t]: -1) < (j + t <= n ? rank[j + t]: -1);
        }
    };

    for (int i = 0; i <= n; i++) {
        sa[i] = i;
        rank[i] = i < n ? s[i]: -1;
    }
    for (; t <= n; t <<= 1) {
        sort(sa.begin(), sa.end(), comp);
        tmp[sa[0]] = 0;
        for (int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i-1]] + (comp(sa[i-1], sa[i]) ? 1: 0);
        }
        for (int i = 0; i <= n; i++) {
            rank[i] = tmp[i];
        }
    }
    return sa;
}

template<typename T>
vector<int> lcp_array(const T &s, const vector<int> &sa) {
    int n = (int) s.size(), h = 0;
    vector<int> rank(n+1), lcp(n+1, 0);
    for (int i = 0; i <= n; i++) {
        rank[sa[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        int j = sa[rank[i]-1];
        if (h > 0) h--;
        for (;j+h < n && i+h < n; h++) {
           if (s[j+h] != s[i+h]) break;
        }
        lcp[rank[i]-1] = h;
    }
    return lcp;
}


// return the number of t
template<typename T>
int count_string(T &t, const T &s, const vector<int> &sa) {
    int n = (int)s.size();
    int ok1 = -1, ng1 = n+1, ok2 = -1, ng2 = n+1;
    while (ng1 - ok1 > 1) {
        int mid = (ok1 + ng1) / 2;
        int m = min((int)t.size(), n - sa[mid]);
        if (s.substr(sa[mid], m) < t) {
            ok1 = mid;
        } else {
            ng1 = mid;
        }
    }
    t.push_back('~');
    while (ng2 - ok2 > 1) {
        int mid = (ok2 + ng2) / 2;
        int m = min((int)t.size(), n - sa[mid]);
        if (s.substr(sa[mid], m) < t) {
            ok2 = mid;
        } else {
            ng2 = mid;
        }
    }
    t.pop_back();
    return ok2 - ok1;
}

/*
template<typename T, typename S = char>
int count_vec(T &t, const T &s, const vector<int> &sa, S end = '~') {
    int n = (int)s.size();
    int ok1 = 0, ng1 = n, ok2 = 0, ng2 = n+1;
    while (ng1 - ok1 > 1) {
        int mid = (ok1 + ng1) / 2;
        cout << mid << "\n";
        int m = min((int)t.size(), n - sa[mid]);
        bool flag = false;
        for (int i = 0; i < m; i++) { 
            if (s[i + sa[mid]] < t[i]) {
                ok1 = mid; flag = true;
                break;
            } else if (s[i + sa[mid]] > t[i]) {
                ng1 = mid; flag = true;
                break;
            } 
        }
        if (flag == false) {
            if ((int) t.size() <= n - sa[mid]) {
                ng1 = mid;
            } else {
                ok1 = mid;
            }
        }
    }
    t.push_back(end);
    while (ng2 - ok2 > 1) {
        int mid = (ok2 + ng2) / 2;
        int m = min((int)t.size(), n - sa[mid]);
        bool flag = false;
        for (int i = 0; i < m; i++) { 
            if (s[i + sa[mid]] < t[i]) {
                ok2 = mid; flag = true;
                break;
            } else if (s[i + sa[mid]] > t[i]) {
                ng2 = mid; flag = true;
                break;
            } 
        }
        if (flag == false) {
            if ((int) t.size() < n - sa[mid]) {
                ng1 = mid;
            } else {
                ok1 = mid;
            }
        }
    }
    t.pop_back();
    return ng2 - ng1;
}
*/