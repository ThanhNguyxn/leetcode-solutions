#include <bits/stdc++.h>
using namespace std;

static const int MOD = 998244353;

static inline int addmod(int a, int b){
    a += b;
    if(a >= MOD) a -= MOD;
    if(a < 0) a += MOD;
    return a;
}
static inline int mulmod(long long a, long long b){
    return int((a * b) % MOD);
}
static int modpow(int a, int e){
    long long r = 1, x = a;
    while(e){
        if(e & 1) r = r * x % MOD;
        x = x * x % MOD;
        e >>= 1;
    }
    return int(r);
}

struct DP {
    // Stores base array + lazy affine:
    // real_F(d) = dp[idx(d)] * ml + ad
    vector<int> dp;
    int ml = 1; // multiplier
    int ad = 0; // add-to-all

    // reversed indexing with saturation for big d
    inline int idx(int d) const {
        return max(0, (int)dp.size() - d - 1);
    }
    inline int get(int d) const {
        int x = dp[idx(d)];
        return addmod(mulmod(x, ml), ad);
    }
    inline int& ref(int d){
        return dp[idx(d)];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        vector<vector<int>> g(n);
        for(int i = 1; i < n; i++){
            int p; cin >> p; --p;
            g[p].push_back(i);
        }

        // factorials
        vector<int> fact(n + 1, 1);
        for(int i = 1; i <= n; i++) fact[i] = mulmod(fact[i-1], i);

        // postorder (iterative)
        vector<int> order;
        order.reserve(n);
        {
            vector<int> st;
            st.push_back(0);
            while(!st.empty()){
                int v = st.back(); st.pop_back();
                order.push_back(v);
                for(int u : g[v]) st.push_back(u);
            }
        }
        reverse(order.begin(), order.end());

        vector<DP> dp(n);

        for(int v : order){
            if(g[v].empty()){
                dp[v].dp = {1};
                dp[v].ml = 1;
                dp[v].ad = 0;
                continue;
            }

            int m = (int)g[v].size();

            // For each child u: shift child's DP to be relative to v
            // by appending value so that get(0) becomes 0.
            vector<int> safe(m);
            int best_u = -1;
            int best_pos = -1;

            for(int i = 0; i < m; i++){
                int u = g[v][i];

                int inv_ml = modpow(dp[u].ml, MOD - 2);
                int extra = mulmod(inv_ml, (MOD - dp[u].ad) % MOD); // (-ad)/ml
                dp[u].dp.push_back(extra);

                safe[i] = dp[u].get(k - 1);

                if(best_u == -1 || dp[u].dp.size() > dp[best_u].dp.size()){
                    best_u = u;
                    best_pos = i;
                }
            }

            // prefix/suffix products of safe
            vector<int> pref(m + 1, 1), suf(m + 1, 1);
            for(int i = 0; i < m; i++) pref[i+1] = mulmod(pref[i], safe[i]);
            for(int i = m - 1; i >= 0; i--) suf[i] = mulmod(suf[i+1], safe[i]);

            // take best child's dp as base (small-to-large)
            dp[v] = std::move(dp[best_u]);

            // scale base with factor when best child is last:
            // cur = (m-1)! * product_{j != best} safe[j]
            int base_cur = mulmod(fact[m - 1], mulmod(pref[best_pos], suf[best_pos + 1]));
            if(base_cur == 0){
                // reset to zero poly of enough length
                int mx = 1;
                for(int u : g[v]) mx = max(mx, (int)dp[u].dp.size());
                dp[v].dp.assign(mx, 0);
                dp[v].ml = 1;
                dp[v].ad = 0;
            } else {
                dp[v].ml = mulmod(dp[v].ml, base_cur);
                dp[v].ad = mulmod(dp[v].ad, base_cur);
            }

            int inv_base_ml = modpow(dp[v].ml, MOD - 2);

            // merge every other child as "last child"
            for(int i = 0; i < m; i++){
                int u = g[v][i];
                if(u == best_u) continue;

                int cur = mulmod(fact[m - 1], mulmod(pref[i], suf[i + 1])); // (m-1)! * prod_{j!=i} safe[j]
                int tot = mulmod(cur, dp[u].get(n)); // add-to-all part

                dp[v].ad = addmod(dp[v].ad, tot);

                // only need iterate over dp[u] size
                for(int j = 0; j < (int)dp[u].dp.size(); j++){
                    dp[v].ref(j) = addmod(dp[v].ref(j), -mulmod(inv_base_ml, tot));
                    dp[v].ref(j) = addmod(dp[v].ref(j), mulmod(mulmod(cur, dp[u].get(j)), inv_base_ml));
                }
            }
        }

        cout << dp[0].get(n) << "\n";
    }
    return 0;
}
