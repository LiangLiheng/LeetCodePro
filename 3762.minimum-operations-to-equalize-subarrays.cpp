#
# @lc app=leetcode id=3762 lang=cpp
#
# [3762] Minimum Operations to Equalize Subarrays
#
# @lc code=start
class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        vector<long long> result;
        
        for (auto& query : queries) {
            int left = query[0];
            int right = query[1];
            
            // Extract subarray
            vector<long long> subarray;
            for (int i = left; i <= right; i++) {
                subarray.push_back(nums[i]);
            }
            
            // Check if all elements have same remainder mod k
            long long firstRemainder = subarray[0] % k;
            bool possible = true;
            for (long long val : subarray) {
                if (val % k != firstRemainder) {
                    possible = false;
                    break;
                }
            }
            
            if (!possible) {
                result.push_back(-1);
                continue;
            }
            
            // Sort to find median
            sort(subarray.begin(), subarray.end());
            
            // Find median
            int n = subarray.size();
            long long median = subarray[n / 2];
            
            // Calculate total operations
            long long operations = 0;
            for (long long val : subarray) {
                operations += abs(val - median) / k;
            }
            
            result.push_back(operations);
        }
        
        return result;
    }
};
# @lc code=end