#
# @lc app=leetcode id=3686 lang=cpp
#
# [3686] Number of Stable Subsequences
#
# @lc code=start
class Solution {
public:
    int countStableSubsequences(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        
        // States:
        // 0: empty
        // 1: last 1 element is even
        // 2: last 2 consecutive elements are even
        // 3: last 1 element is odd
        // 4: last 2 consecutive elements are odd
        
        vector<long long> dp(5, 0);
        dp[0] = 1; // empty subsequence
        
        for (int num : nums) {
            vector<long long> new_dp(5, 0);
            
            // Option 1: Don't include current element
            for (int i = 0; i < 5; i++) {
                new_dp[i] = dp[i];
            }
            
            int parity = num % 2; // 0 for even, 1 for odd
            
            if (parity == 0) { // even number
                // Transitions when adding an even number
                new_dp[1] = (new_dp[1] + dp[0]) % MOD; // empty -> 1 even
                new_dp[2] = (new_dp[2] + dp[1]) % MOD; // 1 even -> 2 even
                new_dp[1] = (new_dp[1] + dp[3]) % MOD; // 1 odd -> 1 even
                new_dp[1] = (new_dp[1] + dp[4]) % MOD; // 2 odd -> 1 even
            } else { // odd number
                // Transitions when adding an odd number
                new_dp[3] = (new_dp[3] + dp[0]) % MOD; // empty -> 1 odd
                new_dp[4] = (new_dp[4] + dp[3]) % MOD; // 1 odd -> 2 odd
                new_dp[3] = (new_dp[3] + dp[1]) % MOD; // 1 even -> 1 odd
                new_dp[3] = (new_dp[3] + dp[2]) % MOD; // 2 even -> 1 odd
            }
            
            dp = new_dp;
        }
        
        // Sum all non-empty states
        long long result = 0;
        for (int i = 1; i < 5; i++) {
            result = (result + dp[i]) % MOD;
        }
        
        return result;
    }
};
# @lc code=end