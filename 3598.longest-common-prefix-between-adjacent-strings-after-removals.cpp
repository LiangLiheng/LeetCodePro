#
# @lc app=leetcode id=3598 lang=cpp
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#
# @lc code=start
class Solution {
public:
    int computeLCP(const string& s1, const string& s2) {
        int len = 0;
        int minLen = min(s1.length(), s2.length());
        for (int i = 0; i < minLen; i++) {
            if (s1[i] == s2[i]) {
                len++;
            } else {
                break;
            }
        }
        return len;
    }
    
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        vector<int> answer(n, 0);
        
        if (n <= 1) {
            return answer;
        }
        
        // Precompute LCP for all adjacent pairs
        vector<int> lcp(n - 1);
        for (int i = 0; i < n - 1; i++) {
            lcp[i] = computeLCP(words[i], words[i + 1]);
        }
        
        // For each removal
        for (int i = 0; i < n; i++) {
            int maxLCP = 0;
            
            // Check all existing pairs that don't involve index i
            for (int j = 0; j < n - 1; j++) {
                if (j != i - 1 && j != i) {
                    maxLCP = max(maxLCP, lcp[j]);
                }
            }
            
            // Check new pair if both neighbors exist
            if (i > 0 && i < n - 1) {
                int newLCP = computeLCP(words[i - 1], words[i + 1]);
                maxLCP = max(maxLCP, newLCP);
            }
            
            answer[i] = maxLCP;
        }
        
        return answer;
    }
};
# @lc code=end