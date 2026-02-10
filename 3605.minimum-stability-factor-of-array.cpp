#
# @lc app=leetcode id=3605 lang=cpp
#
# [3605] Minimum Stability Factor of Array
#
# @lc code=start
class Solution {
public:
    int gcd(int a, int b) {
        while (b) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    
    bool canAchieve(vector<int>& nums, int maxC, int L) {
        int n = nums.size();
        
        if (L == 0) {
            // Need to make all elements < 2
            int count = 0;
            for (int x : nums) {
                if (x >= 2) count++;
            }
            return count <= maxC;
        }
        
        int modifications = 0;
        int i = 0;
        
        while (i < n) {
            if (nums[i] < 2) {
                i++;
                continue;
            }
            
            // Find the longest stable subarray starting at i
            int g = nums[i];
            int j = i + 1;
            
            while (j < n) {
                int new_g = gcd(g, nums[j]);
                if (new_g < 2) break;
                g = new_g;
                j++;
            }
            
            // Stable subarray is [i, j-1] with length j-i
            int len = j - i;
            if (len > L) {
                // Need to place modifications to break it
                int num_mods = len / (L + 1);
                modifications += num_mods;
                if (modifications > maxC) return false;
            }
            
            i = j;
        }
        
        return true;
    }
    
    int minStable(vector<int>& nums, int maxC) {
        int n = nums.size();
        
        // Binary search on the answer
        int left = 0, right = n;
        int answer = n;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(nums, maxC, mid)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return answer;
    }
};
# @lc code=end