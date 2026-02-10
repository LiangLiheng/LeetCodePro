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
        
        map<long long, int> prefixCount;
        prefixCount[0] = 1;
        
        long long prefixSum = 0;
        
        for (int i = 0; i < n; i++) {
            prefixSum += (nums[i] == target) ? 1 : -1;
            
            // Count all prefixes with sum < prefixSum
            auto it = prefixCount.lower_bound(prefixSum);
            for (auto iter = prefixCount.begin(); iter != it; ++iter) {
                count += iter->second;
            }
            
            prefixCount[prefixSum]++;
        }
        
        return count;
    }
};
# @lc code=end