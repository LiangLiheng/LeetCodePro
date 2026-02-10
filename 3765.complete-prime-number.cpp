#
# @lc app=leetcode id=3765 lang=cpp
#
# [3765] Complete Prime Number
#
# @lc code=start
class Solution {
public:
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    bool completePrime(int num) {
        string s = to_string(num);
        int len = s.length();
        
        // Check all prefixes
        for (int i = 1; i <= len; i++) {
            string prefix = s.substr(0, i);
            int prefixNum = stoi(prefix);
            if (!isPrime(prefixNum)) return false;
        }
        
        // Check all suffixes
        for (int i = 0; i < len; i++) {
            string suffix = s.substr(i);
            int suffixNum = stoi(suffix);
            if (!isPrime(suffixNum)) return false;
        }
        
        return true;
    }
};
# @lc code=end