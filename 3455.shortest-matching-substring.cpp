#
# @lc app=leetcode id=3455 lang=cpp
#
# [3455] Shortest Matching Substring
#
# @lc code=start
class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        // Split pattern by '*'
        vector<string> parts;
        string current = "";
        for (char c : p) {
            if (c == '*') {
                parts.push_back(current);
                current = "";
            } else {
                current += c;
            }
        }
        parts.push_back(current);
        
        string prefix = parts[0];
        string middle = parts[1];
        string suffix = parts[2];
        
        int minLen = INT_MAX;
        int n = s.length();
        
        // Try all possible substrings
        for (int i = 0; i <= n; i++) {
            for (int len = 0; i + len <= n; len++) {
                string sub = s.substr(i, len);
                if (matches(sub, prefix, middle, suffix)) {
                    minLen = min(minLen, len);
                    break; // Found shortest for this starting position
                }
            }
        }
        
        return minLen == INT_MAX ? -1 : minLen;
    }
    
private:
    bool matches(const string& s, const string& prefix, const string& middle, const string& suffix) {
        int n = s.length();
        int p1 = prefix.length();
        int p2 = middle.length();
        int p3 = suffix.length();
        
        // s must be at least p1 + p2 + p3 long
        if (n < p1 + p2 + p3) return false;
        
        // Check prefix
        if (s.substr(0, p1) != prefix) return false;
        
        // Check suffix
        if (s.substr(n - p3, p3) != suffix) return false;
        
        // Check if middle exists after prefix and before suffix
        for (int i = p1; i <= n - p3 - p2; i++) {
            if (s.substr(i, p2) == middle) {
                return true;
            }
        }
        
        return false;
    }
};
# @lc code=end