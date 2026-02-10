#
# @lc app=leetcode id=3562 lang=cpp
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#

# @lc code=start
class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<vector<int>> ch(n + 1);
        for (const auto& h : hierarchy) {
            ch[h[0]].push_back(h[1]);
        }
        const int NEGINF = INT_MIN / 2;
        vector<vector<vector<int>>> memo(n + 1, vector<vector<int>>(2, vector<int>(budget + 1, NEGINF)));
        auto dfs = [&](auto&& self, int u, int pb) -> void {
            int idx = u - 1;
            int cost_full = present[idx];
            int cost = pb ? (cost_full / 2) : cost_full;
            int prof = future[idx] - cost;
            vector<int>& dp = memo[u][pb];
            if (dp[0] != NEGINF) return;
            // no buy u
            vector<int> comb(budget + 1, NEGINF);
            comb[0] = 0;
            for (int v : ch[u]) {
                self(self, v, 0);
                const vector<int>& cdp = memo[v][0];
                vector<int> new_comb(budget + 1, NEGINF);
                for (int s = 0; s <= budget; ++s) {
                    if (comb[s] == NEGINF) continue;
                    for (int t = 0; t <= budget - s; ++t) {
                        if (cdp[t] != NEGINF) {
                            new_comb[s + t] = max(new_comb[s + t], comb[s] + cdp[t]);
                        }
                    }
                }
                comb = std::move(new_comb);
            }
            for (int j = 0; j <= budget; ++j) {
                dp[j] = comb[j];
            }
            // buy u
            vector<int> comby(budget + 1, NEGINF);
            comby[0] = 0;
            for (int v : ch[u]) {
                self(self, v, 1);
                const vector<int>& cdp = memo[v][1];
                vector<int> new_comb(budget + 1, NEGINF);
                for (int s = 0; s <= budget; ++s) {
                    if (comby[s] == NEGINF) continue;
                    for (int t = 0; t <= budget - s; ++t) {
                        if (cdp[t] != NEGINF) {
                            new_comb[s + t] = max(new_comb[s + t], comby[s] + cdp[t]);
                        }
                    }
                }
                comby = std::move(new_comb);
            }
            if (cost <= budget) {
                for (int m = 0; m <= budget - cost; ++m) {
                    if (comby[m] != NEGINF) {
                        int tot = m + cost;
                        dp[tot] = max(dp[tot], prof + comby[m]);
                    }
                }
            }
        };
        dfs(dfs, 1, 0);
        const vector<int>& res = memo[1][0];
        int ans = 0;
        for (int j = 0; j <= budget; ++j) {
            if (res[j] != NEGINF) {
                ans = max(ans, res[j]);
            }
        }
        return ans;
    }
};
# @lc code=end