// 1368B - Codeforces Subsequences.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n;
    cin >> n;
    
    vector<ll> cnt(10, 1); // counts for 'c', 'o', 'd', 'e', 'f', 'o', 'r', 'c', 'e', 's'
    ll prod = 1;
    int idx = 0;
    
    while (prod < n) {
        prod /= cnt[idx];
        cnt[idx]++;
        prod *= cnt[idx];
        idx = (idx + 1) % 10;
    }
    
    string s = "codeforces";
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < cnt[i]; ++j) {
            cout << s[i];
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}