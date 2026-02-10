#
# @lc app=leetcode id=3739 lang=cpp
#
# [3739] Count Subarrays With Majority Element II
#
# @lc code=start
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        long long count = 0;
        
        for (int i = 0; i < n; i++) {
            int targetCount = 0;
            for (int j = i; j < n; j++) {
                if (nums[j] == target) {
                    targetCount++;
                }
                int length = j - i + 1;
                // Target is majority if targetCount > length/2
                // Which is equivalent to targetCount * 2 > length
                if (targetCount * 2 > length) {
                    count++;
                }
            }
        }
        
        return count;
    }
};
# @lc code=end