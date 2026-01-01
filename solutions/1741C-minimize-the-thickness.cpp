// 1741C – Minimize the Thickness.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    int answer = n;

    // Try each possible first segment sum = prefix[0..i]
    for (int i = 0; i < n; i++) {
        long long target = 0;
        for (int p = 0; p <= i; p++) target += a[p];

        int maxLen = i + 1;
        int pos = i + 1;

        bool ok = true;
        while (pos < n) {
            long long sum = 0;
            int start = pos;
            while (pos < n && sum < target) {
                sum += a[pos];
                pos++;
            }
            if (sum != target) { ok = false; break; }
            maxLen = max(maxLen, pos - start);
        }

        if (ok) answer = min(answer, maxLen);
    }

    cout << answer << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
