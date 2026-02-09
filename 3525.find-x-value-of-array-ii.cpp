#
# @lc app=leetcode id=3525 lang=cpp
#
# [3525] Find X Value of Array II
#
# @lc code=start
class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        vector<int> result;
        
        for (const auto& query : queries) {
            int index = query[0];
            int value = query[1];
            int start = query[2];
            int x = query[3];
            
            // Update nums[index] to value (this persists)
            nums[index] = value;
            
            // Count how many prefixes have product % k == x
            int count = 0;
            int product = 1;
            
            // Iterate through the subarray from start to end
            for (int i = start; i < nums.size(); i++) {
                product = (product * (nums[i] % k)) % k;
                if (product == x) {
                    count++;
                }
            }
            
            result.push_back(count);
        }
        
        return result;
    }
};
# @lc code=end