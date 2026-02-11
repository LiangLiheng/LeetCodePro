#
# @lc app=leetcode id=3605 lang=java
#
# [3605] Minimum Stability Factor of Array
#

# @lc code=start
class Solution {
    private static int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    private int query(int l, int r, int[][] st, int[] logg) {
        int len = r - l + 1;
        int k = logg[len];
        return gcd(st[l][k], st[r - (1 << k) + 1][k]);
    }

    private boolean canAchieve(int L, int[] nums, int n, int[][] st, int[] logg, int maxC) {
        if (L > n) return true;
        int count = 0;
        int last = -1;
        for (int i = 0; i <= n - L; i++) {
            int g = query(i, i + L - 1, st, logg);
            if (g > 1) {
                if (i > last) {
                    last = i + L - 1;
                    count++;
                    if (count > maxC) return false;
                }
            }
        }
        return true;
    }

    public int minStable(int[] nums, int maxC) {
        int n = nums.length;
        int LOG = 18;
        int[][] st = new int[n][LOG];
        int[] logg = new int[n + 1];
        logg[1] = 0;
        for (int i = 2; i <= n; i++) {
            logg[i] = logg[i / 2] + 1;
        }
        for (int i = 0; i < n; i++) {
            st[i][0] = nums[i];
        }
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
        int left = 0, right = n;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(mid + 1, nums, n, st, logg, maxC)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
}
# @lc code=end