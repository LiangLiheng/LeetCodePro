#
# @lc app=leetcode id=3448 lang=cpp
#
# [3448] Count Substrings Divisible By Last Digit
#
# @lc code=start
class Solution {
public:
    long long countSubstrings(string s) {
        int n = s.length();
        long long count = 0;
        
        for (int i = 0; i < n; i++) {
            int d = s[i] - '0';
            if (d == 0) continue; // Skip zeros (non-zero last digit required)
            
            long long mod_value = 0;
            long long power_of_10 = 1; // 10^(i-j) mod d
            
            for (int j = i; j >= 0; j--) {
                int digit = s[j] - '0';
                mod_value = ((long long)digit * power_of_10 % d + mod_value) % d;
                if (mod_value == 0) count++;
                power_of_10 = (power_of_10 * 10) % d;
            }
        }
        
        return count;
    }
};
# @lc code=end