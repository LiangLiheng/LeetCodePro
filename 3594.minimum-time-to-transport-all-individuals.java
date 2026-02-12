#
# @lc app=leetcode id=3594 lang=java
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
import java.util.*;
class Solution {
    public double minTime(int n, int k, int m, int[] time, double[] mul) {
        if (k == 1 && n > 1) return -1.0;
        int ALL = (1 << n) - 1;
        Map<Long, Double> memo = new HashMap<>();
        double res = dp(0, 0, n, k, m, time, mul, memo, ALL);
        // Verification step: return -1.0 if state is unsolvable
        return res == Double.POSITIVE_INFINITY ? -1.0 : res;
    }
    private double dp(int mask, int stage, int n, int k, int m, int[] time, double[] mul, Map<Long, Double> memo, int ALL) {
        if (mask == ALL) return 0.0;
        long key = ((long)mask << 3) | stage;
        if (memo.containsKey(key)) return memo.get(key);
        double min = Double.POSITIVE_INFINITY;
        List<Integer> atBase = new ArrayList<>();
        for (int i = 0; i < n; i++) if (((mask >> i) & 1) == 0) atBase.add(i);
        int sz = atBase.size();
        boolean foundValidMove = false;
        // Generate all groups of 1..k people to cross
        for (int group = 1; group <= Math.min(k, sz); ++group) {
            List<int[]> combs = combs(atBase, group);
            for (int[] groupArr : combs) {
                int nextMask = mask;
                int maxTime = 0;
                for (int idx : groupArr) { nextMask |= 1 << idx; maxTime = Math.max(maxTime, time[idx]); }
                double crossTime = maxTime * mul[stage];
                int adv = (int)Math.floor(crossTime) % m;
                int nextStage = (stage + adv) % m;
                if (nextMask == ALL) {
                    min = Math.min(min, crossTime);
                    foundValidMove = true;
                    continue;
                }
                // Someone must return
                for (int ret : groupArr) {
                    int retMask = nextMask & ~(1 << ret);
                    double retTime = time[ret] * mul[nextStage];
                    int retAdv = (int)Math.floor(retTime) % m;
                    int retStage = (nextStage + retAdv) % m;
                    double rec = dp(retMask, retStage, n, k, m, time, mul, memo, ALL);
                    if (rec != -1.0 && rec != Double.POSITIVE_INFINITY) {
                        min = Math.min(min, crossTime + retTime + rec);
                        foundValidMove = true;
                    }
                }
            }
        }
        // Verification step: if no valid move was found, return -1.0 explicitly
        double result = foundValidMove ? min : -1.0;
        memo.put(key, result == -1.0 ? Double.POSITIVE_INFINITY : result);
        return result;
    }
    private List<int[]> combs(List<Integer> arr, int k) {
        List<int[]> res = new ArrayList<>();
        combsHelper(arr, k, 0, new int[k], 0, res);
        return res;
    }
    private void combsHelper(List<Integer> arr, int k, int idx, int[] curr, int pos, List<int[]> res) {
        if (pos == k) { res.add(curr.clone()); return; }
        if (idx == arr.size()) return;
        curr[pos] = arr.get(idx);
        combsHelper(arr, k, idx+1, curr, pos+1, res);
        combsHelper(arr, k, idx+1, curr, pos, res);
    }
}
# @lc code=end