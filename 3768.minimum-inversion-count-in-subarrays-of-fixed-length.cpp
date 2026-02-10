#
# @lc app=leetcode id=3768 lang=cpp
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#
# @lc code=start
class Solution {
private:
    long long mergeCount(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp;
        int i = left, j = mid + 1;
        long long count = 0;
        
        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp.push_back(arr[i++]);
            } else {
                temp.push_back(arr[j++]);
                count += (mid - i + 1);
            }
        }
        
        while (i <= mid) temp.push_back(arr[i++]);
        while (j <= right) temp.push_back(arr[j++]);
        
        for (int i = 0; i < temp.size(); i++) {
            arr[left + i] = temp[i];
        }
        
        return count;
    }
    
    long long mergeSortCount(vector<int>& arr, int left, int right) {
        long long count = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;
            count += mergeSortCount(arr, left, mid);
            count += mergeSortCount(arr, mid + 1, right);
            count += mergeCount(arr, left, mid, right);
        }
        return count;
    }
    
public:
    long long minInversionCount(vector<int>& nums, int k) {
        int n = nums.size();
        if (k == 1) return 0;
        
        // Calculate inversions for first window using merge sort
        vector<int> temp(nums.begin(), nums.begin() + k);
        long long count = mergeSortCount(temp, 0, k - 1);
        long long minCount = count;
        
        // Sliding window with multiset
        multiset<int> window;
        for (int i = 0; i < k; i++) {
            window.insert(nums[i]);
        }
        
        for (int i = k; i < n; i++) {
            // Remove nums[i-k]
            int removed = nums[i - k];
            count -= distance(window.begin(), window.lower_bound(removed));
            window.erase(window.find(removed));
            
            // Add nums[i]
            int added = nums[i];
            count += distance(window.upper_bound(added), window.end());
            window.insert(added);
            
            minCount = min(minCount, count);
        }
        
        return minCount;
    }
};
# @lc code=end