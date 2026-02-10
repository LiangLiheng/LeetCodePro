#
# @lc app=leetcode id=3677 lang=cpp
#
# [3677] Count Binary Palindromic Numbers
#

# @lc code=start
class Solution {
public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) return 1;
        int L = 64 - __builtin_clzll(n);
        long long ans = 1LL; // for 0
        for (int len = 1; len < L; ++len) {
            int free_bits = (len + 1) / 2 - 1;
            ans += (1LL << free_bits);
        }
        // same length
        int left_len = (L + 1) / 2;
        int free_bits = left_len - 1;
        int num_masks = 1 << free_bits;
        long long cnt_same = 0;
        for (int mask = 0; mask < num_masks; ++mask) {
            long long pal = (1LL << (L - 1)) | 1LL;
            int pos = L - 2;
            for (int b = 0; b < free_bits; ++b) {
                if (mask & (1 << b)) {
                    pal |= (1LL << pos);
                    int mpos = L - 1 - pos;
                    pal |= (1LL << mpos);
                }
                --pos;
            }
            if (pal <= n) {
                ++cnt_same;
            }
        }
        ans += cnt_same;
        return static_cast<int>(ans);
    }
};
# @lc code=end