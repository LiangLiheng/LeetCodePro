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
        
        // Count inversions in first window [0, k-1]
        long long currentInversions = 0;
        for (int i = 0; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (nums[i] > nums[j]) {
                    currentInversions++;
                }
            }
        }
        
        long long minInversions = currentInversions;
        
        // Build multiset for first window
        multiset<int> window;
        for (int i = 0; i < k; i++) {
            window.insert(nums[i]);
        }
        
        // Slide the window from position 1 to n-k
        for (int i = 1; i <= n - k; i++) {
            int removed = nums[i - 1];
            int added = nums[i + k - 1];
            
            // Remove nums[i-1] from window
            // Count how many elements are smaller (these were inversions)
            auto it = window.find(removed);
            long long smallerCount = distance(window.begin(), it);
            currentInversions -= smallerCount;
            window.erase(it);
            
            // Add nums[i+k-1] to window
            // Count how many elements are larger (these create new inversions)
            long long largerCount = distance(window.upper_bound(added), window.end());
            currentInversions += largerCount;
            window.insert(added);
            
            minInversions = min(minInversions, currentInversions);
        }
        
        return minInversions;
    }
};
# @lc code=end