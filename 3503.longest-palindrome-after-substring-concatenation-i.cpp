#
# @lc app=leetcode id=3503 lang=cpp
#
# [3503] Longest Palindrome After Substring Concatenation I
#
# @lc code=start
class Solution {
public:
    int longestPalindrome(string s, string t) {
        int maxLen = 0;
        
        // Helper function to check if a string is a palindrome
        auto isPalindrome = [](const string& str) {
            int left = 0, right = str.size() - 1;
            while (left < right) {
                if (str[left] != str[right]) return false;
                left++;
                right--;
            }
            return true;
        };
        
        // Try all possible combinations
        // i, j represent substring s[i..j), where j can be i (empty substring)
        // k, l represent substring t[k..l), where l can be k (empty substring)
        
        for (int i = 0; i <= s.size(); i++) {
            for (int j = i; j <= s.size(); j++) {
                string sub_s = s.substr(i, j - i);
                for (int k = 0; k <= t.size(); k++) {
                    for (int l = k; l <= t.size(); l++) {
                        string sub_t = t.substr(k, l - k);
                        // Skip the case where both are empty
                        if (sub_s.empty() && sub_t.empty()) continue;
                        string combined = sub_s + sub_t;
                        if (isPalindrome(combined)) {
                            maxLen = max(maxLen, (int)combined.size());
                        }
                    }
                }
            }
        }
        
        return maxLen;
    }
};
# @lc code=end