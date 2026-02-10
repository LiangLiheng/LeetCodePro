#
# @lc app=leetcode id=3721 lang=cpp
#
# [3721] Longest Balanced Subarray II
#
# @lc code=start
class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        int maxLen = 0;
        
        // Try all possible subarrays
        for (int i = 0; i < n; i++) {
            unordered_set<int> evens;
            unordered_set<int> odds;
            
            for (int j = i; j < n; j++) {
                // Add current number to appropriate set
                if (nums[j] % 2 == 0) {
                    evens.insert(nums[j]);
                } else {
                    odds.insert(nums[j]);
                }
                
                // Check if balanced
                if (evens.size() == odds.size()) {
                    maxLen = max(maxLen, j - i + 1);
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end