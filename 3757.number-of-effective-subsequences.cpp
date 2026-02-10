#
# @lc app=leetcode id=3757 lang=cpp
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
class Solution {
public:
    int countEffective(vector<int>& nums) {
        int n = nums.size();
        long long full_or = 0;
        for (int x : nums) full_or |= x;
        vector<int> bits;
        for (int b = 0; b < 20; b++) {
            if (full_or & (1 << b)) bits.push_back(b);
        }
        int k = bits.size();
        if (k == 0) return 0;
        int max_mask = 1 << k;
        vector<long long> freq(max_mask, 0);
        for (int x : nums) {
            int proj = 0;
            for (int j = 0; j < k; j++) {
                if (x & (1 << bits[j])) proj |= (1 << j);
            }
            freq[proj]++;
        }
        vector<long long> subset_sum = freq;
        for (int i = 0; i < k; i++) {
            for (int mask = 0; mask < max_mask; mask++) {
                if (mask & (1 << i)) {
                    subset_sum[mask] += subset_sum[mask ^ (1 << i)];
                }
            }
        }
        const long long MOD = 1000000007LL;
        auto modpow = [&](long long base, long long exp) -> long long {
            long long res = 1;
            base %= MOD;
            while (exp > 0) {
                if (exp & 1) res = res * base % MOD;
                base = base * base % MOD;
                exp >>= 1;
            }
            return res;
        };
        long long ans = 0;
        int ALL = (1 << k) - 1;
        for (int sub = 1; sub < max_mask; sub++) {
            int comp = ALL ^ sub;
            long long num_free = subset_sum[comp];
            long long ways = modpow(2LL, num_free);
            int pop = __builtin_popcount(sub);
            long long sign = (pop % 2 == 1) ? 1LL : (MOD - 1LL);
            ans = (ans + sign * ways % MOD) % MOD;
        }
        return (int) ans;
    }
};
# @lc code=end