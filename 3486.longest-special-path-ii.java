#
# @lc app=leetcode id=3486 lang=java
#
# [3486] Longest Special Path II
#
# @lc code=start
import java.util.*;
class Solution {
    public int[] longestSpecialPath(int[][] edges, int[] nums) {
        int n = nums.length;
        List<int[]>[] tree = new ArrayList[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            tree[u].add(new int[]{v, w});
            tree[v].add(new int[]{u, w});
        }
        int[] result = new int[]{0, Integer.MAX_VALUE};
        // For each node, initiate a DFS to consider all downward paths from that node
        for (int i = 0; i < n; ++i) {
            dfs(i, -1, tree, nums, new HashMap<>(), false, 0, 1, result);
        }
        return new int[]{result[0], result[1]};
    }
    private void dfs(int node, int parent, List<int[]>[] tree, int[] nums, Map<Integer,Integer> count, boolean usedDuplicate, int pathLen, int nodeCount, int[] result) {
        count.put(nums[node], count.getOrDefault(nums[node], 0) + 1);
        boolean isDuplicate = count.get(nums[node]) == 2;
        if (count.get(nums[node]) > 2 || (usedDuplicate && isDuplicate)) {
            count.put(nums[node], count.get(nums[node]) - 1);
            return;
        }
        if (pathLen > result[0]) {
            result[0] = pathLen;
            result[1] = nodeCount;
        } else if (pathLen == result[0]) {
            result[1] = Math.min(result[1], nodeCount);
        }
        for (int[] nei : tree[node]) {
            int next = nei[0], weight = nei[1];
            if (next == parent) continue;
            dfs(next, node, tree, nums, count, usedDuplicate || isDuplicate, pathLen + weight, nodeCount + 1, result);
        }
        count.put(nums[node], count.get(nums[node]) - 1);
    }
}
# @lc code=end