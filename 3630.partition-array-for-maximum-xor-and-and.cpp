#
# @lc app=leetcode id=3630 lang=cpp
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
class Solution {
public:
    long long maximizeXorAndXor(vector<int>& nums) {
        int n = nums.size();
        int N = 1 << n;
        vector<long long> xor_all(N, 0);
        vector<long long> and_all(N, 0);
        and_all[0] = (1LL << 40) - 1;
        for (int mask = 1; mask < N; ++mask) {
            int i = __builtin_ctz(mask);
            int prev = mask ^ (1 << i);
            xor_all[mask] = xor_all[prev] ^ (long long)nums[i];
            and_all[mask] = and_all[prev] & (long long)nums[i];
        }
        vector<long long> maxxs(N, 0);
        for (int masks = 0; masks < N; ++masks) {
            long long sx = xor_all[masks];
            long long cur = sx;
            for (int sub = masks; sub > 0; sub = (sub - 1) & masks) {
                long long y = xor_all[sub];
                long long val = y + (sx ^ y);
                if (val > cur) cur = val;
            }
            maxxs[masks] = cur;
        }
        long long ans = 0;
        int full = N - 1;
        for (int maskb = 0; maskb < N; ++maskb) {
            long long andb = (maskb == 0 ? 0LL : and_all[maskb]);
            int masks = full ^ maskb;
            long long val = andb + maxxs[masks];
            if (val > ans) ans = val;
        }
        return ans;
    }
};
# @lc code=end