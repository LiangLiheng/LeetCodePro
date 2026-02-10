#
# @lc app=leetcode id=3504 lang=cpp
#
# [3504] Longest Palindrome After Substring Concatenation II
#
# @lc code=start
class Solution {
public:
    bool isPalindrome(const string& str) {
        int n = str.length();
        for (int i = 0; i < n / 2; i++) {
            if (str[i] != str[n - 1 - i]) {
                return false;
            }
        }
        return true;
    }
    
    int longestPalindrome(string s, string t) {
        int maxLen = 0;
        int n = s.length();
        int m = t.length();
        
        // Try all possible substrings from s and t
        for (int si = 0; si <= n; si++) {
            for (int slen = 0; slen <= n - si; slen++) {
                for (int ti = 0; ti <= m; ti++) {
                    for (int tlen = 0; tlen <= m - ti; tlen++) {
                        // Skip if length can't improve current max
                        if (slen + tlen <= maxLen) continue;
                        
                        // Create concatenation
                        string concat = s.substr(si, slen) + t.substr(ti, tlen);
                        
                        // Check if palindrome
                        if (isPalindrome(concat)) {
                            maxLen = concat.length();
                        }
                    }
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end