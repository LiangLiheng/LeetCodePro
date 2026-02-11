#
# @lc app=leetcode id=3695 lang=java
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
import java.util.*;

class Solution {
    private int find(int[] parent, int x) {
        return parent[x] == x ? x : (parent[x] = find(parent, parent[x]));
    }

    public long maxAlternatingSum(int[] nums, int[][] swaps) {
        int n = nums.length;
        int[] parent = new int[n];
        int[] rank = new int[n];
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        for (int[] swap : swaps) {
            int rootP = find(parent, swap[0]);
            int rootQ = find(parent, swap[1]);
            if (rootP != rootQ) {
                if (rank[rootP] > rank[rootQ]) {
                    parent[rootQ] = rootP;
                } else if (rank[rootP] < rank[rootQ]) {
                    parent[rootP] = rootQ;
                } else {
                    parent[rootQ] = rootP;
                    ++rank[rootP];
                }
            }
        }
        Map<Integer, List<Integer>> compValues = new HashMap<>();
        Map<Integer, Integer> evenCounts = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            int root = find(parent, i);
            compValues.computeIfAbsent(root, k -> new ArrayList<>()).add(nums[i]);
            if (i % 2 == 0) {
                evenCounts.merge(root, 1, Integer::sum);
            }
        }
        long ans = 0;
        for (Map.Entry<Integer, List<Integer>> entry : compValues.entrySet()) {
            List<Integer> vals = entry.getValue();
            int numEven = evenCounts.getOrDefault(entry.getKey(), 0);
            vals.sort((a, b) -> b.compareTo(a)); // descending
            long contrib = 0;
            for (int j = 0; j < numEven; ++j) {
                contrib += vals.get(j);
            }
            for (int j = numEven; j < vals.size(); ++j) {
                contrib -= vals.get(j);
            }
            ans += contrib;
        }
        return ans;
    }
}
# @lc code=end