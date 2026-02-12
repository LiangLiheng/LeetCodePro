// @lc app=leetcode id=3765 lang=java
//
// [3765] Complete Prime Number
//
// @lc code=start
class Solution {
    public boolean completePrime(int num) {
        String s = String.valueOf(num);
        int n = s.length();
        for (int i = 1; i <= n; ++i) {
            int prefix = Integer.parseInt(s.substring(0, i));
            int suffix = Integer.parseInt(s.substring(n - i));
            if (!isPrime(prefix) || !isPrime(suffix)) {
                return false;
            }
        }
        return true;
    }
    private boolean isPrime(int x) {
        if (x < 2) return false;
        if (x == 2) return true;
        if (x % 2 == 0) return false;
        for (int i = 3; i * i <= x; i += 2) {
            if (x % i == 0) return false;
        }
        return true;
    }
}
// @lc code=end