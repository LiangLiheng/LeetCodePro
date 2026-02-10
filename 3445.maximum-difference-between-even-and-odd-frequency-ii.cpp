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
        
        // Try all possible substrings of length >= k
        for (int i = 0; i < n; i++) {
            unordered_map<char, int> freq;
            
            for (int j = i; j < n; j++) {
                freq[s[j]]++;
                
                // Check if substring length >= k
                if (j - i + 1 >= k) {
                    int maxOdd = INT_MIN;
                    int minEven = INT_MAX;
                    
                    // Find max odd frequency and min non-zero even frequency
                    for (const auto& p : freq) {
                        if (p.second % 2 == 1) {
                            maxOdd = max(maxOdd, p.second);
                        } else if (p.second > 0) {
                            minEven = min(minEven, p.second);
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