#
# @lc app=leetcode id=3785 lang=java
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#
# @lc code=start
import java.util.*;
class Solution {
    public int minSwaps(int[] nums, int[] forbidden) {
        int n = nums.length;
        // Step 1: Find all positions where nums[i] == forbidden[i]
        List<Integer> conflicts = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            if (nums[i] == forbidden[i]) conflicts.add(i);
        }
        if (conflicts.isEmpty()) return 0;

        // Step 2: Robust impossibility check
        // For each value, ensure enough non-forbidden placements exist
        Map<Integer, List<Integer>> valueToPositions = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            valueToPositions.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }
        Map<Integer, Integer> forbiddenCount = new HashMap<>();
        for (int i = 0; i < n; ++i) {
            forbiddenCount.put(forbidden[i], forbiddenCount.getOrDefault(forbidden[i], 0) + 1);
        }
        for (Map.Entry<Integer, Integer> entry : forbiddenCount.entrySet()) {
            int value = entry.getKey();
            int count = entry.getValue();
            int available = n - Collections.frequency(Arrays.asList(Arrays.stream(forbidden).boxed().toArray(Integer[]::new)), value);
            if (valueToPositions.getOrDefault(value, new ArrayList<>()).size() > n - count) {
                return -1;
            }
        }
        // Step 3: Decompose into cycles and resolve each
        boolean[] visited = new boolean[n];
        int swaps = 0;
        for (int i = 0; i < n; ++i) {
            if (visited[i] || nums[i] == forbidden[i]) continue;
            int curr = i;
            List<Integer> cycle = new ArrayList<>();
            boolean hasConflict = false;
            while (!visited[curr]) {
                visited[curr] = true;
                cycle.add(curr);
                if (nums[curr] == forbidden[curr]) hasConflict = true;
                // Find the next index where nums[next] should go
                int next = -1;
                for (int j = 0; j < n; ++j) {
                    if (!visited[j] && nums[curr] == forbidden[j]) {
                        next = j;
                        break;
                    }
                }
                if (next == -1) break;
                curr = next;
            }
            if (cycle.size() > 1 && hasConflict) {
                swaps += cycle.size() - 1;
            } else if (cycle.size() == 1 && nums[cycle.get(0)] == forbidden[cycle.get(0)]) {
                return -1;
            }
        }
        // Step 4: Final universal verification
        for (int i = 0; i < n; ++i) {
            if (nums[i] == forbidden[i]) return -1;
        }
        return swaps;
    }
}
# @lc code=end