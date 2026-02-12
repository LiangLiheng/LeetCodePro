```java
// @lc app=leetcode id=3398 lang=java
// [3398] Smallest Substring With Identical Characters I
// @lc code=start
class Solution {
    public int minLength(String s, int numOps) {
        int n = s.length();
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(s, numOps, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

    private boolean canAchieve(String s, int numOps, int k) {
        return check(s, numOps, k, '0') || check(s, numOps, k, '1');
    }

    private boolean check(String s, int numOps, int k, char target) {
        int n = s.length();
        int l = 0;
        int windowFlips = 0;
        for (int r = 0; r < n; ++r) {
            if (s.charAt(r) != target) {
                windowFlips++;
            }
            if (r - l + 1 > k) {
                if (s.charAt(l) != target) {
                    windowFlips--;
                }
                l++;
            }
            if (r - l + 1 == k) {
                if (windowFlips <= numOps) {
                    return true;
                }
            }
        }
        return false;
    }
}
// @lc code=end
```