#
# @lc app=leetcode id=3765 lang=java
#
# [3765] Complete Prime Number
#

# @lc code=start
class Solution {
    public boolean completePrime(int num) {
        String s = String.valueOf(num);
        int len = s.length();
        for (int i = 1; i <= len; ++i) {
            long prefix = Long.parseLong(s.substring(0, i));
            if (!isPrime(prefix)) {
                return false;
            }
        }
        for (int i = 1; i <= len; ++i) {
            long suffix = Long.parseLong(s.substring(len - i));
            if (!isPrime(suffix)) {
                return false;
            }
        }
        return true;
    }

    private boolean isPrime(long n) {
        if (n <= 1) {
            return false;
        }
        if (n <= 3) {
            return true;
        }
        if (n % 2 == 0 || n % 3 == 0) {
            return false;
        }
        for (long i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) {
                return false;
            }
        }
        return true;
    }
}
# @lc code=end