#
# @lc app=leetcode id=3509 lang=cpp
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#
# @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = nums.size();
        
        // dp[{sum, length}] = maximum product for that (sum, length) state
        map<pair<int,int>, int> dp;
        
        for (int i = 0; i < n; i++) {
            map<pair<int,int>, int> new_dp = dp; // Preserve states (skip option)
            
            // Option: Start a new subsequence with nums[i]
            if (nums[i] <= limit) {
                auto key = make_pair(nums[i], 1);
                new_dp[key] = max(new_dp[key], nums[i]);
            }
            
            // Option: Extend existing subsequences
            for (auto& [state, prod] : dp) {
                int curr_sum = state.first;
                int curr_len = state.second;
                
                // Determine sign based on position in subsequence
                int sign = (curr_len % 2 == 0) ? 1 : -1;
                int new_sum = curr_sum + sign * nums[i];
                int new_len = curr_len + 1;
                long long new_prod = (long long)prod * nums[i];
                
                if (new_prod <= limit) {
                    auto key = make_pair(new_sum, new_len);
                    new_dp[key] = max(new_dp[key], (int)new_prod);
                }
            }
            
            dp = new_dp;
        }
        
        // Find maximum product with sum equal to k
        int result = -1;
        for (auto& [state, prod] : dp) {
            if (state.first == k) {
                result = max(result, prod);
            }
        }
        
        return result;
    }
};
# @lc code=end