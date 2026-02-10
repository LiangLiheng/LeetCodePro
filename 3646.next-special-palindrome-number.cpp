#include <set>
#include <vector>
#include <algorithm>
#include <string>

#
# @lc app=leetcode id=3646 lang=cpp
#
# [3646] Next Special Palindrome Number
#
# @lc code=start
class Solution {
public:
    long long specialPalindrome(long long n) {
        std::set<long long> specialPalindromes;
        
        // Try all subsets of digits 1-9
        for (int mask = 1; mask < (1 << 9); mask++) {
            std::vector<int> digits;
            int totalLength = 0;
            int oddCount = 0;
            
            for (int d = 1; d <= 9; d++) {
                if (mask & (1 << (d - 1))) {
                    digits.push_back(d);
                    totalLength += d;
                    if (d % 2 == 1) oddCount++;
                }
            }
            
            // Check if this subset can form a palindrome
            if (oddCount > 1) continue;
            if (totalLength > 18) continue;
            
            // Generate the smallest palindrome
            std::string palindrome = generateSmallestPalindrome(digits, oddCount);
            specialPalindromes.insert(std::stoll(palindrome));
        }
        
        // Find the smallest special palindrome > n
        auto it = specialPalindromes.upper_bound(n);
        return (it != specialPalindromes.end()) ? *it : n + 1;
    }
    
private:
    std::string generateSmallestPalindrome(std::vector<int>& digits, int oddCount) {
        std::vector<int> leftHalf;
        int middle = -1;
        
        if (oddCount == 1) {
            for (int d : digits) {
                if (d % 2 == 1) {
                    middle = d;
                    for (int i = 0; i < (d - 1) / 2; i++)
                        leftHalf.push_back(d);
                } else {
                    for (int i = 0; i < d / 2; i++)
                        leftHalf.push_back(d);
                }
            }
        } else {
            for (int d : digits) {
                for (int i = 0; i < d / 2; i++)
                    leftHalf.push_back(d);
            }
        }
        
        std::sort(leftHalf.begin(), leftHalf.end());
        
        std::string result;
        for (int d : leftHalf)
            result += char('0' + d);
        if (middle != -1)
            result += char('0' + middle);
        for (int i = leftHalf.size() - 1; i >= 0; i--)
            result += char('0' + leftHalf[i]);
        
        return result;
    }
};
# @lc code=end