#
# @lc app=leetcode id=3677 lang=cpp
#
# [3677] Count Binary Palindromic Numbers
#
# @lc code=start
class Solution {
public:
    int countBinaryPalindromes(long long n) {
        if (n == 0) return 1;
        
        // Get binary representation of n
        string binary = "";
        long long temp = n;
        while (temp > 0) {
            binary = (char)('0' + (temp % 2)) + binary;
            temp /= 2;
        }
        
        int len = binary.length();
        int count = 1; // Count 0
        
        // Count palindromes with length < len
        for (int l = 1; l < len; l++) {
            if (l == 1) {
                count += 1; // Only "1"
            } else if (l % 2 == 1) {
                // Odd length: 2^((l-1)/2) palindromes
                count += (1 << ((l - 1) / 2));
            } else {
                // Even length: 2^(l/2 - 1) palindromes
                count += (1 << (l / 2 - 1));
            }
        }
        
        // Count palindromes with length = len and value <= n
        int halfLen = (len + 1) / 2;
        
        for (long long i = 0; i < (1LL << (halfLen - 1)); i++) {
            // Construct the first half
            string palin = "1";
            
            // Add the remaining bits of the first half
            for (int j = halfLen - 2; j >= 0; j--) {
                palin += ((i >> j) & 1) ? '1' : '0';
            }
            
            // Mirror to create full palindrome
            if (len % 2 == 1) {
                // Odd length: mirror all except the last bit (middle bit)
                for (int j = halfLen - 2; j >= 0; j--) {
                    palin += palin[j];
                }
            } else {
                // Even length: mirror all bits
                for (int j = halfLen - 1; j >= 0; j--) {
                    palin += palin[j];
                }
            }
            
            // Check if palindrome <= n
            if (palin <= binary) {
                count++;
            }
        }
        
        return count;
    }
};
# @lc code=end