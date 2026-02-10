#
# @lc app=leetcode id=3504 lang=cpp
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

class Solution {
public:
    int longestPalindrome(string s, string t) {
        int n = s.size();
        int m = t.size();
        int ans = 0;

        // Pal DP for s: ispal and max_start_s
        vector<vector<bool>> ispal_s(n, vector<bool>(n, false));
        vector<int> max_start_s(n, 0);
        for (int i = 0; i < n; ++i) {
            ispal_s[i][i] = true;
            max_start_s[i] = 1;
            ans = max(ans, 1);
        }
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i + 1]) {
                ispal_s[i][i + 1] = true;
                max_start_s[i] = 2;
                ans = max(ans, 2);
            }
        }
        for (int leng = 3; leng <= n; ++leng) {
            for (int i = 0; i <= n - leng; ++i) {
                int j = i + leng - 1;
                if (s[i] == s[j] && ispal_s[i + 1][j - 1]) {
                    ispal_s[i][j] = true;
                    max_start_s[i] = max(max_start_s[i], leng);
                    ans = max(ans, leng);
                }
            }
        }

        // Pal DP for t: ispal, max_start_t (unused), max_end_t
        vector<vector<bool>> ispal_t(m, vector<bool>(m, false));
        vector<int> max_start_t(m, 0);
        vector<int> max_end_t(m, 0);
        for (int i = 0; i < m; ++i) {
            ispal_t[i][i] = true;
            max_start_t[i] = 1;
            max_end_t[i] = 1;
            ans = max(ans, 1);
        }
        for (int i = 0; i < m - 1; ++i) {
            if (t[i] == t[i + 1]) {
                ispal_t[i][i + 1] = true;
                max_start_t[i] = 2;
                max_end_t[i + 1] = 2;
                ans = max(ans, 2);
            }
        }
        for (int leng = 3; leng <= m; ++leng) {
            for (int i = 0; i <= m - leng; ++i) {
                int j = i + leng - 1;
                if (t[i] == t[j] && ispal_t[i + 1][j - 1]) {
                    ispal_t[i][j] = true;
                    max_start_t[i] = max(max_start_t[i], leng);
                    max_end_t[j] = max(max_end_t[j], leng);
                    ans = max(ans, leng);
                }
            }
        }

        // Type1: match1[i][j] longest s[i...] prefix == rev(t[...j] suffix)
        vector<vector<int>> match1(n, vector<int>(m, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < m; ++j) {
                if (s[i] == t[j]) {
                    int nextk = 0;
                    if (i + 1 < n && j - 1 >= 0) {
                        nextk = match1[i + 1][j - 1];
                    }
                    match1[i][j] = 1 + nextk;
                }
            }
        }
        // Process type1
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int k = match1[i][j];
                if (k > 0) {
                    int mid_start = i + k;
                    int mid_len = 0;
                    if (mid_start < n) {
                        mid_len = max_start_s[mid_start];
                    }
                    ans = max(ans, 2 * k + mid_len);
                }
            }
        }

        // Hashing for type2
        const long long MOD1 = 1000000007LL;
        const long long BASE1 = 131LL;
        const long long MOD2 = 1000000009LL;
        const long long BASE2 = 137LL;

        auto make_hasher = [&](const string& str) -> auto {
            int sz = str.size();
            vector<long long> p1(sz + 1, 1), h1(sz + 1, 0);
            vector<long long> p2(sz + 1, 1), h2(sz + 1, 0);
            for (int i = 1; i <= sz; ++i) {
                p1[i] = p1[i - 1] * BASE1 % MOD1;
                h1[i] = (h1[i - 1] * BASE1 + (str[i - 1] - 'a' + 1)) % MOD1;
                p2[i] = p2[i - 1] * BASE2 % MOD2;
                h2[i] = (h2[i - 1] * BASE2 + (str[i - 1] - 'a' + 1)) % MOD2;
            }
            auto get = [&](int L, int R) -> pair<long long, long long> {
                int len = R - L + 1;
                long long val1 = (h1[R + 1] + MOD1 - h1[L] * p1[len] % MOD1) % MOD1;
                long long val2 = (h2[R + 1] + MOD2 - h2[L] * p2[len] % MOD2) % MOD2;
                return {val1, val2};
            };
            return get;
        };

        string tr = t;
        reverse(tr.begin(), tr.end());
        auto get_hs = make_hasher(s);
        auto get_htr = make_hasher(tr);

        // Helper to get max k for type2 at p, r
        auto get_k = [&](int p, int r) -> int {
            int low = 1;
            int hi = min(p + 1, r + 1);
            int res = 0;
            while (low <= hi) {
                int md = low + (hi - low) / 2;
                int starts = p - md + 1;
                if (starts < 0) {
                    hi = md - 1;
                    continue;
                }
                int starttr = m - 1 - r;
                int endtr = starttr + md - 1;
                if (endtr >= m) {
                    hi = md - 1;
                    continue;
                }
                auto hs_val = get_hs(starts, p);
                auto htr_val = get_htr(starttr, endtr);
                if (hs_val == htr_val) {
                    res = md;
                    low = md + 1;
                } else {
                    hi = md - 1;
                }
            }
            return res;
        };

        // Process type2
        for (int p = 0; p < n; ++p) {
            for (int r = 0; r < m; ++r) {
                int k = get_k(p, r);
                if (k > 0) {
                    int mid_end = r - k;
                    int mid_len = 0;
                    if (mid_end >= 0) {
                        mid_len = max_end_t[mid_end];
                    }
                    ans = max(ans, 2 * k + mid_len);
                }
            }
        }

        return ans;
    }
};
# @lc code=end