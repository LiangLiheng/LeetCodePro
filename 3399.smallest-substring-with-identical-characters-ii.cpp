#
# @lc app=leetcode id=3399 lang=cpp
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
#include <vector>
#include <algorithm>
class Solution {
public:
    int minLength(std::string s, int numOps) {
        int n = s.size();
        std::vector<int> runs;
        for (int i = 0; i < n; ) {
            int start = i;
            while (i < n && s[i] == s[start]) ++i;
            runs.push_back(i - start);
        }
        int left = 1, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            bool possible = false;
            if (mid == 1) {
                int cost1 = 0, cost2 = 0;
                for (int j = 0; j < n; ++j) {
                    char t1 = (j % 2 == 0 ? '0' : '1');
                    if (s[j] != t1) ++cost1;
                    char t2 = (j % 2 == 0 ? '1' : '0');
                    if (s[j] != t2) ++cost2;
                }
                if (std::min(cost1, cost2) <= numOps) possible = true;
            } else {
                long long need = 0;
                for (int len : runs) {
                    need += static_cast<long long>(len) / (mid + 1);
                    if (need > numOps) break;
                }
                if (need <= numOps) possible = true;
            }
            if (possible) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
# @lc code=end