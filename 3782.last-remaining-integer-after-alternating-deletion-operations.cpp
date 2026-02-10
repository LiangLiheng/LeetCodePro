#
# @lc app=leetcode id=3782 lang=cpp
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#
# @lc code=start
class Solution {
public:
    long long lastInteger(long long n) {
        long long head = 1;
        long long step = 1;
        long long count = n;
        bool fromLeft = true;
        
        while (count > 1) {
            // When going from right with even count, head moves forward
            if (!fromLeft && count % 2 == 0) {
                head += step;
            }
            
            // Update for next iteration
            step *= 2;
            count = (count + 1) / 2;  // Ceiling division for remaining count
            fromLeft = !fromLeft;
        }
        
        return head;
    }
};
# @lc code=end