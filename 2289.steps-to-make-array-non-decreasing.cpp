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
        stack<pair<int, int>> st; // (value, steps_to_remove)
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            int steps = 0;
            // Pop all elements that are <= current element
            while (!st.empty() && st.top().first <= nums[i]) {
                steps = max(steps, st.top().second);
                st.pop();
            }
            
            // If stack not empty, current element will be removed
            if (!st.empty()) {
                steps = steps + 1;
            } else {
                steps = 0;
            }
            
            result = max(result, steps);
            st.push({nums[i], steps});
        }
        
        return result;
    }
};
// @lc code=end