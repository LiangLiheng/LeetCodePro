#
# @lc app=leetcode id=3434 lang=cpp
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        int total = 0;
        for (int num : nums) {
            if (num == k) total++;
        }
        int ans = total;
        for (int v = 1; v <= 50; v++) {
            int cur = 0;
            int maxs = 0;
            for (int num : nums) {
                int d = 0;
                if (num == v) d++;
                if (num == k) d--;
                cur = std::max(d, cur + d);
                maxs = std::max(maxs, cur);
            }
            ans = std::max(ans, total + maxs);
        }
        return ans;
    }
};
# @lc code=end