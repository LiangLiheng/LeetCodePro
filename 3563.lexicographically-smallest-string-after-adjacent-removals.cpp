#
# @lc app=leetcode id=3563 lang=cpp
#
# [3563] Lexicographically Smallest String After Adjacent Removals
#
# @lc code=start
class Solution {
public:
    unordered_map<string, string> memo;
    
    bool isConsecutive(char a, char b) {
        int diff = abs(a - b);
        return diff == 1 || diff == 25; // 25 for 'a' and 'z'
    }
    
    string lexicographicallySmallestString(string s) {
        if (memo.count(s)) return memo[s];
        
        string result = s;
        
        // Try all possible removals
        for (int i = 0; i < (int)s.length() - 1; i++) {
            if (isConsecutive(s[i], s[i+1])) {
                string next = s.substr(0, i) + s.substr(i + 2);
                string candidate = lexicographicallySmallestString(next);
                if (candidate < result) {
                    result = candidate;
                }
            }
        }
        
        memo[s] = result;
        return result;
    }
};
# @lc code=end