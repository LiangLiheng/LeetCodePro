#
# @lc app=leetcode id=3544 lang=java
#
# [3544] Subtree Inversion Sum
#
# @lc code=start
class Solution {
    public long subtreeInversionSum(int[][] edges, int[] nums, int k) {
        int n = nums.length;
        List<Integer>[] tree = new List[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int[] e : edges) {
            tree[e[0]].add(e[1]);
            tree[e[1]].add(e[0]);
        }
        long[][] dp = new long[n][k+2];
        dfs(0, -1, tree, nums, k, dp);
        long res = Long.MIN_VALUE;
        for (int d = 0; d <= k; ++d) {
            res = Math.max(res, dp[0][d]);
        }
        return res;
    }
    private void dfs(int node, int parent, List<Integer>[] tree, int[] nums, int k, long[][] dp) {
        List<long[]> childDPs = new ArrayList<>();
        for (int child : tree[node]) {
            if (child == parent) continue;
            dfs(child, node, tree, nums, k, dp);
            childDPs.add(dp[child]);
        }
        long[] dpNotInvert = new long[k+2];
        Arrays.fill(dpNotInvert, 0);
        dpNotInvert[k+1] = 0;
        if (childDPs.isEmpty()) {
            for (int d = 0; d <= k+1; ++d) dpNotInvert[d] = nums[node];
        } else {
            for (int d = 0; d <= k+1; ++d) dpNotInvert[d] = nums[node];
            for (long[] childDP : childDPs) {
                long[] next = new long[k+2];
                Arrays.fill(next, Long.MIN_VALUE);
                for (int d = 0; d <= k; ++d) {
                    for (int cd = 0; cd <= k; ++cd) {
                        int nd = Math.min(k, d+1);
                        if (dpNotInvert[d] != Long.MIN_VALUE && childDP[nd] != Long.MIN_VALUE) {
                            next[d] = Math.max(next[d], dpNotInvert[d] + childDP[nd]);
                        }
                    }
                }
                for (int d = 0; d <= k+1; ++d) {
                    dpNotInvert[d] = next[d] == Long.MIN_VALUE ? dpNotInvert[d] : next[d];
                }
            }
        }
        long dpInvert = -nums[node];
        if (childDPs.isEmpty()) {
            dpInvert = -nums[node];
        } else {
            List<long[]> allStates = new ArrayList<>();
            for (long[] childDP : childDPs) {
                allStates.add(childDP);
            }
            long sum = 0;
            for (long[] childDP : allStates) {
                sum += childDP[1];
            }
            dpInvert += sum;
        }
        for (int d = 0; d < k; ++d) {
            dp[node][d] = dpNotInvert[d];
        }
        dp[node][k] = Math.max(dpNotInvert[k], dpInvert);
        dp[node][k+1] = dp[node][k];
    }
}
# @lc code=end