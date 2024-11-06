#include<bits/stdc++.h>
using namespace std;
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using ll = long long;
using pii = pair<ll, ll>;
const int64_t inf = 1e9;
ifstream reader;
ofstream writer;
template <typename T>
bool chmin(T &a, const T& b){if(a > b){a = b;return 1;}return 0;}

static vector<vector<pair<int, int>>> dp(200020, vector<pair<int, int>> (2, {inf, inf}));
vector<int> a(200000);

void solve(int n, int m){
    for (int i = 0; i < n; i++){
        reader >> a[i];
    }
    for (int i = 0; i <= n; i++){
        dp[i][0] = {inf, inf};
        dp[i][1] = {inf, inf};
    }
    auto ride = [&](pair<int, int> p, int t){
        if (p.first == inf) return p;
        if (p.second + t > m){
            p.first++;
            p.second = t;
        } else{
            p.second += t;
        }
        return p;
    };
    dp[0][0] = {0, 0};
    for (int i = 0; i < n; i++){
        chmin(dp[i + 1][0], ride(dp[i][0], a[i]));
        if (i != n - 1) chmin(dp[i + 2][1], ride(ride(dp[i][0], a[i + 1]), a[i]));
        chmin(dp[i + 1][1], ride(dp[i][1], a[i]));
    }
    writer << max(dp[n][0].first + (int)(dp[n][0].second > 0), dp[n][1].first + (int)(dp[n][1].second > 0)) << endl;
}

int main(){
    reader.open("input.txt", ios::in);
    writer.open("output.txt", ios::out);
    // reader >> foo で入力
    // writer << bar で出力
    // QCfium法は使っちゃだめっぽい
    cout << -1 << endl;
    while (1) {
        int n, m;
        reader >> n >> m;
        if (n == 0 && m == 0) return 0;
        solve(n, m);
    }
}