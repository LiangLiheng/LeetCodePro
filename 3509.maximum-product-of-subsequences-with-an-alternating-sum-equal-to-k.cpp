#
# @lc app=leetcode id=3509 lang=cpp
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        int n = nums.size();
        const int OFFSET = 1800;
        const int MAX_S = 3600;
        const int STATES = (MAX_S + 1) * 2;
        vector<bitset<5001>> curr(STATES);
        vector<bitset<5001>> next_state(STATES);
        for (int i = 0; i < n; ++i) {
            int m = nums[i];
            // reset next_state
            for (auto& bs : next_state) bs.reset();
            // add singleton subsequence [nums[i]]
            {
                long long pr = m;
                if (pr <= limit) {
                    int dif = m;
                    int s = OFFSET + dif;
                    if (s >= 0 && s <= MAX_S) {
                        int p = 1;
                        int idx = s * 2 + p;
                        next_state[idx].set((size_t)pr);
                    }
                }
            }
            // update from curr to next_state
            for (int s = 0; s <= MAX_S; ++s) {
                for (int p = 0; p < 2; ++p) {
                    int idx = s * 2 + p;
                    bitset<5001>& old_bs = curr[idx];
                    if (old_bs.none()) continue;
                    // skip
                    next_state[idx] |= old_bs;
                    // take
                    int sign = (p == 0 ? 1 : -1);
                    int delta = sign * m;
                    int ns = s + delta;
                    if (ns < 0 || ns > MAX_S) continue;
                    int np = 1 - p;
                    int nidx = ns * 2 + np;
                    bitset<5001>& nbs = next_state[nidx];
                    size_t pos = old_bs._Find_first();
                    while (pos < 5001) {
                        long long newpr = (long long)pos * m;
                        if (newpr > limit) break;
                        nbs.set((size_t)newpr);
                        pos = old_bs._Find_next(pos);
                    }
                }
            }
            // swap
            curr.swap(next_state);
        }
        int ts = OFFSET + k;
        if (ts < 0 || ts > MAX_S) return -1;
        bitset<5001>& bs0 = curr[ts * 2 + 0];
        bitset<5001>& bs1 = curr[ts * 2 + 1];
        for (int pr = limit; pr >= 0; --pr) {
            if (bs0[pr] || bs1[pr]) {
                return pr;
            }
        }
        return -1;
    }
};
# @lc code=end