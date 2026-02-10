#
# @lc app=leetcode id=3734 lang=cpp
#
# [3734] Lexicographically Smallest Palindromic Permutation Greater Than Target
#
# @lc code=start
class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.length();
        vector<int> freq(26, 0);
        
        // Count character frequencies
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Check if palindrome is possible
        int oddCount = 0;
        char middle = '\0';
        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2 == 1) {
                oddCount++;
                middle = 'a' + i;
            }
        }
        
        // Palindrome not possible if more than one odd frequency
        if (oddCount > 1) {
            return "";
        }
        
        // Build the left half using half of each character's frequency
        vector<char> half;
        for (int i = 0; i < 26; i++) {
            int count = freq[i] / 2;
            for (int j = 0; j < count; j++) {
                half.push_back('a' + i);
            }
        }
        
        // Sort to start from lexicographically smallest permutation
        sort(half.begin(), half.end());
        
        // Try all permutations of left half in lexicographic order
        do {
            // Build palindrome from current permutation
            string palindrome = buildPalindrome(half, middle);
            
            // Return first palindrome greater than target
            if (palindrome > target) {
                return palindrome;
            }
        } while (next_permutation(half.begin(), half.end()));
        
        // No valid palindrome found
        return "";
    }
    
private:
    string buildPalindrome(const vector<char>& half, char middle) {
        string result(half.begin(), half.end());
        
        // Add middle character if exists (odd length palindrome)
        if (middle != '\0') {
            result += middle;
        }
        
        // Add reversed left half to form palindrome
        for (int i = half.size() - 1; i >= 0; i--) {
            result += half[i];
        }
        
        return result;
    }
};
# @lc code=end