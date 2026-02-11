#
# @lc app=leetcode id=3563 lang=java
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#

# @lc code=start
class Solution {
    public String lexicographicallySmallestString(String s) {
        int n = s.length();
        if (n == 0) return "";
        boolean[][] canEmpty = new boolean[n][n];
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                // outer pair
                if (canPair(s.charAt(i), s.charAt(j)) && (i + 1 > j - 1 || canEmpty[i + 1][j - 1])) {
                    canEmpty[i][j] = true;
                    continue;
                }
                // splits
                for (int k = i; k < j; ++k) {
                    boolean left = canEmpty[i][k];
                    boolean right = canEmpty[k + 1][j];
                    if (left && right) {
                        canEmpty[i][j] = true;
                        break;
                    }
                }
            }
        }
        String[] minFrom = new String[n + 1];
        minFrom[n] = "";
        for (int pos = n - 1; pos >= 0; --pos) {
            String best = null;
            if (canEmpty[pos][n - 1]) {
                best = "";
            }
            for (int j = pos; j < n; ++j) {
                boolean gapOk = (j == pos) || canEmpty[pos][j - 1];
                if (gapOk) {
                    String cand = String.valueOf(s.charAt(j)) + minFrom[j + 1];
                    if (best == null || cand.compareTo(best) < 0) {
                        best = cand;
                    }
                }
            }
            minFrom[pos] = best;
        }
        return minFrom[0];
    }

    private boolean canPair(char a, char b) {
        int da = a - 'a';
        int db = b - 'a';
        if (Math.abs(da - db) == 1) return true;
        return (a == 'a' && b == 'z') || (a == 'z' && b == 'a');
    }
}
# @lc code=end