#
# @lc app=leetcode id=3779 lang=cpp
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#
# @lc code=start
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int operations = 0;
        int start = 0;
        int n = nums.size();
        
        while (start < n) {
            // Check if remaining elements are all distinct
            unordered_set<int> seen;
            bool hasDuplicate = false;
            for (int i = start; i < n; i++) {
                if (seen.count(nums[i])) {
                    hasDuplicate = true;
                    break;
                }
                seen.insert(nums[i]);
            }
            
            if (!hasDuplicate) {
                break;
            }
            
            // Remove first 3 elements (or all remaining if < 3)
            start += 3;
            operations++;
        }
        
        return operations;
    }
};
# @lc code=end