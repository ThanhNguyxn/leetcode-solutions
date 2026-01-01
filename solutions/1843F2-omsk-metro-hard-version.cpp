// 1843F2 – Omsk Metro (hard version).cpp (C++17)
#include <bits/stdc++.h>
using namespace std;

struct Info {
    int sum = 0;

    int minPref = 0, maxPref = 0;
    int minSuf  = 0, maxSuf  = 0;

    int minSeg  = 0, maxSeg  = 0; // subsegment sums, empty allowed
};

static Info combineInfo(const Info &A, const Info &B) {
    Info R;
    R.sum = A.sum + B.sum;

    R.minPref = min(A.minPref, A.sum + B.minPref);
    R.maxPref = max(A.maxPref, A.sum + B.maxPref);

    R.minSuf = min(B.minSuf, B.sum + A.minSuf);
    R.maxSuf = max(B.maxSuf, B.sum + A.maxSuf);

    R.minSeg = min({A.minSeg, B.minSeg, A.minSuf + B.minPref});
    R.maxSeg = max({A.maxSeg, B.maxSeg, A.maxSuf + B.maxPref});
    return R;
}

static Info reverseInfo(const Info &X) {
    Info R = X;
    swap(R.minPref, R.minSuf);
    swap(R.maxPref, R.maxSuf);
    // minSeg/maxSeg and sum remain valid under reversal
    return R;
}

static Info nodeInfo(int w) {
    Info I;
    I.sum = w;
    I.minPref = I.minSuf = I.minSeg = min(0, w);
    I.maxPref = I.maxSuf = I.maxSeg = max(0, w);
    return I;
}

static void solve_one() {
    int q;
    cin >> q;

    int maxNodes = q + 2;
    const int LOG = 20; // enough for <= 2e5 nodes

    vector<int> depth(maxNodes, 0), w(maxNodes, 0);
    vector<array<int, LOG>> up(maxNodes);
    vector<array<Info, LOG>> seg(maxNodes);

    // Initial node 1 with weight +1
    int nodes = 1;
    w[1] = +1;
    depth[1] = 0;
    for (int j = 0; j < LOG; j++) {
        up[1][j] = 0;
        seg[1][j] = Info(); // empty
    }

    auto lift = [&](int v, int dist) {
        // Returns (ancestor, info of vertices along the path excluding the final ancestor),
        // in upward order starting from v.
        Info acc; // identity (empty allowed)
        for (int j = LOG - 1; j >= 0; j--) {
            if (dist & (1 << j)) {
                acc = combineInfo(acc, seg[v][j]);
                v = up[v][j];
            }
        }
        return pair<int, Info>(v, acc);
    };

    auto lca = [&](int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        a = lift(a, depth[a] - depth[b]).first;
        if (a == b) return a;
        for (int j = LOG - 1; j >= 0; j--) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    };

    auto pathInfo = [&](int u, int v) {
        int L = lca(u, v);

        auto [uu, infoU] = lift(u, depth[u] - depth[L]); // excludes L
        auto [vv, infoV] = lift(v, depth[v] - depth[L]); // excludes L

        Info mid = nodeInfo(w[L]);              // include L exactly once
        Info down = reverseInfo(infoV);         // convert v->L (up) to L->v (down)

        return combineInfo(combineInfo(infoU, mid), down);
    };

    while (q--) {
        char type;
        cin >> type;
        if (type == '+') {
            int parent, x;
            cin >> parent >> x;
            nodes++;
            int v = nodes;

            w[v] = x;
            depth[v] = depth[parent] + 1;
            up[v][0] = parent;
            seg[v][0] = nodeInfo(w[v]); // length 1 vertex segment (the node itself)

            for (int j = 1; j < LOG; j++) {
                int mid = up[v][j - 1];
                up[v][j] = mid ? up[mid][j - 1] : 0;
                seg[v][j] = mid ? combineInfo(seg[v][j - 1], seg[mid][j - 1]) : seg[v][j - 1];
            }
        } else {
            int u, v, k;
            cin >> u >> v >> k;

            Info I = pathInfo(u, v);

            // For +/-1 sequences, all attainable subsegment sums (empty allowed) form an interval.
            bool ok = (I.minSeg <= k && k <= I.maxSeg);
            cout << (ok ? "YES\n" : "NO\n");
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
