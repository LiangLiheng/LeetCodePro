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
        stack<int> st;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            int cur_steps = 0;
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                cur_steps = max(cur_steps, dp[st.top()] + 1);
                st.pop();
            }
            if (!st.empty()) {
                dp[i] = max(cur_steps, 1);
            }
            ans = max(ans, dp[i]);
            st.push(i);
        }
        return ans;
    }
};
# @lc code=end