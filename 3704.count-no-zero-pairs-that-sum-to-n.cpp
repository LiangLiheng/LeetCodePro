#
# @lc app=leetcode id=3704 lang=cpp
#
# [3704] Count No-Zero Pairs That Sum to N
#

# @lc code=start
class Solution {
public:
    long long countNoZeroPairs(long long n) {
        std::string num = std::to_string(n);
        int len = num.length();
        int digits[20];
        for(int i = 0; i < len; i++) {
            digits[i] = num[i] - '0';
        }
        long long memo0[20][2][2];
        long long memo1[20][2][2];
        memset(memo0, -1, sizeof(memo0));
        memset(memo1, -1, sizeof(memo1));
        auto solve = [&](auto&& self, int pos, int sa, int sb) -> std::pair<long long, long long> {
            if(pos == len) {
                return {sa && sb ? 1LL : 0LL, 0LL};
            }
            if(memo0[pos][sa][sb] != -1) {
                return {memo0[pos][sa][sb], memo1[pos][sa][sb]};
            }
            long long w0 = 0;
            long long w1 = 0;
            int mda = sa ? 1 : 0;
            int mdb = sb ? 1 : 0;
            for(int da = mda; da <= 9; ++da) {
                int nsa = sa || (da != 0);
                for(int db = mdb; db <= 9; ++db) {
                    int nsb = sb || (db != 0);
                    auto p = self(self, pos + 1, nsa, nsb);
                    long long lo0 = p.first;
                    long long lo1 = p.second;
                    for(int cin = 0; cin < 2; ++cin) {
                        long long lw = (cin == 0 ? lo0 : lo1);
                        if(lw == 0) continue;
                        int sv = da + db + cin;
                        if(sv % 10 == digits[pos]) {
                            int co = sv / 10;
                            if(co == 0) {
                                w0 += lw;
                            } else {
                                w1 += lw;
                            }
                        }
                    }
                }
            }
            memo0[pos][sa][sb] = w0;
            memo1[pos][sa][sb] = w1;
            return {w0, w1};
        };
        auto res = solve(solve, 0, 0, 0);
        return res.first;
    }
};
# @lc code=end