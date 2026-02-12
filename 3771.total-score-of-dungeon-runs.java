# @lc app=leetcode id=3771 lang=java
#
# [3771] Total Score of Dungeon Runs
#
# @lc code=start
class Solution {
    public long totalScore(int hp, int[] damage, int[] requirement) {
        int n = damage.length;
        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + damage[i];
        }
        long total = 0;
        for (int start = 0; start < n; ++start) {
            long curHp = hp;
            for (int i = start; i < n; ++i) {
                curHp -= damage[i];
                if (curHp >= requirement[i]) {
                    total++;
                }
            }
        }
        return total;
    }
}
# @lc code=end