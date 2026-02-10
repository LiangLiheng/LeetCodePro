#
# @lc app=leetcode id=3779 lang=cpp
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        vector<int> last_pos(100001, -1);
        for(int i = 0; i < n; i++) {
            last_pos[nums[i]] = i;
        }
        int max_prev = -1;
        for(int i = 0; i < n; i++) {
            if(last_pos[nums[i]] > i) {
                max_prev = std::max(max_prev, i);
            }
        }
        if(max_prev == -1) return 0;
        int start_pos = max_prev + 1;
        return (start_pos + 2) / 3;
    }
};
# @lc code=end