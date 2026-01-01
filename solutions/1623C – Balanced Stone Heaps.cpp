// 1623C – Balanced Stone Heaps.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static bool can_make(const vector<long long>& a, long long target) {
    int n = (int)a.size();
    vector<long long> b = a;

    for (int i = n - 1; i >= 2; --i) {
        if (b[i] < target) return false;

        // You can only redistribute stones originating from heap i (not the received ones),
        // so cap by a[i].
        long long extra = min(a[i], b[i] - target);
        long long give = extra / 3;

        b[i - 1] += give;
        b[i - 2] += 2 * give;
    }
    return (b[0] >= target && b[1] >= target);
}

static void solve_one() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    long long lo = 0, hi = (long long)1e9;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (can_make(a, mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
