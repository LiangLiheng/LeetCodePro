#
# @lc app=leetcode id=3579 lang=cpp
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.size();
        const int INF = 1000000005;
        vector<int> dp(n + 1, INF);
        dp[0] = 0;
        auto compute_cost = [&](int L, int R) -> int {
            int len = R - L + 1;
            vector<vector<int>> cnt(26, vector<int>(26, 0));
            int M = 0;
            for (int p = L; p <= R; ++p) {
                int cs = word1[p] - 'a';
                int ct = word2[p] - 'a';
                if (cs != ct) {
                    cnt[cs][ct]++;
                    ++M;
                }
            }
            int K = 0;
            for (int a = 0; a < 26; ++a) {
                for (int b = a + 1; b < 26; ++b) {
                    K += min(cnt[a][b], cnt[b][a]);
                }
            }
            int cost_no = M - K;
            // reverse
            vector<vector<int>> cnt_rev(26, vector<int>(26, 0));
            int Mr = 0;
            for (int p = 0; p < len; ++p) {
                int rev_p = L + len - 1 - p;
                int cs = word1[rev_p] - 'a';
                int ct = word2[L + p] - 'a';
                if (cs != ct) {
                    cnt_rev[cs][ct]++;
                    ++Mr;
                }
            }
            int Kr = 0;
            for (int a = 0; a < 26; ++a) {
                for (int b = a + 1; b < 26; ++b) {
                    Kr += min(cnt_rev[a][b], cnt_rev[b][a]);
                }
            }
            int cost_rev = 1 + Mr - Kr;
            return min(cost_no, cost_rev);
        };
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                int c = compute_cost(j, i - 1);
                if (dp[j] < INF) {
                    dp[i] = min(dp[i], dp[j] + c);
                }
            }
        }
        return dp[n];
    }
};
# @lc code=end