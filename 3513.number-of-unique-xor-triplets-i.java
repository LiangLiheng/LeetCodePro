#
# @lc app=leetcode id=3513 lang=java
#
# [3513] Number of Unique XOR Triplets I
#
# @lc code=start
import java.util.*;
class Solution {
    public int uniqueXorTriplets(int[] nums) {
        int n = nums.length;
        Set<Integer> xorSet = new HashSet<>();
        int[] prefixXor = new int[n + 1];
        prefixXor[0] = 0;
        for (int i = 0; i < n; i++) {
            prefixXor[i + 1] = prefixXor[i] ^ nums[i];
        }
        // Enumerate all subarrays to get all possible triplet XORs efficiently
        for (int i = 0; i < n; i++) {
            for (int k = i; k < n; k++) {
                xorSet.add(prefixXor[k + 1] ^ prefixXor[i]);
            }
        }
        return xorSet.size();
    }
}
# @lc code=end