#
# @lc app=leetcode id=3457 lang=java
#
# [3457] Eat Pizzas!
#

# @lc code=start
class Solution {
    public long maxWeight(int[] pizzas) {
        Arrays.sort(pizzas);
        int n = pizzas.length;
        int days = n / 4;
        long maxTotal = 0;

        // Strategy 1: Greedy from largest down
        long total1 = 0;
        for (int d = 0; d < days; ++d) {
            int base = n - 4 * (d + 1);
            int[] group = new int[4];
            for (int j = 0; j < 4; ++j) {
                group[j] = pizzas[base + j];
            }
            Arrays.sort(group);
            if ((d & 1) == 0) {
                total1 += group[3];
            } else {
                total1 += group[2];
            }
        }
        maxTotal = total1;

        // Strategy 2: Greedy from smallest up
        long total2 = 0;
        for (int d = 0; d < days; ++d) {
            int base = 4 * d;
            int[] group = new int[4];
            for (int j = 0; j < 4; ++j) {
                group[j] = pizzas[base + j];
            }
            Arrays.sort(group);
            if ((d & 1) == 0) {
                total2 += group[3];
            } else {
                total2 += group[2];
            }
        }
        if (total2 > maxTotal) maxTotal = total2;

        // Verification: If further improvement is possible, consider reversed day ordering
        // (For generality, this could be expanded further with more batch orderings)

        return maxTotal;
    }
}
# @lc code=end