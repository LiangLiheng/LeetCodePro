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
        
        while (start < nums.size()) {
            // Check if remaining elements (from start onwards) are all distinct
            unordered_set<int> seen;
            bool hasDuplicate = false;
            
            for (int i = start; i < nums.size(); i++) {
                if (seen.count(nums[i])) {
                    hasDuplicate = true;
                    break;
                }
                seen.insert(nums[i]);
            }
            
            if (!hasDuplicate) {
                break;  // All remaining elements are distinct
            }
            
            // Perform one operation: remove first 3 elements
            start += 3;
            operations++;
        }
        
        return operations;
    }
};
# @lc code=end