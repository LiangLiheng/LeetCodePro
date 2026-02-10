#
# @lc app=leetcode id=3579 lang=cpp
#
# [3579] Minimum Steps to Convert String with Operations
#
# @lc code=start
class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.length();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] == INT_MAX) continue;
                string s1 = word1.substr(j, i - j);
                string s2 = word2.substr(j, i - j);
                int cost = calcMinOps(s1, s2);
                dp[i] = min(dp[i], dp[j] + cost);
            }
        }
        
        return dp[n];
    }
    
private:
    int calcMinOps(string s, string t) {
        int ops1 = calcOpsHelper(s, t, 0);
        
        string rev = s;
        reverse(rev.begin(), rev.end());
        int ops2 = calcOpsHelper(rev, t, 1);
        
        return min(ops1, ops2);
    }
    
    int calcOpsHelper(string s, string t, int reverseCount) {
        int n = s.length();
        vector<bool> used(n, false);
        int ops = reverseCount;
        
        // Find positions that can be paired for swaps
        for (int i = 0; i < n; i++) {
            if (used[i] || s[i] == t[i]) continue;
            for (int j = i + 1; j < n; j++) {
                if (used[j] || s[j] == t[j]) continue;
                if (s[i] == t[j] && s[j] == t[i]) {
                    used[i] = used[j] = true;
                    ops++;
                    break;
                }
            }
        }
        
        // Count remaining mismatches that need replacements
        for (int i = 0; i < n; i++) {
            if (!used[i] && s[i] != t[i]) {
                ops++;
            }
        }
        
        return ops;
    }
};
# @lc code=end