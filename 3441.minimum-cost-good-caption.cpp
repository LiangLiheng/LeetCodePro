#
# @lc app=leetcode id=3441 lang=cpp
#
# [3441] Minimum Cost Good Caption
#

# @lc code=start
class Solution {
public:
    string minCostGoodCaption(string caption) {
        int n = caption.length();
        if (n < 3) return "";
        std::vector<int> val(n);
        for (int i = 0; i < n; ++i) {
            val[i] = caption[i] - 'a';
        }
        const int INF = 2000000000;
        std::vector<std::vector<std::vector<int>>> dp(n + 1, std::vector<std::vector<int>>(26, std::vector<int>(4, INF)));
        for (int c = 0; c < 26; ++c) {
            dp[n][c][3] = 0;
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int pc = 0; pc < 26; ++pc) {
                for (int pk = 1; pk <= 3; ++pk) {
                    int min_val = INF;
                    for (int nc = 0; nc < 26; ++nc) {
                        int cost = std::abs(val[i] - nc);
                        int nk = -1;
                        if (nc == pc) {
                            nk = (pk == 3 ? 3 : pk + 1);
                        } else if (pk == 3) {
                            nk = 1;
                        }
                        if (nk != -1) {
                            int nextc = cost + dp[i + 1][nc][nk];
                            if (nextc < min_val) min_val = nextc;
                        }
                    }
                    dp[i][pc][pk] = min_val;
                }
            }
        }
        int min_cost = INF;
        for (int nc = 0; nc < 26; ++nc) {
            int cost = std::abs(val[0] - nc);
            int total = cost + dp[1][nc][1];
            if (total < min_cost) min_cost = total;
        }
        if (min_cost == INF) return "";
        // Construct lex smallest
        std::string result;
        int prev_char = -1;
        int prev_streak = 0;
        int current_cost = 0;
        for (int i = 0; i < n; ++i) {
            bool found = false;
            for (int nc = 0; nc < 26; ++nc) {
                int cost = std::abs(val[i] - nc);
                int nk = -1;
                if (prev_char != -1 && nc == prev_char) {
                    nk = (prev_streak == 3 ? 3 : prev_streak + 1);
                } else if (prev_char == -1 || prev_streak == 3) {
                    nk = 1;
                }
                if (nk != -1) {
                    int remaining = dp[i + 1][nc][nk];
                    if (remaining != INF && current_cost + cost + remaining == min_cost) {
                        result += static_cast<char>('a' + nc);
                        prev_char = nc;
                        prev_streak = nk;
                        current_cost += cost;
                        found = true;
                        break;
                    }
                }
            }
            if (!found) {
                return ""; // fallback
            }
        }
        return result;
    }
};
# @lc code=end