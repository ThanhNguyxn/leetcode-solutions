// 1760F – Quests.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n, d;
    long long c;
    cin >> n >> c >> d;

    vector<long long> a(n);
    for (auto &x : a) cin >> x;
    sort(a.begin(), a.end(), greater<long long>());

    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

    auto can = [&](int k) -> bool {
        // Cycle length = k + 1
        int len = k + 1;
        long long full = d / len;
        int rem = d % len;

        long long sum_cycle = pref[min(n, len)];
        long long sum_rem = pref[min(n, rem)];

        if (sum_rem >= c) return true;
        long long need = c - sum_rem;

        if (sum_cycle == 0) return false;

        // Check: full * sum_cycle >= need without overflow
        // full >= ceil(need / sum_cycle)
        long long required_full = (need + sum_cycle - 1) / sum_cycle;
        return full >= required_full;
    };

    // k = 0 means we take a[0] every day => max possible in the hardest repeat case
    if (!can(0)) {
        cout << "Impossible\n";
        return;
    }

    // If we can reach c without repeating within d days, answer is Infinity
    // That corresponds to k >= d (cycle length >= d+1), total = sum of top min(n,d) once
    if (pref[min(n, d)] >= c) {
        cout << "Infinity\n";
        return;
    }

    // Otherwise, binary search maximum k in [0, d-1]
    int lo = 0, hi = d - 1;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (can(mid)) lo = mid;
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
