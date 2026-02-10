#
# @lc app=leetcode id=3670 lang=cpp
#
# [3670] Maximum Product of Two Integers With No Common Bits
#
# @lc code=start
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        long long maxProd = 0;
        int n = nums.size();
        
        // Check all pairs
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // Check if they share no common bits
                if ((nums[i] & nums[j]) == 0) {
                    long long prod = (long long)nums[i] * nums[j];
                    maxProd = max(maxProd, prod);
                }
            }
        }
        
        return maxProd;
    }
};
# @lc code=end