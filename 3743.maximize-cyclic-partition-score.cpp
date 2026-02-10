#
# @lc app=leetcode id=3743 lang=cpp
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
class Solution {
public:
    long long maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ext(2 * n);
        for (int i = 0; i < n; ++i) {
            ext[i] = nums[i];
            ext[n + i] = nums[i];
        }
        int N = 2 * n;
        // Sparse table for max and min
        int LOG = 0;
        while ((1 << LOG) <= N) ++LOG;
        vector<vector<int>> st_max(LOG, vector<int>(N));
        vector<vector<int>> st_min(LOG, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            st_max[0][i] = ext[i];
            st_min[0][i] = ext[i];
        }
        for (int lv = 1; lv < LOG; ++lv) {
            for (int i = 0; i + (1 << lv) <= N; ++i) {
                st_max[lv][i] = max(st_max[lv - 1][i], st_max[lv - 1][i + (1 << (lv - 1))]);
                st_min[lv][i] = min(st_min[lv - 1][i], st_min[lv - 1][i + (1 << (lv - 1))]);
            }
        }
        auto query_max = [&](int L, int R) -> int {
            int len = R - L;
            int lv = 31 - __builtin_clz(len);
            return max(st_max[lv][L], st_max[lv][R - (1 << lv)]);
        };
        auto query_min = [&](int L, int R) -> int {
            int len = R - L;
            int lv = 31 - __builtin_clz(len);
            return min(st_min[lv][L], st_min[lv][R - (1 << lv)]);
        };
        int maxk = min(k, n);
        vector<long long> prev_dp(N + 1, LLONG_MIN / 2);
        prev_dp[0] = 0;
        long long ans = 0;
        for (int j = 1; j <= maxk; ++j) {
            vector<long long> curr_dp(N + 1, LLONG_MIN / 2);
            for (int i = j; i <= N; ++i) {
                for (int l = j - 1; l < i; ++l) {
                    long long rg = (long long)query_max(l, i) - query_min(l, i);
                    if (prev_dp[l] != LLONG_MIN / 2) {
                        curr_dp[i] = max(curr_dp[i], prev_dp[l] + rg);
                    }
                }
            }
            prev_dp = curr_dp;
            for (int i = n; i < 2 * n; ++i) {
                ans = max(ans, prev_dp[i]);
            }
        }
        return ans;
    }
};
# @lc code=end