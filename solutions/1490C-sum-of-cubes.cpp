// 1490C – Sum of Cubes.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one(const vector<long long>& cubes, const unordered_set<long long>& S) {
    long long x;
    cin >> x;

    for (long long c : cubes) {
        if (c >= x) break;
        if (S.find(x - c) != S.end()) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<long long> cubes;
    cubes.reserve(10000);
    unordered_set<long long> S;
    S.reserve(20000);

    for (long long i = 1; i * i * i <= (long long)1e12; i++) {
        long long c = i * i * i;
        cubes.push_back(c);
        S.insert(c);
    }

    int t;
    cin >> t;
    while (t--) solve_one(cubes, S);
    return 0;
}
