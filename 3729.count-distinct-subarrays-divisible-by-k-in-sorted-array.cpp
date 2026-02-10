#
# @lc app=leetcode id=3729 lang=cpp
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#
# @lc code=start
class Solution {
public:
    long long numGoodSubarrays(vector<int>& nums, int k) {
        set<vector<int>> distinctSubarrays;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            long long sum = 0;
            vector<int> current;
            for (int j = i; j < n; j++) {
                sum += nums[j];
                current.push_back(nums[j]);
                if (sum % k == 0) {
                    distinctSubarrays.insert(current);
                }
            }
        }
        
        return distinctSubarrays.size();
    }
};
# @lc code=end