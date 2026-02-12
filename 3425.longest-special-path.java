#
# @lc app=leetcode id=3425 lang=java
#
# [3425] Longest Special Path
#
# @lc code=start
import java.util.*;
class Solution {
    public int[] longestSpecialPath(int[][] edges, int[] nums) {
        int n = nums.length;
        // Build adjacency list with edge weights
        List<int[]>[] tree = new List[n];
        for (int i = 0; i < n; i++) tree[i] = new ArrayList<>();
        for (int[] e : edges) {
            tree[e[0]].add(new int[]{e[1], e[2]});
            tree[e[1]].add(new int[]{e[0], e[2]});
        }
        int[] res = new int[]{0, 1}; // [max_length, min_num_nodes]
        Set<Integer> pathValues = new HashSet<>();
        dfs(0, -1, 0, 1, pathValues, tree, nums, res);
        return res;
    }

    private void dfs(int node, int parent, int currLen, int numNodes, Set<Integer> pathValues, List<int[]>[] tree, int[] nums, int[] res) {
        boolean added = pathValues.add(nums[node]);
        if (!added) return;
        // Update result at every node (not just leaves)
        if (currLen > res[0]) {
            res[0] = currLen;
            res[1] = numNodes;
        } else if (currLen == res[0] && numNodes < res[1]) {
            res[1] = numNodes;
        }
        for (int[] next : tree[node]) {
            int nei = next[0], weight = next[1];
            if (nei == parent) continue;
            if (!pathValues.contains(nums[nei])) {
                dfs(nei, node, currLen + weight, numNodes + 1, pathValues, tree, nums, res);
            }
        }
        pathValues.remove(nums[node]);
    }
}
# @lc code=end