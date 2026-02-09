#
# @lc app=leetcode id=3399 lang=cpp
#
# [3399] Smallest Substring With Identical Characters II
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        
        // Find initial max consecutive length
        int maxConsec = 1;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            maxConsec = max(maxConsec, j - i);
            i = j;
        }
        
        // Special case: check if we can achieve alternating pattern (length 1)
        int flipsPattern1 = 0, flipsPattern2 = 0;
        for (int i = 0; i < n; i++) {
            char expected1 = '0' + (i % 2);  // '0' for even, '1' for odd
            char expected2 = '1' - (i % 2);  // '1' for even, '0' for odd
            if (s[i] != expected1) flipsPattern1++;
            if (s[i] != expected2) flipsPattern2++;
        }
        int minFlipsAlt = min(flipsPattern1, flipsPattern2);
        
        if (numOps >= minFlipsAlt) {
            return 1;
        }
        
        // Binary search for the minimum achievable length
        int left = 2, right = maxConsec;
        int result = maxConsec;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canAchieve(s, mid, numOps)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
private:
    bool canAchieve(string s, int k, int numOps) {
        int n = s.length();
        int flips = 0;
        int i = 0;
        
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            int len = j - i;
            if (len > k) {
                flips += len / (k + 1);
            }
            i = j;
        }
        
        return flips <= numOps;
    }
};
# @lc code=end