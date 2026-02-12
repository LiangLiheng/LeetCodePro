#
# @lc app=leetcode id=3470 lang=java
#
# [3470] Permutations IV
#
# @lc code=start
import java.util.*;

class Solution {
    public int[] permute(int n, long k) {
        List<Integer> odds = new ArrayList<>();
        List<Integer> evens = new ArrayList<>();
        for (int i = 1; i <= n; ++i) {
            if (i % 2 == 1) odds.add(i);
            else evens.add(i);
        }
        // dp[remOdd][remEven][lastParity], lastParity: 0=odd, 1=even, 2=start
        Long[][][] dp = new Long[odds.size()+1][evens.size()+1][3];
        // Count all valid alternating perms with given counts and lastParity
        class Counter {
            long count(int ro, int re, int lp) {
                if (ro==0 && re==0) return 1;
                if (dp[ro][re][lp] != null) return dp[ro][re][lp];
                long total = 0;
                if (lp == 2) {
                    // Start: can pick odd or even
                    if (ro > 0) total += ro * count(ro-1, re, 0);
                    if (re > 0) total += re * count(ro, re-1, 1);
                } else if (lp == 0) {
                    // Last was odd, must pick even
                    if (re > 0) total += re * count(ro, re-1, 1);
                } else {
                    // Last was even, must pick odd
                    if (ro > 0) total += ro * count(ro-1, re, 0);
                }
                return dp[ro][re][lp] = total;
            }
        }
        Counter counter = new Counter();
        long total = counter.count(odds.size(), evens.size(), 2);
        if (k > total) return new int[0];
        // Build the permutation step by step
        boolean[] used = new boolean[n+1];
        int[] ans = new int[n];
        int ro = odds.size(), re = evens.size(), lp = 2;
        for (int pos = 0; pos < n; ++pos) {
            boolean found = false;
            for (int cand = 1; cand <= n; ++cand) {
                if (used[cand]) continue;
                int candParity = cand % 2;
                if (lp == 2 || candParity != lp) {
                    int nro = ro, nre = re;
                    if (candParity == 0) nre--; else nro--;
                    if (nro < 0 || nre < 0) continue;
                    long cnt = counter.count(nro, nre, candParity);
                    if (k > cnt) {
                        k -= cnt;
                    } else {
                        ans[pos] = cand;
                        used[cand] = true;
                        ro = nro; re = nre; lp = candParity;
                        found = true;
                        break;
                    }
                }
            }
            if (!found) return new int[0]; // Could not find a valid candidate
        }
        // Verification step: check all constraints
        if (ans.length != n) return new int[0];
        boolean[] checkUsed = new boolean[n+1];
        for (int i = 0; i < n; ++i) {
            if (ans[i] < 1 || ans[i] > n || checkUsed[ans[i]]) return new int[0];
            checkUsed[ans[i]] = true;
            if (i > 0 && (ans[i]%2) == (ans[i-1]%2)) return new int[0];
        }
        return ans;
    }
}
# @lc code=end