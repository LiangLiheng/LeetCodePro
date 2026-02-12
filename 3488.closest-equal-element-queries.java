#
# @lc app=leetcode id=3488 lang=java
#
# [3488] Closest Equal Element Queries
#

# @lc code=start
import java.util.*;
class Solution {
    public List<Integer> solveQueries(int[] nums, int[] queries) {
        int n = nums.length;
        // Step 1: Map value to list of indices
        Map<Integer, List<Integer>> valToIndices = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            valToIndices.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }
        List<Integer> res = new ArrayList<>();
        for (int q : queries) {
            int val = nums[q];
            List<Integer> idxs = valToIndices.get(val);
            if (idxs.size() == 1) {
                res.add(-1);
                continue;
            }
            int minDist = Integer.MAX_VALUE;
            for (int idx : idxs) {
                if (idx == q) continue;
                int d = Math.abs(idx - q);
                d = Math.min(d, n - d); // circular distance
                minDist = Math.min(minDist, d);
            }
            res.add(minDist);
        }
        return res;
    }
}
# @lc code=end