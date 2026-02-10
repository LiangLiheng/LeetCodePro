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
            // Check if remaining subarray has all distinct elements
            unordered_set<int> seen;
            bool allDistinct = true;
            
            for (int i = start; i < nums.size(); i++) {
                if (seen.count(nums[i])) {
                    allDistinct = false;
                    break;
                }
                seen.insert(nums[i]);
            }
            
            if (allDistinct) {
                break;  // All remaining elements are distinct
            }
            
            // Remove first 3 elements (or all remaining if < 3)
            start += min(3, (int)nums.size() - start);
            operations++;
        }
        
        return operations;
    }
};
# @lc code=end