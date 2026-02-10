//
// @lc app=leetcode id=2289 lang=cpp
//
// [2289] Steps to Make Array Non-decreasing
//
// @lc code=start
class Solution {
public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        stack<pair<int, int>> st; // (index, steps)
        int maxSteps = 0;
        
        for (int i = 0; i < n; i++) {
            int steps = 0;
            // Pop all elements that are <= current element
            while (!st.empty() && nums[st.top().first] <= nums[i]) {
                steps = max(steps, st.top().second);
                st.pop();
            }
            
            // If stack is not empty, current element will be removed
            if (!st.empty()) {
                steps++;
                maxSteps = max(maxSteps, steps);
            }
            
            st.push({i, steps});
        }
        
        return maxSteps;
    }
};
// @lc code=end