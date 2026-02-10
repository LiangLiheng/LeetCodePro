#
# @lc app=leetcode id=3768 lang=cpp
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#
# @lc code=start
class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == 1) return 0;
        
        // Calculate inversions for the first window
        long long current = 0;
        multiset<int> window;
        
        for (int i = 0; i < k; i++) {
            // Count how many elements in window are greater than nums[i]
            current += distance(window.upper_bound(nums[i]), window.end());
            window.insert(nums[i]);
        }
        
        long long minInv = current;
        
        // Slide the window
        for (int i = k; i < n; i++) {
            // Remove nums[i-k]
            int removed = nums[i - k];
            // Count smaller elements in the remaining window
            current -= distance(window.begin(), window.lower_bound(removed));
            window.erase(window.find(removed));
            
            // Add nums[i]
            int added = nums[i];
            // Count larger elements in the current window
            current += distance(window.upper_bound(added), window.end());
            window.insert(added);
            
            minInv = min(minInv, current);
        }
        
        return minInv;
    }
};
# @lc code=end