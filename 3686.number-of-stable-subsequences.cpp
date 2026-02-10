#
# @lc app=leetcode id=3686 lang=cpp
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        const int MOD = 1000000007;
        int n = nums.size();
        long long sum1[2] = {0, 0};
        long long sum2[2] = {0, 0};
        long long ans = 0;
        for(int i = 0; i < n; ++i) {
            int p = nums[i] % 2;
            int op = 1 - p;
            long long f1 = (1LL + sum1[op] + sum2[op]) % MOD;
            long long f2 = sum1[p] % MOD;
            ans = (ans + f1 + f2) % MOD;
            sum1[p] = (sum1[p] + f1) % MOD;
            sum2[p] = (sum2[p] + f2) % MOD;
        }
        return static_cast<int>(ans);
    }
};
# @lc code=end