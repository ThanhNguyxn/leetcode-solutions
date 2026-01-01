// 1703F – Yet Another Problem About Pairs Satisfying an Inequality.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> goodIdx; // indices i such that a[i] < i
    goodIdx.reserve(n);

    for (int i = 1; i <= n; i++) {
        if (a[i] < i) goodIdx.push_back(i);
    }

    long long ans = 0;
    for (int j = 1; j <= n; j++) {
        if (a[j] < j) {
            // count i such that i < a[j] and a[i] < i
            int bound = (int)a[j];
            ans += (long long)(lower_bound(goodIdx.begin(), goodIdx.end(), bound) - goodIdx.begin());
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
