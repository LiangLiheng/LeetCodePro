#
# @lc app=leetcode id=3782 lang=cpp
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#
# @lc code=start
class Solution {
public:
    long long lastInteger(long long n) {
        long long first = 1;
        long long step = 1;
        long long remaining = n;
        bool left = true;
        
        while (remaining > 1) {
            if (!left && remaining % 2 == 0) {
                first += step;
            }
            
            step *= 2;
            remaining = (remaining + 1) / 2;
            left = !left;
        }
        
        return first;
    }
};
# @lc code=end