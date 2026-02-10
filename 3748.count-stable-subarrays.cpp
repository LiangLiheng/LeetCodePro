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
        vector<int> maxLen(n);
        
        // Compute maxLen[i]: maximum length of non-decreasing subarray starting at i
        maxLen[n-1] = 1;
        for (int i = n-2; i >= 0; i--) {
            if (nums[i] <= nums[i+1]) {
                maxLen[i] = maxLen[i+1] + 1;
            } else {
                maxLen[i] = 1;
            }
        }
        
        // Process each query
        vector<long long> ans;
        for (auto& query : queries) {
            int l = query[0], r = query[1];
            long long count = 0;
            for (int i = l; i <= r; i++) {
                count += min(maxLen[i], r - i + 1);
            }
            ans.push_back(count);
        }
        
        return ans;
    }
};
# @lc code=end