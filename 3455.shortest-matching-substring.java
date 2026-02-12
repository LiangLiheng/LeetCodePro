#
# @lc app=leetcode id=3455 lang=java
#
# [3455] Shortest Matching Substring
#

# @lc code=start
class Solution {
    public int shortestMatchingSubstring(String s, String p) {
        // Handle the special case where p is "**"
        if (p.equals("**")) return 0;
        int firstStar = p.indexOf('*');
        int secondStar = p.indexOf('*', firstStar + 1);
        String pre = p.substring(0, firstStar);
        String mid = p.substring(firstStar + 1, secondStar);
        String suf = p.substring(secondStar + 1);
        int n = s.length();
        int minLen = Integer.MAX_VALUE;
        for (int i = 0; i <= n - pre.length(); ++i) {
            if (!s.startsWith(pre, i)) continue;
            int preEnd = i + pre.length();
            for (int j = preEnd; j <= n - suf.length(); ++j) {
                if (!s.startsWith(suf, j)) continue;
                int sufEnd = j + suf.length();
                // Check that mid occurs entirely between preEnd and j
                int midStart = mid.isEmpty() ? preEnd : s.indexOf(mid, preEnd);
                if (mid.isEmpty() || (midStart != -1 && midStart + mid.length() <= j)) {
                    int len = sufEnd - i;
                    if (len < minLen) minLen = len;
                }
            }
        }
        return minLen == Integer.MAX_VALUE ? -1 : minLen;
    }
}
# @lc code=end