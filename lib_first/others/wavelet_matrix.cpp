#include<bits/stdc++.h>
using namespace std;

#define dump(x) cerr << "line " << __LINE__ << " " << #x << " : " << x << "\n"
/*
#include <boost/dynamic_bitset.hpp>
boost::dynamic_bitset<> bit();
*/

// const uint32_t B = 262144u; // 131072u, 262144u, 524288u?
const uint32_t B = 1u << 18; // 131072u, 262144u, 524288u

struct easy_bit_vector {
    easy_bit_vector(int _n) : n(_n), sum(n+1, 0), cnt0(n+1, -1), cnt1(n+1, -1){};

    void set(int i, bool f = 1) {
        bit[i] = f;
    }
    void build() {
        int c = 0, d = 0;
        for (int i = 0; i < n; i++) {
            if (bit[i] == 1) {
                c++;
                cnt1[c] = i;
            } else {
                d++;
                cnt0[d] = i;
            }
            sum[i+1] = c;
        }
        initialized = true;
    }
    int access(int i) {
        assert(initialized == true);
        return bit[i];
    }
    // sum of [0, i)
    int rank(int i, bool f = 1) {
        assert(initialized == true);
        return (f ? sum[i]: i - sum[i]);
    }
    // return counts of f in [0, i) (e.g. first bit is cnt1[1])
    int select(int i, bool f = 1) {
        assert(initialized == true);
        return (f ? cnt1[i]: cnt0[i]);
    }
    int size() {
        return n;
    }
    inline bool operator[](const int k) const {
        return bit[k];
    }

private:
    int n;
    bool initialized = false;
    bitset<B> bit;
    vector<uint32_t> sum, cnt0, cnt1;
};

template<typename T = int>
struct wavelet_matrix {
    int n;
    T Max;
    vector<easy_bit_vector> bit_vector;
    vector<int> mid, id;
    // mid[i]: idx separating Left and Right at the level of "i" (first idx of Right)
    // id[i]: first idx of 
    int max_log;

    wavelet_matrix(vector<T> &a) {
        n = (int) a.size();
        max_log = 0;
        Max = *max_element(a.begin(), a.end());
        while ((1ll << max_log) <= Max) max_log++;
        bit_vector.resize(max_log, easy_bit_vector(n));
        mid.resize(max_log);
        build(a, Max);
    }

    void build(vector<T> &a, T Max) {
        vector<int> cur = a;
        for (int lg = max_log-1; lg >= 0; lg--) {
            vector<T> left, right;
            for (int i = 0; i < n; i++) {
                bool b = (cur[i] >> lg) & 1;
                bit_vector[lg].set(i, b);
                if (b == 0) left.emplace_back(cur[i]);
                else right.emplace_back(cur[i]);
            }
            mid[lg] = (int) left.size();
            cur = left;
            cur.insert(cur.end(), right.begin(), right.end());
            bit_vector[lg].build();
        }
    }

    // return how many times val appears in [l, r) (l, r are 0-indexed)
    int rank(T val, int l, int r) {
        if (val > Max) return -1;
        for (int lg = max_log-1; lg >= 0; lg--) {
            bool bit = (val >> lg) & 1;
            l = bit_vector[lg].rank(l, bit);
            r = bit_vector[lg].rank(r, bit);
            if (bit == 0) {
                if (l == r) return 0;
            } else {
                l += mid[lg];
                r += mid[lg];
            }
        }
        return r - l;
    }
    // return val of original vec[i]
    T access(int i) {
        T res = 0;
        for (int lg = max_log-1; lg >= 0; lg--) {
            bool bit = bit_vector[lg][i];
            if (bit) {
                res |= (T(1) << lg);
                i = bit_vector[lg].rank(i) + mid[lg];
            } else {
                i = bit_vector[lg].rank(i, 0);
            }
        }
        return res;
    }
    // return (0-indexed) index of the Kth val in original vector
    int select(T val, int K) {
        if (val > Max) return -1;
        int l = 0, r = n;
        for (int lg = max_log-1; lg >= 0; lg--) {
            bool bit = (val >> lg) & 1;
            l = bit_vector[lg].rank(l, bit);
            r = bit_vector[lg].rank(r, bit);
            if (bit == 0) {
                if (l == r) return -1;
            } else {
                l += mid[lg];
                r += mid[lg];
            }
        }
        l += K;
        if (r <= l) return -1;
        for (int lg = 0; lg < max_log; lg++) {
            bool bit = (val >> lg) & 1;
            if (bit) {
                l = bit_vector[lg].select(l - mid[lg]+1, bit);
            } else {
                l = bit_vector[lg].select(l+1, bit);
            }
        }
        return l;
    }
    // return the index of the ith element in [l, r)
    T quantile(int l, int r, int i) {
        if (r - l <= i) return -1;
        T res = 0;
        for (int lg = max_log-1; lg >= 0; lg--) {
            int zero_count = bit_vector[lg].rank(r, 0) - bit_vector[lg].rank(l, 0);
            if (i < zero_count) {
                l = bit_vector[lg].rank(l, 0);
                r = bit_vector[lg].rank(r, 0);
            } else {
                res |= T(1) << lg;
                i -= zero_count;
                l = bit_vector[lg].rank(l) + mid[lg];
                r = bit_vector[lg].rank(r) + mid[lg];
            }
        }
        return res;
    }

private: 
};
////////////////////////////////////////////
/*
    // T[s, e]中で出現回数が多い順にその頻度とともにk個返す
    vector<pair<int, int>> topk(int s, int e, int k) const {
        vector<pair<int, int>> result;
        map<int, int> freq;

        for (int i = s; i < e; ++i) {
            int val = access(i);
            freq[val]++;
        }

        vector<pair<int, int>> freq_vec(freq.begin(), freq.end());
        sort(freq_vec.begin(), freq_vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        });

        for (int i = 0; i < min(k, (int)freq_vec.size()); ++i) {
            result.push_back(freq_vec[i]);
        }
        return result;
    }

    // T[s, e]の合計を返す
    long long sum(int s, int e) const {
        long long total = 0;
        for (int i = s; i < e; ++i) {
            total += access(i);
        }
        return total;
    }

    // T[s, e]中に出現するx <= c < yを満たす値の合計出現数を返す
    int range_freq(int s, int e, int x, int y) const {
        return rank(y - 1, e) - rank(x, s);
    }

    // T[s, e]中に出現するx <= c < yを満たす値を頻度とともに列挙する
    vector<pair<int, int>> range_list(int s, int e, int x, int y) const {
        vector<pair<int, int>> result;
        map<int, int> freq;

        for (int i = s; i < e; ++i) {
            int val = access(i);
            if (x <= val && val < y) {
                freq[val]++;
            }
        }

        for (const auto& [val, count] : freq) {
            result.push_back({val, count});
        }
        return result;
    }

    // T[s, e]中に出現する値を大きい順にその頻度とともにk個返す
    vector<pair<int, int>> range_maxk(int s, int e, int k) const {
        return topk(s, e, k);
    }

    // T[s, e]中に出現する値を小さい順にその頻度とともにk個返す
    vector<pair<int, int>> range_mink(int s, int e, int k) const {
        vector<pair<int, int>> result = topk(s, e, k);
        sort(result.begin(), result.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first;
        });
        return result;
    }

    // T[s, e]中でx <= c < yを満たす最大のcを返す
    int prev_value(int s, int e, int x, int y) const {
        int max_val = -1;
        for (int i = s; i < e; ++i) {
            int val = access(i);
            if (x <= val && val < y) {
                max_val = max(max_val, val);
            }
        }
        return max_val;
    }

    // T[s, e]中でx <= c < yを満たす最小のcを返す
    int next_value(int s, int e, int x, int y) const {
        int min_val = INT_MAX;
        for (int i = s; i < e; ++i) {
            int val = access(i);
            if (x <= val && val < y) {
                min_val = min(min_val, val);
            }
        }
        return (min_val == INT_MAX) ? -1 : min_val;
    }

    // intersect 関数
    vector<pair<int, int>> intersect(int s1, int e1, int s2, int e2) const {
        vector<pair<int, int>> result;
        intersect_recursive(0, 0, n, s1, e1, s2, e2, 0, sigma, result);
        return result;
    }

    // 再帰的に intersect を計算する関数
    void intersect_recursive(int lg, int l, int r, int s1, int e1, int s2, int e2, int val_l, int val_r, vector<pair<int, int>>& result) const {
        if (val_l + 1 == val_r) {
            // 基底ケース: この値の範囲に一つの要素しかない場合
            int freq1 = e1 - s1;
            int freq2 = e2 - s2;
            if (freq1 > 0 && freq2 > 0) {
                // 共通している場合、結果に追加
                result.push_back({val_l, min(freq1, freq2)});
            }
            return;
        }

        // 現在のレベルで、左側と右側に分かれる要素の範囲
        int m = (val_l + val_r) / 2;

        // 現在のレベルでの `0` と `1` の分布を確認
        int s1_left = bit_vector[lg]._rank(s1, 0); // s1から始まる左側の `0` の個数
        int e1_left = bit_vector[lg]._rank(e1, 0); // e1までの左側の `0` の個数
        int s1_right = s1 - s1_left; // 右側の `1` の個数
        int e1_right = e1 - e1_left;

        int s2_left = bit_vector[lg]._rank(s2, 0); // s2から始まる左側の `0` の個数
        int e2_left = bit_vector[lg]._rank(e2, 0); // e2までの左側の `0` の個数
        int s2_right = s2 - s2_left; // 右側の `1` の個数
        int e2_right = e2 - e2_left;

        // 左側の範囲に対する再帰
        intersect_recursive(lg + 1, l, mid[lg], s1_left, e1_left, s2_left, e2_left, val_l, m, result);

        // 右側の範囲に対する再帰
        intersect_recursive(lg + 1, mid[lg], r, s1_right, e1_right, s2_right, e2_right, m, val_r, result);
    }

*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    easy_bit_vector bit(200);
    vector<int> a = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
    wavelet_matrix wm(a);
    for (int i = 0; i < 6; i++) cout << i << " " << wm.quantile(1, 6, i) << "\n";
}
