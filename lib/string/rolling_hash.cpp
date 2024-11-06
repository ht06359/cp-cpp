#include<bits/stdc++.h>
using namespace std;

// https://atcoder.jp/contests/abc141/submissions/57837441
/////////////////////////////////////////

const uint64_t hashmod = 0x1fffffffffffffff;
const uint64_t base = chrono::duration_cast<chrono::microseconds>(chrono::system_clock::now().time_since_epoch()).count() % hashmod;
const uint64_t mdf = uint64_t(1e17) + 1;

template<typename T = string>
struct rolling_hash {
    int n;
    vector<uint64_t> hash, p;

    inline uint64_t mul(uint64_t a, uint64_t b) const {
        uint64_t a31 = a >> 31, b31 = b >> 31;
        a &= 0x7fffffffull; b &= 0x7fffffffull;
        uint64_t x = a * b31 + b * a31;
        uint64_t res = (a31 * b31 << 1) + (x >> 30) + ((x & 0x3fffffffull) << 31) + a * b;
        res = (res >> 61) + (res & hashmod);
        if (res >= hashmod) res -= hashmod;
        return res;
    }

    rolling_hash(const T &a) {
        n = (int)a.size();
        hash.assign(n + 1, 0ull);
        p.assign(n + 1, 0ull);
        p[0] = 1;
        for(int i = 0; i < n; i++) {
            p[i + 1] = mul(p[i], base);
            hash[i + 1] = mul(hash[i], base) + (mdf + (uint64_t)a[i]);
            if(hash[i + 1] >= hashmod) hash[i + 1] -= hashmod;
        }
    }
    
    // get hashing of S[l, r)
    inline uint64_t get(int l, int r) const {
        uint64_t res = hash[r] + hashmod - mul(hash[l], p[r - l]);
        if (res >= hashmod) res -= hashmod;
        return res;
    }

    // return longest common prefixes of a and b
    inline int lcp(const rolling_hash &b, int l1, int r1, int l2, int r2) const {
        int size = min(r1 - l1, r2 - l2);
        int ok = 0, ng = size + 1;
        while(ng - ok > 1) {
            int mid = (ok + ng) / 2;
            if(get(l1, l1 + mid) == b.get(l2, l2 + mid)) ok = mid;
            else ng = mid;
        }
        return ok;
    }

    // return hash1 + hash2 
    inline uint64_t connect(uint64_t hash1, uint64_t hash2, int hash2size) const {
        uint64_t res = mul(hash1, p[hash2size]) + hash2;
        if (res >= hashmod) res -= hashmod;
        return res;
    }
};

/////////////////////////////////////////////////////////////////////////////////////

/*    
    void connect(const string &s){
        int64_t n = hash.size() - 1, m = s.size();
        hash.resize(n + m + 1);
        p.resize(n + m + 1);
        for(int64_t i = n; i < n + m; i++) {
            p[i + 1] = mul(p[i], base);
            hash[i + 1] = mul(hash[i], base) + s[i - n];
            if(hash[i + 1] >= hashmod) hash[i + 1] -= hashmod;
        }
    }

hashmod 2^61 - 1 の RollingHash です  結構強いです
名前の衝突がある場合は namespace で囲うと良いです
hash[i] : s[0, i) のハッシュ結果  hash[i + 1] = s[i] + s[i-1] * p[1] + s[i-2] * p[2] + ...
p[i] : base ** i
get(l, r) : s[l, r) のハッシュ結果  s[r-1] + s[r-2] * p[1] + ... + s[l] * p[r - l + 1]
connect(h1, h2, h2len) : 2つのハッシュ結果からそれらを繋げたときのハッシュ結果を得ます
connect(s) : コンストラクタで渡した文字列に s を繋げたことにします  過去必要になったやつ
LCP(...) : Longest Common Prefix の長さ
*/