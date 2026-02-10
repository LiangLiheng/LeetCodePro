#
# @lc app=leetcode id=3575 lang=cpp
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[par[i]].push_back(i);
        }
        const long long MOD = 1000000007LL;
        int MS = 1 << 10;
        vector<vector<long long>> dp(n, vector<long long>(MS, -1LL));
        long long total = 0;
        auto get_mask = [](int val) -> pair<bool, int> {
            string s = to_string(val);
            int freq[10] = {0};
            for (char c : s) {
                int d = c - '0';
                ++freq[d];
                if (freq[d] > 1) return {false, 0};
            }
            int mask = 0;
            for (int d = 0; d < 10; ++d) {
                if (freq[d]) mask |= (1 << d);
            }
            return {true, mask};
        };
        function<void(int)> dfs = [&](int u) {
            auto [can, own_mask] = get_mask(vals[u]);
            long long ownv = vals[u];
            vector<long long> comb(MS, -1LL);
            comb[0] = 0;
            for (int v : adj[u]) {
                dfs(v);
                vector<long long> new_comb(MS, -1LL);
                for (int cm = 0; cm < MS; ++cm) {
                    if (comb[cm] == -1LL) continue;
                    for (int vm = 0; vm < MS; ++vm) {
                        if (dp[v][vm] == -1LL) continue;
                        if ((cm & vm) == 0) {
                            int nm = cm | vm;
                            new_comb[nm] = max(new_comb[nm], comb[cm] + dp[v][vm]);
                        }
                    }
                }
                comb = std::move(new_comb);
            }
            vector<long long>& dpu = dp[u];
            fill(dpu.begin(), dpu.end(), -1LL);
            dpu[0] = 0;
            for (int m = 0; m < MS; ++m) {
                if (comb[m] != -1LL) {
                    dpu[m] = max(dpu[m], comb[m]);
                }
            }
            if (can) {
                for (int cm = 0; cm < MS; ++cm) {
                    if (comb[cm] != -1LL && (cm & own_mask) == 0) {
                        int nm = cm | own_mask;
                        dpu[nm] = max(dpu[nm], comb[cm] + ownv);
                    }
                }
            }
            long long mx = 0;
            for (int m = 0; m < MS; ++m) {
                if (dpu[m] != -1LL) {
                    mx = max(mx, dpu[m]);
                }
            }
            total = (total + mx) % MOD;
        };
        dfs(0);
        return static_cast<int>(total);
    }
};
# @lc code=end