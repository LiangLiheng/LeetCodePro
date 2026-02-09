#
# @lc app=leetcode id=3503 lang=cpp
#
# [3503] Longest Palindrome After Substring Concatenation I
#
# @lc code=start
class Solution {
public:
    bool isPalindrome(string s) {
        int n = s.length();
        for (int i = 0; i < n / 2; i++) {
            if (s[i] != s[n - 1 - i]) {
                return false;
            }
        }
        return true;
    }
    
    int longestPalindrome(string s, string t) {
        int maxLen = 0;
        int n = s.length();
        int m = t.length();
        
        // Try all substrings from s (including empty)
        for (int i = 0; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                string subs = s.substr(i, j - i);
                
                // Try all substrings from t (including empty)
                for (int k = 0; k <= m; k++) {
                    for (int l = k; l <= m; l++) {
                        string subt = t.substr(k, l - k);
                        string concat = subs + subt;
                        
                        // Check if palindrome
                        if (isPalindrome(concat)) {
                            maxLen = max(maxLen, (int)concat.length());
                        }
                    }
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end