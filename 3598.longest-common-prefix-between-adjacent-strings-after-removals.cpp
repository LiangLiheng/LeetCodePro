#
# @lc app=leetcode id=3598 lang=cpp
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#
# @lc code=start
class Solution {
public:
    int commonPrefixLength(const string& s1, const string& s2) {
        int len = min(s1.length(), s2.length());
        int count = 0;
        for (int i = 0; i < len; i++) {
            if (s1[i] == s2[i]) {
                count++;
            } else {
                break;
            }
        }
        return count;
    }
    
    vector<int> longestCommonPrefix(vector<string>& words) {
        int n = words.size();
        vector<int> answer(n, 0);
        
        if (n <= 1) {
            return answer; // No adjacent pairs possible
        }
        
        // Pre-compute prefix lengths for all adjacent pairs
        vector<int> prefixLen(n - 1);
        for (int i = 0; i < n - 1; i++) {
            prefixLen[i] = commonPrefixLength(words[i], words[i + 1]);
        }
        
        for (int removeIdx = 0; removeIdx < n; removeIdx++) {
            int maxLen = 0;
            
            // Check all original pairs except those involving removeIdx
            for (int pairIdx = 0; pairIdx < n - 1; pairIdx++) {
                if (pairIdx == removeIdx || pairIdx + 1 == removeIdx) {
                    continue; // This pair involves the removed element
                }
                maxLen = max(maxLen, prefixLen[pairIdx]);
            }
            
            // If we remove a middle element, we get a new pair
            if (removeIdx > 0 && removeIdx < n - 1) {
                int newPairLen = commonPrefixLength(words[removeIdx - 1], words[removeIdx + 1]);
                maxLen = max(maxLen, newPairLen);
            }
            
            answer[removeIdx] = maxLen;
        }
        
        return answer;
    }
};
# @lc code=end