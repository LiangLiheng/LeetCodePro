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
            long long max_val = nums[left];
            long long operations = 0;
            
            for (int right = left; right < n; right++) {
                if (nums[right] < max_val) {
                    operations += max_val - nums[right];
                } else {
                    max_val = nums[right];
                }
                
                if (operations <= k) {
                    count++;
                } else {
                    break;
                }
            }
        }
        
        return count;
    }
};
# @lc code=end