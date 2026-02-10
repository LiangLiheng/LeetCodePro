#
# @lc app=leetcode id=3434 lang=cpp
#
# [3434] Maximum Frequency After Subarray Operation
#
# @lc code=start
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        int n = nums.size();
        
        // Count initial frequency of k
        int initialCount = 0;
        for (int num : nums) {
            if (num == k) initialCount++;
        }
        
        int maxResult = initialCount;
        
        // Get unique values to try converting
        unordered_set<int> uniqueVals(nums.begin(), nums.end());
        
        // Try converting each unique value v to k
        for (int v : uniqueVals) {
            if (v == k) continue;  // Skip if already k
            
            // Create score array:
            // +1 for elements equal to v (can be converted to k)
            // -1 for elements equal to k (will be changed away from k)
            // 0 for other elements
            vector<int> score(n);
            for (int i = 0; i < n; i++) {
                if (nums[i] == v) {
                    score[i] = 1;
                } else if (nums[i] == k) {
                    score[i] = -1;
                } else {
                    score[i] = 0;
                }
            }
            
            // Use Kadane's algorithm to find maximum subarray sum
            // This represents the best gain from selecting a subarray
            int maxSum = 0;
            int currentSum = 0;
            for (int s : score) {
                currentSum = max(0, currentSum + s);
                maxSum = max(maxSum, currentSum);
            }
            
            // Total frequency = initial count + gain from best subarray
            maxResult = max(maxResult, initialCount + maxSum);
        }
        
        return maxResult;
    }
};
# @lc code=end