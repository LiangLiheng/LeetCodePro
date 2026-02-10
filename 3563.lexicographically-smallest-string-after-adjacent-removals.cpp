#
# @lc app=leetcode id=3563 lang=cpp
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#

# @lc code=start
class Solution {
public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        auto is_consec = [&](char x, char y) -> bool {
            int d = abs((int)x - (int)y);
            return d == 1 || (x == 'a' && y == 'z') || (x == 'z' && y == 'a');
        };
        vector<vector<int>> max_pairs(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            max_pairs[i][i] = 0;
        }
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                int j = i + len - 1;
                int temp = 0;
                if (is_consec(s[i], s[j])) {
                    int inner = (i + 1 <= j - 1 ? max_pairs[i + 1][j - 1] : 0);
                    temp = 1 + inner;
                }
                for (int k = i; k < j; ++k) {
                    temp = max(temp, max_pairs[i][k] + max_pairs[k + 1][j]);
                }
                max_pairs[i][j] = temp;
            }
        }
        vector<string> best(n + 1);
        best[n] = "";
        for (int i = n - 1; i >= 0; --i) {
            string min_cand(1, '{'); // sentinel larger than any valid
            // check empty
            int tot_len = n - i;
            bool can_be_empty = (tot_len % 2 == 0);
            if (can_be_empty) {
                int need_pairs = tot_len / 2;
                int got_pairs = (i < n ? max_pairs[i][n - 1] : 0);
                if (got_pairs == need_pairs) {
                    min_cand = "";
                }
            }
            // check next k
            for (int k = i; k < n; ++k) {
                int gap_len = k - i;
                bool gap_ok = (gap_len % 2 == 0);
                if (gap_ok && gap_len > 0) {
                    int need = gap_len / 2;
                    int got = max_pairs[i][k - 1];
                    gap_ok = (got == need);
                }
                if (gap_ok) {
                    string cand = "";
                    cand += s[k];
                    cand += best[k + 1];
                    if (cand < min_cand) {
                        min_cand = cand;
                    }
                }
            }
            best[i] = min_cand;
        }
        return best[0];
    }
};
# @lc code=end