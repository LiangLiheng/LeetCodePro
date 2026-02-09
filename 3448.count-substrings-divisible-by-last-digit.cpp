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
            if (s[i] == '0') continue; // Skip if last digit is 0
            
            int d = s[i] - '0';
            int num_mod = 0;
            int power_mod = 1;
            
            for (int j = i; j >= 0; j--) {
                num_mod = (num_mod + (s[j] - '0') * power_mod) % d;
                if (num_mod == 0) {
                    count++;
                }
                power_mod = (power_mod * 10) % d;
            }
        }
        
        return count;
    }
};
# @lc code=end