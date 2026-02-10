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
        
        // Try all 3^n partitions
        int totalPartitions = 1;
        for (int i = 0; i < n; i++) totalPartitions *= 3;
        
        for (int mask = 0; mask < totalPartitions; mask++) {
            vector<int> A, B, C;
            int tempMask = mask;
            
            // Assign each element to A, B, or C based on base-3 digit
            for (int i = 0; i < n; i++) {
                int group = tempMask % 3;
                tempMask /= 3;
                
                if (group == 0) A.push_back(nums[i]);
                else if (group == 1) B.push_back(nums[i]);
                else C.push_back(nums[i]);
            }
            
            // Calculate XOR(A)
            long long xorA = 0;
            for (int x : A) xorA ^= x;
            
            // Calculate AND(B)
            long long andB = 0;
            if (!B.empty()) {
                andB = B[0];
                for (size_t i = 1; i < B.size(); i++) {
                    andB &= B[i];
                }
            }
            
            // Calculate XOR(C)
            long long xorC = 0;
            for (int x : C) xorC ^= x;
            
            long long sum = xorA + andB + xorC;
            maxSum = max(maxSum, sum);
        }
        
        return maxSum;
    }
};
# @lc code=end