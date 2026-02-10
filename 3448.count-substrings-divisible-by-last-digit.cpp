#
# @lc app=leetcode id=3448 lang=cpp
#
# [3448] Count Substrings Divisible By Last Digit
#

# @lc code=start
class Solution {
public:
    long long countSubstrings(string s) {
        int n = s.length();
        long long total = 0;
        for(int d = 1; d <= 9; d++) {
            long long fr[10][10] = {0};
            long long local_ans = 0;
            for(int i = n - 1; i >= 0; i--) {
                long long new_fr[10][10] = {0};
                for(int md = 0; md < d; md++) {
                    for(int pw = 0; pw < d; pw++) {
                        long long c = fr[md][pw];
                        if(c == 0) continue;
                        int dig = s[i] - '0';
                        int nmd = (int)(((long long)dig * pw % d + md) % d);
                        int npw = (int)(((long long)pw * 10) % d);
                        if(nmd == 0) {
                            local_ans += c;
                        }
                        new_fr[nmd][npw] += c;
                    }
                }
                for(int md = 0; md < d; md++) {
                    for(int pw = 0; pw < d; pw++) {
                        fr[md][pw] = new_fr[md][pw];
                    }
                }
                int digi = s[i] - '0';
                if(digi == d) {
                    local_ans += 1;
                    int ipw = 10 % d;
                    fr[0][ipw] += 1;
                }
            }
            total += local_ans;
        }
        return total;
    }
};
# @lc code=end