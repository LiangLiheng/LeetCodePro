#
# @lc app=leetcode id=3782 lang=java
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#

# @lc code=start
class Solution {
    public long lastInteger(long n) {
        return fLeft(n);
    }

    private long fLeft(long n) {
        if (n == 1) {
            return 1;
        }
        return 2 * fRight((n + 1) / 2) - 1;
    }

    private long fRight(long n) {
        if (n == 1) {
            return 1;
        }
        long m = (n + 1) / 2;
        long fl = fLeft(m);
        if (n % 2 == 0) {
            return 2 * fl;
        } else {
            return 2 * fl - 1;
        }
    }
}
# @lc code=end