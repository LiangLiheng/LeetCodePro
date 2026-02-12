#
# @lc app=leetcode id=3575 lang=java
#
# [3575] Maximum Good Subtree Score
#
# @lc code=start
import java.util.*;
class Solution {
    static final int MOD = 1000000007;
    public int goodSubtreeSum(int[] vals, int[] par) {
        int n = vals.length;
        List<Integer>[] tree = new ArrayList[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int i = 1; i < n; ++i) tree[par[i]].add(i);
        int[] maxScore = new int[n];
        dfs(0, vals, tree, maxScore);
        long sum = 0;
        for (int s : maxScore) sum = (sum + s) % MOD;
        return (int) sum;
    }
    // Returns: Map<digitMask, maxSum> for the subtree rooted at u
    private Map<Integer, Integer> dfs(int u, int[] vals, List<Integer>[] tree, int[] maxScore) {
        Map<Integer, Integer> dp = new HashMap<>();
        int myMask = digitMask(vals[u]);
        if (myMask != -1) dp.put(myMask, vals[u]);
        for (int v : tree[u]) {
            Map<Integer, Integer> childDP = dfs(v, vals, tree, maxScore);
            Map<Integer, Integer> nextDP = new HashMap<>(dp);
            // Decompose merge: for each pair, only combine if digits do not overlap, and verify validity
            for (Map.Entry<Integer, Integer> ce : childDP.entrySet()) {
                int cmask = ce.getKey(), csum = ce.getValue();
                for (Map.Entry<Integer, Integer> de : dp.entrySet()) {
                    int dmask = de.getKey(), dsum = de.getValue();
                    if ((cmask & dmask) == 0) {
                        int nmask = cmask | dmask;
                        // Explicitly verify digit uniqueness
                        if (Integer.bitCount(nmask) == Integer.bitCount(cmask) + Integer.bitCount(dmask)) {
                            nextDP.put(nmask, Math.max(nextDP.getOrDefault(nmask, 0), csum + dsum));
                        }
                    }
                }
                // Also keep childDP alone
                nextDP.put(cmask, Math.max(nextDP.getOrDefault(cmask, 0), csum));
            }
            dp = nextDP;
        }
        // Ensure single-node selection is possible
        if (myMask != -1) dp.put(myMask, Math.max(dp.getOrDefault(myMask, 0), vals[u]));
        // Verify all entries have unique digits (consistency check)
        Iterator<Map.Entry<Integer, Integer>> it = dp.entrySet().iterator();
        while (it.hasNext()) {
            Map.Entry<Integer, Integer> entry = it.next();
            if (!isUniqueDigits(entry.getKey())) it.remove();
        }
        int max = 0;
        for (int s : dp.values()) max = Math.max(max, s);
        maxScore[u] = max;
        return dp;
    }
    // Returns bitmask of digits in x, or -1 if any digit repeats
    private int digitMask(int x) {
        int mask = 0;
        while (x > 0) {
            int d = x % 10;
            if (((mask >> d) & 1) != 0) return -1;
            mask |= 1 << d;
            x /= 10;
        }
        return mask;
    }
    // Consistency check: returns true if mask has only unique digits
    private boolean isUniqueDigits(int mask) {
        // Each bit (0-9) represents a digit, so always unique
        // Mask should not have more than 10 bits
        return mask >= 0 && mask < (1<<10);
    }
}
# @lc code=end