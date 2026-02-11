#
# @lc app=leetcode id=3579 lang=java
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
class Solution {
    public int minOperations(String word1, String word2) {
        int n = word1.length();
        int[][] cost = new int[n][n];
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                int l = len;
                // no reverse
                int[][] freq = new int[26][26];
                for (int k = i; k <= j; ++k) {
                    int sc = word1.charAt(k) - 'a';
                    int tc = word2.charAt(k) - 'a';
                    freq[sc][tc]++;
                }
                int M_no = 0;
                for (int c = 0; c < 26; ++c) {
                    M_no += freq[c][c];
                }
                int D_no = l - M_no;
                int pairs_no = 0;
                for (int x = 0; x < 26; ++x) {
                    for (int y = x + 1; y < 26; ++y) {
                        pairs_no += Math.min(freq[y][x], freq[x][y]);
                    }
                }
                int ops_no = D_no - pairs_no;
                // reverse
                int[][] freq_rev = new int[26][26];
                for (int k = 0; k < l; ++k) {
                    int pos_s = i + l - 1 - k;
                    int sc = word1.charAt(pos_s) - 'a';
                    int tc = word2.charAt(i + k) - 'a';
                    freq_rev[sc][tc]++;
                }
                int M_rev = 0;
                for (int c = 0; c < 26; ++c) {
                    M_rev += freq_rev[c][c];
                }
                int D_rev = l - M_rev;
                int pairs_rev = 0;
                for (int x = 0; x < 26; ++x) {
                    for (int y = x + 1; y < 26; ++y) {
                        pairs_rev += Math.min(freq_rev[y][x], freq_rev[x][y]);
                    }
                }
                int ops_rev = D_rev - pairs_rev + 1;
                cost[i][j] = Math.min(ops_no, ops_rev);
            }
        }
        // partition DP
        int[] dp = new int[n + 1];
        int INF = 1 << 30;
        for (int ii = 0; ii <= n; ++ii) {
            dp[ii] = INF;
        }
        dp[0] = 0;
        for (int end = 1; end <= n; ++end) {
            for (int st = 0; st < end; ++st) {
                dp[end] = Math.min(dp[end], dp[st] + cost[st][end - 1]);
            }
        }
        return dp[n];
    }
}
# @lc code=end