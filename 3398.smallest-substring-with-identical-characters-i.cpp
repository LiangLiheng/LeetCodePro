#
# @lc app=leetcode id=3398 lang=cpp
#
# [3398] Smallest Substring With Identical Characters I
#
# @lc code=start
class Solution {
public:
    int minLength(string s, int numOps) {
        int n = s.length();
        
        // Helper function to count flips needed for max length k
        auto countFlips = [&](int k) -> int {
            int flips = 0;
            int i = 0;
            while (i < n) {
                int j = i;
                // Find consecutive run of same character
                while (j < n && s[j] == s[i]) {
                    j++;
                }
                int len = j - i;
                // If run length exceeds k, calculate flips needed
                if (len > k) {
                    flips += len / (k + 1);
                }
                i = j;
            }
            return flips;
        };
        
        // Binary search on the answer
        int left = 1, right = n;
        int ans = n;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (countFlips(mid) <= numOps) {
                ans = mid;
                right = mid - 1;  // Try smaller
            } else {
                left = mid + 1;   // Need larger
            }
        }
        
        return ans;
    }
};
# @lc code=end