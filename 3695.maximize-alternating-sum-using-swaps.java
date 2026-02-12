#
# @lc app=leetcode id=3695 lang=java
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
import java.util.*;
class Solution {
    public long maxAlternatingSum(int[] nums, int[][] swaps) {
        int n = nums.length;
        // 1. Find connected components using Union-Find
        int[] parent = new int[n];
        for (int i = 0; i < n; ++i) parent[i] = i;
        for (int[] swap : swaps) {
            union(parent, swap[0], swap[1]);
        }
        // 2. Group indices by component
        Map<Integer, List<Integer>> groups = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            int root = find(parent, i);
            groups.computeIfAbsent(root, k -> new ArrayList<>()).add(i);
        }
        int[] res = new int[n];
        // 3. For each component, assign largest values to smallest/even indices
        for (List<Integer> group : groups.values()) {
            List<Integer> idxs = new ArrayList<>(group);
            List<Integer> vals = new ArrayList<>();
            for (int idx : idxs) vals.add(nums[idx]);
            Collections.sort(idxs);
            Collections.sort(vals, Collections.reverseOrder());
            for (int j = 0; j < idxs.size(); ++j) {
                res[idxs.get(j)] = vals.get(j);
            }
        }
        // 4. Compute the alternating sum
        long ans = 0;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) ans += res[i];
            else ans -= res[i];
        }
        // 5. Optionally, verify that each component's values are assigned as intended (debug/validation step)
        return ans;
    }
    private int find(int[] parent, int x) {
        if (parent[x] != x) parent[x] = find(parent, parent[x]);
        return parent[x];
    }
    private void union(int[] parent, int x, int y) {
        int px = find(parent, x), py = find(parent, y);
        if (px != py) parent[px] = py;
    }
}
# @lc code=end