#
# @lc app=leetcode id=3503 lang=cpp
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution {
public:
    int longestPalindrome(string s, string t) {
        int n = s.length();
        int m = t.length();
        int ans = 1;  // at least 1 (single char)
        auto is_pal = [](const string& p) -> bool {
            int l = 0;
            int r = (int)p.length() - 1;
            while (l < r) {
                if (p[l++] != p[r--]) {
                    return false;
                }
            }
            return true;
        };
        auto get_max_pal = [&](const string& str) -> int {
            int sz = str.length();
            int mx = 1;
            for (int i = 0; i < sz; ++i) {
                for (int len_sub = 1; len_sub <= sz - i; ++len_sub) {
                    string sub = str.substr(i, len_sub);
                    if (is_pal(sub)) {
                        mx = std::max(mx, len_sub);
                    }
                }
            }
            return mx;
        };
        int max_s = get_max_pal(s);
        int max_t = get_max_pal(t);
        ans = std::max({ans, max_s, max_t});
        // Now non-empty from both
        for (int i = 0; i < n; ++i) {
            for (int len1 = 1; len1 <= n - i; ++len1) {
                string left = s.substr(i, len1);
                for (int j = 0; j < m; ++j) {
                    for (int len2 = 1; len2 <= m - j; ++len2) {
                        string right = t.substr(j, len2);
                        string comb = left + right;
                        if (is_pal(comb)) {
                            ans = std::max(ans, len1 + len2);
                        }
                    }
                }
            }
        }
        return ans;
    }
};
# @lc code=end