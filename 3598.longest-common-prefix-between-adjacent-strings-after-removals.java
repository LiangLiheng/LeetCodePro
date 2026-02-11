#
# @lc app=leetcode id=3598 lang=java
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

# @lc code=start
class Solution {
    private static int getLcp(String a, String b) {
        int minLen = Math.min(a.length(), b.length());
        for (int k = 0; k < minLen; k++) {
            if (a.charAt(k) != b.charAt(k)) {
                return k;
            }
        }
        return minLen;
    }

    public int[] longestCommonPrefix(String[] words) {
        int n = words.length;
        int[] ans = new int[n];
        if (n < 2) {
            return ans;
        }
        int[] pre = new int[n - 1];
        for (int j = 0; j < n - 1; j++) {
            pre[j] = getLcp(words[j], words[j + 1]);
        }
        int[] leftMax = new int[n];
        leftMax[0] = 0;
        for (int j = 1; j < n; j++) {
            leftMax[j] = Math.max(leftMax[j - 1], pre[j - 1]);
        }
        int[] rightMax = new int[n];
        rightMax[n - 1] = 0;
        for (int k = n - 2; k >= 0; k--) {
            rightMax[k] = Math.max(rightMax[k + 1], pre[k]);
        }
        for (int i = 0; i < n; i++) {
            int cand1 = (i >= 2) ? leftMax[i - 1] : 0;
            int cand2 = (i <= n - 3) ? rightMax[i + 1] : 0;
            int origMax = Math.max(cand1, cand2);
            int bridge = 0;
            if (i > 0 && i < n - 1) {
                bridge = getLcp(words[i - 1], words[i + 1]);
            }
            ans[i] = Math.max(origMax, bridge);
        }
        return ans;
    }
}
# @lc code=end