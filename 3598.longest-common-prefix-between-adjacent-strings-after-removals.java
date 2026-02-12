#
# @lc app=leetcode id=3598 lang=java
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#
# @lc code=start
class Solution {
    private int getLCP(String a, String b) {
        int len = Math.min(a.length(), b.length());
        int i = 0;
        while (i < len && a.charAt(i) == b.charAt(i)) i++;
        return i;
    }
    public int[] longestCommonPrefix(String[] words) {
        int n = words.length;
        if (n == 1) return new int[]{0};
        int[] lcp = new int[n-1];
        for (int i = 0; i < n-1; i++) {
            lcp[i] = getLCP(words[i], words[i+1]);
        }
        int[] answer = new int[n];
        for (int i = 0; i < n; i++) {
            int maxLCP = 0;
            // If i-1 and i+1 are valid, compute new LCP
            if (i-1 >= 0 && i+1 < n) {
                maxLCP = getLCP(words[i-1], words[i+1]);
            }
            // Consider unaffected LCPs
            for (int j = 0; j < n-1; j++) {
                if (j == i-1 || j == i) continue; // affected pairs
                maxLCP = Math.max(maxLCP, lcp[j]);
            }
            answer[i] = maxLCP;
        }
        return answer;
    }
}
# @lc code=end