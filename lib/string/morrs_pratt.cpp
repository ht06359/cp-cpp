#include<bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size(), j = -1;
    vector<int> a(n, -1);
    for (int i = 0; i < n; i++) {
        while ( j >= 0 && s[i] != s[j]) j = a[j];
        j++;
        a[i+1] = j;
    }
}