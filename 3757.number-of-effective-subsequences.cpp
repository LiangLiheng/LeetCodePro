#
# @lc app=leetcode id=3757 lang=cpp
#
# [3757] Number of Effective Subsequences
#
# @lc code=start
class Solution {
public:
    int countEffective(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        
        // Count frequency of each value
        map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }
        
        // Calculate total OR
        int total_or = 0;
        for (auto& [val, cnt] : freq) {
            total_or |= val;
        }
        
        // Extract unique values and counts
        vector<pair<int, int>> items;
        for (auto& [val, cnt] : freq) {
            items.push_back({val, cnt});
        }
        
        int m = items.size();
        
        // Precompute powers of 2
        int max_cnt = 0;
        for (auto& [val, cnt] : items) {
            max_cnt = max(max_cnt, cnt);
        }
        vector<long long> pow2(max_cnt + 1);
        pow2[0] = 1;
        for (int i = 1; i <= max_cnt; i++) {
            pow2[i] = (pow2[i-1] * 2) % MOD;
        }
        
        // DP: dp[or_value] = number of ways to achieve this OR value
        unordered_map<int, long long> dp;
        dp[0] = 1;
        
        for (int i = 0; i < m; i++) {
            int val = items[i].first;
            int cnt = items[i].second;
            long long keep_ways = (pow2[cnt] - 1 + MOD) % MOD;
            
            unordered_map<int, long long> new_dp;
            for (auto& [or_val, ways] : dp) {
                // Remove all elements of this value
                new_dp[or_val] = (new_dp[or_val] + ways) % MOD;
                // Keep at least one element of this value
                new_dp[or_val | val] = (new_dp[or_val | val] + ways * keep_ways) % MOD;
            }
            dp = new_dp;
        }
        
        // Count effective subsequences (OR < total_or)
        long long result = 0;
        for (auto& [or_val, ways] : dp) {
            if (or_val < total_or) {
                result = (result + ways) % MOD;
            }
        }
        
        return result;
    }
};
# @lc code=end