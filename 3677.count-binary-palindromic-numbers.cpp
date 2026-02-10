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
        
        // Find bit length of n
        int maxLen = 0;
        long long temp = n;
        while (temp > 0) {
            maxLen++;
            temp >>= 1;
        }
        
        int count = 0;
        
        // Count palindromes with length < maxLen
        if (maxLen > 1) {
            count += 2; // Length 1: "0" and "1"
            
            // For each length from 2 to maxLen-1
            for (int len = 2; len < maxLen; len++) {
                if (len % 2 == 0) {
                    // Even length: 2^(len/2-1) palindromes
                    count += (1 << (len / 2 - 1));
                } else {
                    // Odd length: 2^((len-1)/2) palindromes
                    count += (1 << ((len - 1) / 2));
                }
            }
        }
        
        // Count palindromes with length == maxLen and value <= n
        if (maxLen == 1) {
            count = n + 1; // Both 0 and 1 (or just 0 if n=0, handled above)
        } else {
            count += countPalindromesOfLength(maxLen, n);
        }
        
        return count;
    }
    
private:
    // Count palindromes of specific length that are <= maxVal
    int countPalindromesOfLength(int len, long long maxVal) {
        bool isOdd = (len % 2 == 1);
        int halfLen = isOdd ? (len + 1) / 2 : len / 2;
        
        long long minHalf = 1LL << (halfLen - 1); // Minimum half (first bit is 1)
        long long maxHalf = (1LL << halfLen) - 1; // Maximum half
        
        // Binary search for the maximum valid half
        long long left = minHalf, right = maxHalf;
        long long result = minHalf - 1;
        
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            long long palindrome = createPalindrome(mid, isOdd);
            
            if (palindrome <= maxVal) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        if (result < minHalf) return 0;
        return (int)(result - minHalf + 1);
    }
    
    // Create palindrome from first half
    long long createPalindrome(long long half, bool isOdd) {
        long long result = half;
        if (isOdd) half >>= 1; // Skip middle bit for odd length
        
        // Mirror the remaining bits
        while (half > 0) {
            result = (result << 1) | (half & 1);
            half >>= 1;
        }
        return result;
    }
};
# @lc code=end