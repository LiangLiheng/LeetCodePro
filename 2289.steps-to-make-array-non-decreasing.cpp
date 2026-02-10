#
# @lc app=leetcode id=2289 lang=cpp
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        stack<int> stk;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int steps = 0;
            while (!stk.empty() && nums[stk.top()] <= nums[i]) {
                steps = max(steps, dp[stk.top()]);
                stk.pop();
            }
            if (!stk.empty()) {
                dp[i] = steps + 1;
                ans = max(ans, dp[i]);
            }
            stk.push(i);
        }
        return ans;
    }
};
# @lc code=end