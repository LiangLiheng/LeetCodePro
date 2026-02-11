#
# @lc app=leetcode id=3721 lang=java
#
# [3721] Longest Balanced Subarray II
#

# @lc code=start
class Solution {
  public int longestBalanced(int[] nums) {
    int n = nums.length;
    final int MAX = 100001;
    int[] firstPos = new int[MAX];
    int[] lastPos = new int[MAX];
    java.util.Arrays.fill(firstPos, -1);
    java.util.Arrays.fill(lastPos, -1);
    for (int i = 0; i < n; i++) {
      int val = nums[i];
      if (firstPos[val] == -1) {
        firstPos[val] = i;
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      int val = nums[i];
      if (lastPos[val] == -1) {
        lastPos[val] = i;
      }
    }
    java.util.HashMap<Integer, Integer> minIdx = new java.util.HashMap<>();
    minIdx.put(0, -1);
    int pd = 0;
    int fd = 0;
    int ans = 0;
    for (int r = 0; r < n; r++) {
      int val = nums[r];
      if (firstPos[val] == r) {
        int sign = (val % 2 == 0 ? 1 : -1);
        pd += sign;
      }
      if (minIdx.containsKey(pd)) {
        int idx = minIdx.get(pd);
        ans = Math.max(ans, r - idx);
      }
      if (lastPos[val] == r) {
        int sign = (val % 2 == 0 ? 1 : -1);
        fd += sign;
        minIdx.putIfAbsent(fd, r);
      }
    }
    return ans;
  }
}
# @lc code=end