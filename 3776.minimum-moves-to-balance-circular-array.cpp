#
# @lc app=leetcode id=3776 lang=cpp
#
# [3776] Minimum Moves to Balance Circular Array
#

# @lc code=start
class Solution {
public:
    long long minMoves(vector<int>& balance) {
        int n = balance.size();
        long long total = 0;
        int neg_idx = -1;
        for(int i = 0; i < n; ++i) {
            total += (long long) balance[i];
            if(balance[i] < 0) {
                neg_idx = i;
            }
        }
        if(total < 0) return -1;
        if(neg_idx == -1) return 0;
        long long deficit = - (long long) balance[neg_idx];
        long long moves = 0;
        long long remaining = deficit;
        for(int dist = 1; dist <= n / 2; ++dist) {
            int p1 = (neg_idx + dist) % n;
            int p2 = ((neg_idx - dist) % n + n) % n;
            long long cap = (long long) balance[p1];
            if(p1 != p2) {
                cap += (long long) balance[p2];
            }
            if(cap >= remaining) {
                moves += remaining * (long long) dist;
                remaining = 0;
            } else {
                moves += cap * (long long) dist;
                remaining -= cap;
            }
            if(remaining <= 0) break;
        }
        if(remaining > 0) return -1;
        return moves;
    }
};
# @lc code=end