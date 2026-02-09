#
# @lc app=leetcode id=3420 lang=cpp
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#
# @lc code=start
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        long long count = 0;
        
        for (int left = 0; left < n; left++) {
            long long cost = 0;
            long long max_val = nums[left];
            
            for (int right = left; right < n; right++) {
                // Calculate cost to make nums[left...right] non-decreasing
                if (nums[right] < max_val) {
                    cost += max_val - nums[right];
                } else {
                    max_val = nums[right];
                }
                
                if (cost <= k) {
                    count++;
                } else {
                    break;  // No point in extending further from this left
                }
            }
        }
        
        return count;
    }
};
# @lc code=end