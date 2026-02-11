#
# @lc app=leetcode id=3646 lang=java
#
# [3646] Next Special Palindrome Number
#

# @lc code=start
class Solution {
    public long specialPalindrome(long n) {
        long[] min_greater = {Long.MAX_VALUE};
        int[] evens = {2, 4, 6, 8};
        int[] odds = {1, 3, 5, 7, 9};
        
        // Even length: subsets of evens
        for (int mask = 0; mask < (1 << 4); mask++) {
            int[] cnt = new int[10];
            int len = 0;
            for (int i = 0; i < 4; i++) {
                if ((mask & (1 << i)) != 0) {
                    int d = evens[i];
                    cnt[d] = d;
                    len += d;
                }
            }
            if (len == 0 || len > 19) continue;
            int[] pcount = new int[10];
            for (int d = 1; d <= 9; d++) pcount[d] = cnt[d] / 2;
            generate(0, new StringBuilder(), pcount, min_greater, n, len / 2, -1, len);
        }
        
        // Odd length: one odd + subsets of evens
        for (int o : odds) {
            for (int mask = 0; mask < (1 << 4); mask++) {
                int[] cnt = new int[10];
                cnt[o] = o;
                int len = o;
                for (int i = 0; i < 4; i++) {
                    if ((mask & (1 << i)) != 0) {
                        int d = evens[i];
                        cnt[d] = d;
                        len += d;
                    }
                }
                if (len == 0 || len > 19) continue;
                int[] pcount = new int[10];
                for (int d = 1; d <= 9; d++) pcount[d] = cnt[d] / 2;
                generate(0, new StringBuilder(), pcount, min_greater, n, len / 2, o, len);
            }
        }
        
        return min_greater[0] == Long.MAX_VALUE ? 0 : min_greater[0]; // 0 fallback unlikely
    }
    
    private void generate(int pos, StringBuilder pairs, int[] rem, long[] min_g, long n, int nump, int center, int L) {
        if (pos == nump) {
            StringBuilder full = new StringBuilder(pairs);
            if (L % 2 == 1) {
                full.append((char) ('0' + center));
            }
            String left_part = full.toString();
            String pair_str = left_part.substring(0, nump);
            StringBuilder revb = new StringBuilder(pair_str);
            revb.reverse();
            String num_str = left_part + revb.toString();
            try {
                long num = Long.parseLong(num_str);
                if (num > n && num < min_g[0]) {
                    min_g[0] = num;
                }
            } catch (NumberFormatException ignored) {
            }
            return;
        }
        for (int d = 1; d <= 9; d++) {
            if (rem[d] > 0) {
                rem[d]--;
                pairs.append((char) ('0' + d));
                generate(pos + 1, pairs, rem, min_g, n, nump, center, L);
                pairs.deleteCharAt(pairs.length() - 1);
                rem[d]++;
            }
        }
    }
}
# @lc code=end