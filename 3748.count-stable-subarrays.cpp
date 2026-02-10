#
# @lc app=leetcode id=3748 lang=cpp
#
# [3748] Count Stable Subarrays
#
# @lc code=start
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> max_reach(n);
        
        // Precompute max_reach for each position
        // max_reach[i] = maximum index j such that nums[i..j] is non-decreasing
        for (int i = n - 1; i >= 0; i--) {
            if (i == n - 1) {
                max_reach[i] = i;
            } else if (nums[i] <= nums[i + 1]) {
                max_reach[i] = max_reach[i + 1];
            } else {
                max_reach[i] = i;
            }
        }
        
        // Process queries
        vector<long long> result;
        for (auto& query : queries) {
            int l = query[0], r = query[1];
            long long count = 0;
            
            // For each starting position in [l, r]
            for (int i = l; i <= r; i++) {
                // Count stable subarrays starting at i
                // They can extend up to min(max_reach[i], r)
                count += min(max_reach[i], r) - i + 1;
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};
# @lc code=end