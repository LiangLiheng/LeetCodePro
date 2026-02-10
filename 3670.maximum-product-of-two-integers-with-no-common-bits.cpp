#
# @lc app=leetcode id=3670 lang=cpp
#
# [3670] Maximum Product of Two Integers With No Common Bits
#

# @lc code=start
class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        const int N = 1 << 20;
        std::vector<int> f(N, 0);
        for (int x : nums) {
            f[x] = x;
        }
        for (int i = 0; i < 20; ++i) {
            for (int m = 0; m < N; ++m) {
                if (m & (1 << i)) {
                    f[m] = std::max(f[m], f[m ^ (1 << i)]);
                }
            }
        }
        long long ans = 0;
        for (int x : nums) {
            int comp = (~x) & (N - 1);
            ans = std::max(ans, 1LL * x * f[comp]);
        }
        return ans;
    }
};
# @lc code=end