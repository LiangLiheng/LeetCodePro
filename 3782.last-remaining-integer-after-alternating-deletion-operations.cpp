#
# @lc app=leetcode id=3782 lang=cpp
#
# [3782] Last Remaining Integer After Alternating Deletion Operations
#

# @lc code=start
class Solution {
public:
    long long lastInteger(long long n) {
        std::vector<std::pair<long long, int>> history;
        long long m = n;
        int op = 1;  // 1: left, 2: right
        while (m > 1) {
            history.emplace_back(m, op);
            m = (m + 1) / 2;
            op = 3 - op;
        }
        long long pos = 1;
        for (int i = static_cast<int>(history.size()) - 1; i >= 0; --i) {
            auto [prev_m, this_op] = history[i];
            long long prev_pos;
            if (this_op == 1) {
                prev_pos = 2 * pos - 1;
            } else {
                int parity = static_cast<int>(prev_m & 1);
                prev_pos = 2 * pos - parity;
            }
            pos = prev_pos;
        }
        return pos;
    }
};
# @lc code=end