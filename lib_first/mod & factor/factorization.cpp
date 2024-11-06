#include<bits/stdc++.h>
using namespace std;

vector<int64_t> f((int)1e7+1, -1);
void calc() {
    f[0] = f[1] = 1;
    for (int i = 2; i <= 1e7; i++) {
        if (f[i] == -1) {
            for (int j = i; j <= 1e7; j+=i) {
                if (f[j] == -1) f[j] = i;
            }
        }
    }
}