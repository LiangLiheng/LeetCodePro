#
# @lc app=leetcode id=3777 lang=java
#
# [3777] Minimum Deletions to Make Alternating Substring
#
# @lc code=start
class Solution {
    public int[] minDeletions(String s, int[][] queries) {
        char[] chars = s.toCharArray();
        List<Integer> answer = new ArrayList<>();
        for (int[] q : queries) {
            if (q[0] == 1) {
                // Flip the character at index j
                int j = q[1];
                chars[j] = chars[j] == 'A' ? 'B' : 'A';
            } else if (q[0] == 2) {
                // Compute minimum deletions for s[l..r]
                int l = q[1], r = q[2];
                int deletions = 0;
                for (int i = l + 1; i <= r; ++i) {
                    if (chars[i] == chars[i - 1]) {
                        deletions++;
                    }
                }
                answer.add(deletions);
            }
        }
        // Convert answer list to array
        int[] res = new int[answer.size()];
        for (int i = 0; i < answer.size(); ++i) {
            res[i] = answer.get(i);
        }
        return res;
    }
}
# @lc code=end