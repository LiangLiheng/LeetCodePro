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
        int n = nums.size();
        
        // dp[i][parity][count]
        // i: position in array
        // parity: 0=even, 1=odd, 2=empty
        // count: consecutive same parity count (0, 1, 2)
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(3, vector<long long>(3, 0)));
        
        // Base case: empty subsequence
        dp[0][2][0] = 1;
        
        for (int i = 0; i < n; i++) {
            int parity = nums[i] % 2; // 0 for even, 1 for odd
            
            for (int last_parity = 0; last_parity < 3; last_parity++) {
                for (int count = 0; count < 3; count++) {
                    if (dp[i][last_parity][count] == 0) continue;
                    
                    // Option 1: Don't take nums[i]
                    dp[i + 1][last_parity][count] = (dp[i + 1][last_parity][count] + dp[i][last_parity][count]) % MOD;
                    
                    // Option 2: Take nums[i]
                    if (last_parity == 2) {
                        // Empty subsequence, start with nums[i]
                        dp[i + 1][parity][1] = (dp[i + 1][parity][1] + dp[i][last_parity][count]) % MOD;
                    } else if (last_parity == parity) {
                        // Same parity as last element
                        if (count < 2) {
                            dp[i + 1][parity][count + 1] = (dp[i + 1][parity][count + 1] + dp[i][last_parity][count]) % MOD;
                        }
                        // If count == 2, we can't take this element
                    } else {
                        // Different parity
                        dp[i + 1][parity][1] = (dp[i + 1][parity][1] + dp[i][last_parity][count]) % MOD;
                    }
                }
            }
        }
        
        // Sum all valid subsequences (excluding empty)
        long long result = 0;
        for (int parity = 0; parity < 2; parity++) {
            for (int count = 1; count <= 2; count++) {
                result = (result + dp[n][parity][count]) % MOD;
            }
        }
        
        return result;
    }
};
# @lc code=end