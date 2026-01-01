// 1676F – Longest Strike.cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

static void solve_one() {
    int n, k;
    cin >> n >> k;

    map<long long, int> freq;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        freq[x]++;
    }

    vector<long long> good;
    good.reserve(freq.size());
    for (auto &p : freq) if (p.second >= k) good.push_back(p.first);

    if (good.empty()) {
        cout << -1 << "\n";
        return;
    }

    long long bestL = good[0], bestR = good[0];
    long long curL = good[0], curR = good[0];

    for (int i = 1; i < (int)good.size(); i++) {
        if (good[i] == curR + 1) {
            curR = good[i];
        } else {
            if (curR - curL > bestR - bestL) {
                bestL = curL; bestR = curR;
            }
            curL = curR = good[i];
        }
    }
    if (curR - curL > bestR - bestL) {
        bestL = curL; bestR = curR;
    }

    cout << bestL << " " << bestR << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve_one();
    return 0;
}
