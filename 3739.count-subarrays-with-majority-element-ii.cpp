#
# @lc app=leetcode id=3739 lang=cpp
#
# [3739] Count Subarrays With Majority Element II
#
# @lc code=start
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        long long count = 0;
        unordered_map<int, int> balanceFreq;
        balanceFreq[0] = 1;
        int balance = 0;
        
        for (int num : nums) {
            balance += (num == target) ? 1 : -1;
            for (auto& [prevBalance, freq] : balanceFreq) {
                if (prevBalance < balance) {
                    count += freq;
                }
            }
            balanceFreq[balance]++;
        }
        
        return count;
    }
};
# @lc code=end