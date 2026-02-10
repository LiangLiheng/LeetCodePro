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
        
        int count = 0;
        
        // Find bit length of n
        int bit_len = 64 - __builtin_clzll(n);
        
        // Count length 1: "0" and "1"
        count = 2;
        
        // Count lengths 2 to bit_len - 1
        for (int len = 2; len < bit_len; len++) {
            if (len % 2 == 1) {
                // Odd length: 2^((len-1)/2) palindromes
                count += (1 << ((len - 1) / 2));
            } else {
                // Even length: 2^(len/2-1) palindromes
                count += (1 << (len / 2 - 1));
            }
        }
        
        // Count palindromes of length bit_len that are <= n
        count += countPalindromesOfLengthLE(bit_len, n);
        
        return count;
    }
    
private:
    int countPalindromesOfLengthLE(int len, long long n) {
        int count = 0;
        int half_len = (len + 1) / 2;
        
        // Generate all possible first halves
        long long start = 1LL << (half_len - 1);
        long long end = 1LL << half_len;
        
        for (long long half = start; half < end; half++) {
            long long palindrome = makePalindrome(half, len);
            if (palindrome <= n) {
                count++;
            } else {
                break; // Palindromes are in increasing order
            }
        }
        
        return count;
    }
    
    long long makePalindrome(long long half, int len) {
        long long result = half;
        long long temp = half;
        
        // Skip middle bit for odd length
        if (len % 2 == 1) {
            temp >>= 1;
        }
        
        // Mirror the remaining bits
        while (temp > 0) {
            result = (result << 1) | (temp & 1);
            temp >>= 1;
        }
        
        return result;
    }
};
# @lc code=end