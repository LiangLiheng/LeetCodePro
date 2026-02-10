#
# @lc app=leetcode id=3509 lang=cpp
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#
# @lc code=start
class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        // dp[(sum, parity)] = max_product
        // parity: 0=even length, 1=odd length
        map<pair<int,int>, int> dp;
        
        for (int num : nums) {
            map<pair<int,int>, int> newDp = dp;
            
            // Start new subsequence
            if (num <= limit) {
                pair<int,int> state(num, 1);
                newDp[state] = max(newDp[state], num);
            }
            
            // Extend existing subsequences
            for (auto it = dp.begin(); it != dp.end(); ++it) {
                int sum = it->first.first;
                int parity = it->first.second;
                int prod = it->second;
                
                int newSum = (parity == 0) ? (sum + num) : (sum - num);
                long long newProd = (long long)prod * num;
                
                if (newProd <= limit) {
                    pair<int,int> newState(newSum, 1 - parity);
                    newDp[newState] = max(newDp[newState], (int)newProd);
                }
            }
            
            dp = newDp;
        }
        
        // Find answer
        int ans = -1;
        for (auto it = dp.begin(); it != dp.end(); ++it) {
            if (it->first.first == k) {
                ans = max(ans, it->second);
            }
        }
        
        return ans;
    }
};
# @lc code=end