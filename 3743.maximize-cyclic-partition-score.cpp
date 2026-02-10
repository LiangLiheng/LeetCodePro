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
        long long maxScore = 0;
        
        // Try all starting positions to handle cyclic nature
        for (int start = 0; start < n; start++) {
            // Create rotated array
            vector<int> rotated(n);
            for (int i = 0; i < n; i++) {
                rotated[i] = nums[(start + i) % n];
            }
            
            // Precompute ranges for all subarrays [i, j]
            vector<vector<long long>> range(n, vector<long long>(n, 0));
            for (int i = 0; i < n; i++) {
                int minVal = rotated[i], maxVal = rotated[i];
                for (int j = i; j < n; j++) {
                    minVal = min(minVal, rotated[j]);
                    maxVal = max(maxVal, rotated[j]);
                    range[i][j] = maxVal - minVal;
                }
            }
            
            // dp[i][j] = max score partitioning first i+1 elements into exactly j parts
            vector<vector<long long>> dp(n, vector<long long>(k + 1, -1));
            
            // Base case: 1 partition
            for (int i = 0; i < n; i++) {
                dp[i][1] = range[0][i];
            }
            
            // Fill DP table
            for (int i = 1; i < n; i++) {
                for (int j = 2; j <= min(i + 1, k); j++) {
                    // Try all split points
                    for (int p = j - 2; p < i; p++) {
                        if (dp[p][j - 1] != -1) {
                            dp[i][j] = max(dp[i][j], dp[p][j - 1] + range[p + 1][i]);
                        }
                    }
                }
            }
            
            // Check all possible number of partitions (at most k)
            for (int j = 1; j <= k; j++) {
                if (dp[n - 1][j] != -1) {
                    maxScore = max(maxScore, dp[n - 1][j]);
                }
            }
        }
        
        return maxScore;
    }
};
# @lc code=end