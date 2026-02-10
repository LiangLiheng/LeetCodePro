#
# @lc app=leetcode id=3455 lang=cpp
#
# [3455] Shortest Matching Substring
#

# @lc code=start
class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        size_t star1 = p.find('*');
        size_t star2 = p.find('*', star1 + 1);
        string prefix = p.substr(0, star1);
        string middle = p.substr(star1 + 1, star2 - star1 - 1);
        string suffix = p.substr(star2 + 1);
        int lp = prefix.size();
        int lm = middle.size();
        int ls = suffix.size();
        int n = s.size();
        auto find_ends = [&](const string& pat) -> vector<int> {
            int m = pat.size();
            if (m == 0) return {};
            vector<int> pi(m, 0);
            for (int i = 1, j = 0; i < m; ++i) {
                while (j > 0 && pat[i] != pat[j]) j = pi[j - 1];
                if (pat[i] == pat[j]) ++j;
                pi[i] = j;
            }
            vector<int> res;
            int q = 0;
            for (int i = 0; i < n; ++i) {
                while (q > 0 && s[i] != pat[q]) q = pi[q - 1];
                if (s[i] == pat[q]) ++q;
                if (q == m) {
                    res.push_back(i);
                    q = pi[q - 1];
                }
            }
            return res;
        };
        vector<int> pre_ends = (lp > 0 ? find_ends(prefix) : vector<int>{});
        vector<int> mid_ends = (lm > 0 ? find_ends(middle) : vector<int>{});
        vector<int> suf_ends = (ls > 0 ? find_ends(suffix) : vector<int>{});
        const int INF = 1 << 30;
        int ans = INF;
        if (lm > 0) {
            for (int C : mid_ends) {
                int threshA = C - lm;
                int A = -1;
                if (lp == 0) {
                    A = threshA;
                } else {
                    auto it = upper_bound(pre_ends.begin(), pre_ends.end(), threshA);
                    if (it != pre_ends.begin()) {
                        --it;
                        A = *it;
                    }
                }
                if (lp > 0 && A == -1) continue;
                int start_pos = (lp == 0 ? A + 1 : A - lp + 1);
                if (start_pos < 0) continue;
                int threshE = C + ls;
                int E = -1;
                if (ls == 0) {
                    E = C;
                } else {
                    auto it = lower_bound(suf_ends.begin(), suf_ends.end(), threshE);
                    if (it != suf_ends.end()) {
                        E = *it;
                    }
                }
                if (E == -1) continue;
                int curlen = E - start_pos + 1;
                if (curlen >= 0) ans = min(ans, curlen);
            }
        } else {
            if (ls == 0) {
                if (lp == 0) {
                    ans = 0;
                } else if (!pre_ends.empty()) {
                    ans = lp;
                }
            } else {
                for (int E : suf_ends) {
                    int threshA = E - ls;
                    int A = -1;
                    if (lp == 0) {
                        A = threshA;
                    } else {
                        auto it = upper_bound(pre_ends.begin(), pre_ends.end(), threshA);
                        if (it != pre_ends.begin()) {
                            --it;
                            A = *it;
                        }
                    }
                    if (lp > 0 && A == -1) continue;
                    int start_pos = (lp == 0 ? A + 1 : A - lp + 1);
                    if (start_pos < 0) continue;
                    int curlen = E - start_pos + 1;
                    if (curlen >= 0) ans = min(ans, curlen);
                }
            }
        }
        return (ans == INF ? -1 : ans);
    }
};
# @lc code=end