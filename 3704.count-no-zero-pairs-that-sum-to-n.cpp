#
# @lc app=leetcode id=3704 lang=cpp
#
# [3704] Count No-Zero Pairs That Sum to N
#
# @lc code=start
class Solution {
public:
    bool hasZero(long long num) {
        while (num > 0) {
            if (num % 10 == 0) return true;
            num /= 10;
        }
        return false;
    }
    
    long long countNoZeroPairs(long long n) {
        long long count = 0;
        for (long long a = 1; a < n; a++) {
            long long b = n - a;
            if (!hasZero(a) && !hasZero(b)) {
                count++;
            }
        }
        return count;
    }
};
# @lc code=end