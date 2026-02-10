#
# @lc app=leetcode id=3510 lang=cpp
#
# [3510] Minimum Pair Removal to Sort Array II
#
# @lc code=start
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int operations = 0;
        
        while (!isNonDecreasing(nums)) {
            // Find the leftmost adjacent pair with minimum sum
            int minSum = INT_MAX;
            int minIdx = -1;
            
            for (int i = 0; i < nums.size() - 1; i++) {
                int sum = nums[i] + nums[i+1];
                if (sum < minSum) {
                    minSum = sum;
                    minIdx = i;
                }
            }
            
            // Replace the pair with their sum
            nums[minIdx] = minSum;
            nums.erase(nums.begin() + minIdx + 1);
            operations++;
        }
        
        return operations;
    }
    
private:
    bool isNonDecreasing(const vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i-1]) {
                return false;
            }
        }
        return true;
    }
};
# @lc code=end