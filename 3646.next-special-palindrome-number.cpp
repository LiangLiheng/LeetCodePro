#
# @lc app=leetcode id=3646 lang=cpp
#
# [3646] Next Special Palindrome Number
#
# @lc code=start
class Solution {
public:
    long long specialPalindrome(long long n) {
        vector<long long> specials;
        
        // Generate all valid special palindromes
        // Try all subsets of {1,2,3,4,5,6,7,8,9}
        for (int mask = 1; mask < (1 << 9); mask++) {
            vector<int> digits;
            int oddCount = 0;
            
            for (int d = 1; d <= 9; d++) {
                if (mask & (1 << (d - 1))) {
                    digits.push_back(d);
                    if (d % 2 == 1) oddCount++;
                }
            }
            
            // Can only form palindrome if at most one odd digit
            if (oddCount > 1) continue;
            
            // Construct the palindrome
            string palin = constructPalindrome(digits);
            if (!palin.empty()) {
                specials.push_back(stoll(palin));
            }
        }
        
        sort(specials.begin(), specials.end());
        
        // Find first special > n
        for (long long sp : specials) {
            if (sp > n) return sp;
        }
        
        return -1;
    }
    
private:
    string constructPalindrome(vector<int>& digits) {
        string left = "";
        string middle = "";
        
        for (int d : digits) {
            if (d % 2 == 1) {
                // Odd digit: one in middle, rest split
                middle = string(1, '0' + d);
                for (int i = 0; i < (d - 1) / 2; i++) {
                    left += ('0' + d);
                }
            } else {
                // Even digit: split evenly
                for (int i = 0; i < d / 2; i++) {
                    left += ('0' + d);
                }
            }
        }
        
        // Sort left to get smallest palindrome
        sort(left.begin(), left.end());
        
        string right = left;
        reverse(right.begin(), right.end());
        
        return left + middle + right;
    }
};
# @lc code=end