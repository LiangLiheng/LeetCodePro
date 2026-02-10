#
# @lc app=leetcode id=3748 lang=cpp
#
# [3748] Count Stable Subarrays
#
# @lc code=start
class Solution {
public:
    vector<long long> countStableSubarrays(vector<int>& nums, vector<vector<int>>& queries) {
        vector<long long> result;
        
        for (auto& query : queries) {
            int l = query[0];
            int r = query[1];
            long long count = 0;
            
            int i = l;
            while (i <= r) {
                int j = i;
                // Extend j to find maximal non-decreasing sequence
                while (j < r && nums[j] <= nums[j + 1]) {
                    j++;
                }
                // Count subarrays in this non-decreasing sequence
                long long len = j - i + 1;
                count += len * (len + 1) / 2;
                i = j + 1;
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};
# @lc code=end