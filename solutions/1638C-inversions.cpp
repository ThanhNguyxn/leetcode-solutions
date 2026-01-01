// 1638C – Inversions.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    int components = 0;
    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, p[i]);
        if (mx == i) components++;
    }
    cout << components << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
