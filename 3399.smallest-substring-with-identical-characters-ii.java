#
# @lc app=leetcode id=3399 lang=java
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution {
    public int minLength(String s, int numOps) {
        int n = s.length();
        if (numOps >= n) return 1;
        if (numOps == 0) {
            int maxBlock = 1, curr = 1;
            for (int i = 1; i < n; ++i) {
                if (s.charAt(i) == s.charAt(i-1)) curr++;
                else curr = 1;
                maxBlock = Math.max(maxBlock, curr);
            }
            return maxBlock;
        }
        int left = 1, right = n;
        while (left < right) {
            int mid = (left + right) / 2;
            if (canAchieve(s, numOps, mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }
    private boolean canAchieve(String s, int numOps, int maxLen) {
        // Try for both '0' and '1' as possible target characters
        return canAchieveForChar(s, numOps, maxLen, '0') || canAchieveForChar(s, numOps, maxLen, '1');
    }
    private boolean canAchieveForChar(String s, int numOps, int maxLen, char target) {
        int n = s.length();
        int flips = 0, left = 0;
        for (int right = 0; right < n; ++right) {
            if (s.charAt(right) != target) flips++;
            if (right - left + 1 > maxLen) {
                if (s.charAt(left) != target) flips--;
                left++;
            }
            if (right - left + 1 == maxLen && flips <= numOps) return true;
        }
        return false;
    }
}
# @lc code=end