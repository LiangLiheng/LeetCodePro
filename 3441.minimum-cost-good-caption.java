#
# @lc app=leetcode id=3441 lang=java
#
# [3441] Minimum Cost Good Caption
#
# @lc code=start
import java.util.*;
class Solution {
    public String minCostGoodCaption(String caption) {
        int n = caption.length();
        if (n < 3) return "";
        int INF = 1000000000;
        int[][] dp = new int[n][26];
        int[][] prev = new int[n][26];
        int[][] prevChar = new int[n][26];
        for (int[] row : dp) Arrays.fill(row, INF);
        for (int[] row : prev) Arrays.fill(row, -1);
        for (int[] row : prevChar) Arrays.fill(row, -1);
        // Explicitly initialize all possible first groups (positions 0 to k-1, k>=3)
        for (int k = 3; k <= n; ++k) {
            for (int ch = 0; ch < 26; ++ch) {
                int cost = 0;
                for (int t = 0; t < k; ++t)
                    if (caption.charAt(t) - 'a' != ch) cost++;
                if (cost < dp[k-1][ch] || (cost == dp[k-1][ch] && ch < prevChar[k-1][ch])) {
                    dp[k-1][ch] = cost;
                    prev[k-1][ch] = -1;
                    prevChar[k-1][ch] = -1;
                }
            }
        }
        // DP for rest positions
        for (int i = 3; i < n; ++i) {
            for (int k = 3; k <= i+1; ++k) {
                int j = i - k + 1;
                if (j < 0) break;
                for (int ch = 0; ch < 26; ++ch) {
                    int cost = 0;
                    for (int t = j; t <= i; ++t)
                        if (caption.charAt(t) - 'a' != ch) cost++;
                    if (j == 0) continue; // already initialized base case
                    for (int ch2 = 0; ch2 < 26; ++ch2) {
                        if (dp[j-1][ch2] == INF) continue;
                        int total = dp[j-1][ch2] + cost;
                        if (total < dp[i][ch] || (total == dp[i][ch] && (ch2 < prevChar[i][ch] || (ch2 == prevChar[i][ch] && ch < ch2)))) {
                            dp[i][ch] = total;
                            prev[i][ch] = j-1;
                            prevChar[i][ch] = ch2;
                        }
                    }
                }
            }
        }
        // Find minimal cost at the end
        int minCost = INF, bestCh = -1;
        for (int ch = 0; ch < 26; ++ch) {
            if (dp[n-1][ch] < minCost || (dp[n-1][ch] == minCost && ch < bestCh)) {
                minCost = dp[n-1][ch];
                bestCh = ch;
            }
        }
        if (minCost == INF) return "";
        // Reconstruct answer
        StringBuilder sb = new StringBuilder();
        int i = n-1, ch = bestCh;
        while (i >= 0) {
            int j = prev[i][ch];
            int len = i - j;
            for (int t = 0; t < len; ++t) sb.append((char)('a'+ch));
            int ch2 = prevChar[i][ch];
            i = j;
            ch = ch2;
        }
        String result = sb.reverse().toString();
        // Verification step: check all groups are at least 3 consecutive identical
        int cnt = 1;
        for (int idx = 1; idx < result.length(); ++idx) {
            if (result.charAt(idx) == result.charAt(idx-1)) {
                cnt++;
            } else {
                if (cnt < 3) return "";
                cnt = 1;
            }
        }
        if (cnt < 3) return "";
        return result;
    }
}
# @lc code=end