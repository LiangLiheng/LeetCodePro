#
# @lc app=leetcode id=3725 lang=java
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#
# @lc code=start
import java.util.*;
class Solution {
    public int countCoprime(int[][] mat) {
        int MOD = 1_000_000_007;
        int m = mat.length, n = mat[0].length;
        Map<Integer, Integer> dp = new HashMap<>();
        // Initialize with row 0
        for (int num : mat[0]) {
            dp.put(num, (dp.getOrDefault(num, 0) + 1) % MOD);
        }
        for (int i = 1; i < m; i++) {
            Map<Integer, Integer> ndp = new HashMap<>();
            for (int num : mat[i]) {
                for (Map.Entry<Integer, Integer> entry : dp.entrySet()) {
                    int g = gcd(num, entry.getKey());
                    ndp.put(g, (int)(((long)ndp.getOrDefault(g, 0) + entry.getValue()) % MOD));
                }
            }
            dp = ndp;
        }
        // Verify output corresponds to GCD 1 combinations
        return dp.getOrDefault(1, 0);
    }
    private int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }
}
# @lc code=end