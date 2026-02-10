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
            int l = query[0];
            int r = query[1];
            
            // If subarray has only one element, no operations needed
            if (l == r) {
                result.push_back(0);
                continue;
            }
            
            // Check if all elements have the same remainder modulo k
            long long remainder = nums[l] % k;
            bool possible = true;
            
            vector<long long> coefficients;
            for (int i = l; i <= r; i++) {
                if (nums[i] % k != remainder) {
                    possible = false;
                    break;
                }
                // Each nums[i] = remainder + coefficient * k
                long long coefficient = (nums[i] - remainder) / k;
                coefficients.push_back(coefficient);
            }
            
            if (!possible) {
                result.push_back(-1);
                continue;
            }
            
            // Sort to find median
            sort(coefficients.begin(), coefficients.end());
            
            // Use median as target coefficient
            long long median = coefficients[coefficients.size() / 2];
            
            // Calculate total operations
            long long ops = 0;
            for (long long coef : coefficients) {
                ops += abs(coef - median);
            }
            
            result.push_back(ops);
        }
        
        return result;
    }
};
# @lc code=end