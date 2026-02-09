#
# @lc app=leetcode id=3458 lang=cpp
#
# [3458] Select K Disjoint Special Substrings
#
# @lc code=start
class Solution {
public:
    bool maxSubstringLength(string s, int k) {
        int n = s.length();
        
        if (k == 0) return true;
        
        // Compute first and last occurrence of each character
        vector<int> first(26, -1), last(26, -1);
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first[c] == -1) first[c] = i;
            last[c] = i;
        }
        
        // Find all special substrings
        vector<pair<int, int>> specials; // {end, start}
        
        for (int i = 0; i < n; i++) {
            int maxRight = i;
            int minLeft = i;
            
            for (int j = i; j < n; j++) {
                int c = s[j] - 'a';
                maxRight = max(maxRight, last[c]);
                minLeft = min(minLeft, first[c]);
                
                // Check if [i, j] is a special substring
                if (minLeft >= i && maxRight == j) {
                    // Exclude entire string
                    if (i > 0 || j < n - 1) {
                        specials.push_back({j, i});
                    }
                }
            }
        }
        
        // Sort by ending position for greedy selection
        sort(specials.begin(), specials.end());
        
        // Greedily select maximum disjoint substrings
        int count = 0;
        int lastEnd = -1;
        
        for (auto& p : specials) {
            int end = p.first;
            int start = p.second;
            
            if (start > lastEnd) {
                count++;
                lastEnd = end;
                if (count >= k) return true;
            }
        }
        
        return count >= k;
    }
};
# @lc code=end