// 1472D – Even-Odd Game.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    sort(a.begin(), a.end(), greater<long long>());

    long long alice = 0, bob = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) { // Alice's turn
            if (a[i] % 2 == 0) alice += a[i];
        } else { // Bob's turn
            if (a[i] % 2 == 1) bob += a[i];
        }
    }

    if (alice > bob) cout << "Alice\n";
    else if (bob > alice) cout << "Bob\n";
    else cout << "Tie\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
