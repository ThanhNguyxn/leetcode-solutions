// 1805C – Place for a Selfie.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static bool is_good(long long a, long long b, long long c, long long k) {
    // Need (b - k)^2 < 4*a*c (strict)
    long double diff = (long double)b - (long double)k;
    long double left = diff * diff;
    long double right = 4.0L * (long double)a * (long double)c;
    return left < right;
}

static void solve_one() {
    int n, m;
    cin >> n >> m;

    vector<long long> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end());

    while (m--) {
        long long a, b, c;
        cin >> a >> b >> c;

        if (c <= 0) {
            cout << "NO\n";
            continue;
        }

        auto it = lower_bound(s.begin(), s.end(), b);

        bool ok = false;
        long long chosen = 0;

        if (it != s.end() && is_good(a, b, c, *it)) {
            ok = true;
            chosen = *it;
        } else if (it != s.begin()) {
            --it;
            if (is_good(a, b, c, *it)) {
                ok = true;
                chosen = *it;
            }
        }

        if (!ok) {
            cout << "NO\n";
        } else {
            cout << "YES\n" << chosen << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
