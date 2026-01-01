// 1791G1 – Teleporters (Easy Version).cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n;
    long long c;
    cin >> n >> c;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    vector<long long> cost(n);
    for (int i = 0; i < n; i++) {
        // Start at 0 each time, walk to i+1 costs (i+1), then use teleporter costs a[i]
        cost[i] = a[i] + (i + 1);
    }

    sort(cost.begin(), cost.end());

    int used = 0;
    for (long long x : cost) {
        if (c < x) break;
        c -= x;
        used++;
    }
    cout << used << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
