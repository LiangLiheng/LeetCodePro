#
# @lc app=leetcode id=3398 lang=cpp
#
# [3398] Smallest Substring With Identical Characters I
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        int left = 1, right = n;
        const int INF = 1000000005;
        auto can = [&](int maxl) -> bool {
            int pd[1005][2];
            int cd[1005][2];
            for (int i = 0; i < 1005; ++i) {
                for (int j = 0; j < 2; ++j) {
                    pd[i][j] = INF;
                }
            }
            int orig = s[0] - '0';
            pd[1][0] = (0 != orig);
            pd[1][1] = (1 != orig);
            for (int pos = 1; pos < n; ++pos) {
                for (int i = 0; i < 1005; ++i) {
                    for (int j = 0; j < 2; ++j) {
                        cd[i][j] = INF;
                    }
                }
                int corig = s[pos] - '0';
                for (int plen = 1; plen <= maxl; ++plen) {
                    for (int pc = 0; pc < 2; ++pc) {
                        if (pd[plen][pc] > 1001) continue;
                        for (int nc = 0; nc < 2; ++nc) {
                            int cost = (nc != corig);
                            int nlen = (nc == pc ? plen + 1 : 1);
                            if (nlen > maxl) continue;
                            cd[nlen][nc] = std::min(cd[nlen][nc], pd[plen][pc] + cost);
                        }
                    }
                }
                for (int i = 0; i < 1005; ++i) {
                    for (int j = 0; j < 2; ++j) {
                        pd[i][j] = cd[i][j];
                    }
                }
            }
            int minc = INF;
            for (int len = 1; len <= maxl; ++len) {
                for (int c = 0; c < 2; ++c) {
                    minc = std::min(minc, pd[len][c]);
                }
            }
            return minc <= numOps;
        };
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (can(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
# @lc code=end