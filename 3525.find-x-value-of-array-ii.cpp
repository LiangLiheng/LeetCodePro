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
        
        for (auto& query : queries) {
            int index = query[0];
            int value = query[1];
            int start = query[2];
            int x = query[3];
            
            // Update nums[index]
            nums[index] = value;
            
            // Count valid suffix removals
            int count = 0;
            int n = nums.size();
            
            // Compute products incrementally from start to each possible end
            long long product = 1;
            for (int end = start; end < n; end++) {
                product = (product * (nums[end] % k)) % k;
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