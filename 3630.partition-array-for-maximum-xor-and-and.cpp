#
# @lc app=leetcode id=3630 lang=cpp
#
# [3630] Partition Array for Maximum XOR and AND
#
# @lc code=start
class Solution {
public:
    long long maximizeXorAndXor(vector<int>& nums) {
        int n = nums.size();
        long long maxSum = 0;
        
        // Calculate total number of partitions (3^n)
        int totalPartitions = 1;
        for (int i = 0; i < n; i++) {
            totalPartitions *= 3;
        }
        
        // Try all possible partitions using ternary representation
        for (int mask = 0; mask < totalPartitions; mask++) {
            int temp = mask;
            long long xorA = 0, xorC = 0;
            long long andB = 0;
            bool hasB = false;
            
            // Decode ternary mask: 0=A, 1=B, 2=C
            for (int i = 0; i < n; i++) {
                int group = temp % 3;
                temp /= 3;
                
                if (group == 0) {
                    xorA ^= nums[i];
                } else if (group == 1) {
                    if (!hasB) {
                        andB = nums[i];
                        hasB = true;
                    } else {
                        andB &= nums[i];
                    }
                } else {
                    xorC ^= nums[i];
                }
            }
            
            long long sum = xorA + andB + xorC;
            maxSum = max(maxSum, sum);
        }
        
        return maxSum;
    }
};
# @lc code=end