#
# @lc app=leetcode id=3729 lang=java
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#

# @lc code=start
class Solution {
  public long numGoodSubarrays(int[] nums, int k) {
    long total = 0L;
    java.util.Map<Integer, java.util.Long> freq = new java.util.HashMap<>();
    freq.put(0, 1L);
    long prefix = 0L;
    long KK = k;
    for (int num : nums) {
      prefix = (prefix + ((long) num % KK + KK) % KK) % KK;
      int key = (int) prefix;
      if (freq.containsKey(key)) {
        total += freq.get(key);
      }
      freq.put(key, freq.getOrDefault(key, 0L) + 1L);
    }
    long subtract = 0L;
    int n = nums.length;
    int i = 0;
    while (i < n) {
      int val = nums[i];
      int start = i;
      while (i < n && nums[i] == val) ++i;
      int cnt = i - start;
      long modv = ((long) val % KK + KK) % KK;
      for (int l = 1; l <= cnt; ++l) {
        long sum_mod = ((long) l * modv % KK + KK) % KK;
        if (sum_mod == 0) {
          subtract += (cnt - l);
        }
      }
    }
    return total - subtract;
  }
}
# @lc code=end