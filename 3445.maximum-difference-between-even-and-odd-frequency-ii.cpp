#
# @lc app=leetcode id=3445 lang=cpp
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#
# @lc code=start
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.length();
        int maxDiff = INT_MIN;
        
        // Try all substrings of length >= k
        for (int i = 0; i < n - k + 1; i++) {
            vector<int> freq(5, 0); // For digits 0-4
            
            for (int j = i; j < n; j++) {
                freq[s[j] - '0']++;
                
                // Only consider substrings of length >= k
                if (j - i + 1 >= k) {
                    // Find max odd frequency and min even frequency
                    int maxOdd = INT_MIN;
                    int minEven = INT_MAX;
                    
                    for (int f : freq) {
                        if (f > 0) {
                            if (f % 2 == 1) {
                                maxOdd = max(maxOdd, f);
                            } else {
                                minEven = min(minEven, f);
                            }
                        }
                    }
                    
                    // If we have both odd and even frequencies
                    if (maxOdd != INT_MIN && minEven != INT_MAX) {
                        maxDiff = max(maxDiff, maxOdd - minEven);
                    }
                }
            }
        }
        
        return maxDiff;
    }
};
# @lc code=end