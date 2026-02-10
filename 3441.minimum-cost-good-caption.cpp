#
# @lc app=leetcode id=3441 lang=cpp
#
# [3441] Minimum Cost Good Caption
#
# @lc code=start
class Solution {
public:
    string minCostGoodCaption(string caption) {
        int n = caption.length();
        if (n < 3) return "";
        
        // dp[i] = minimum cost to make caption[0...i-1] good
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 3; i <= n; i++) {
            for (int j = 0; j <= i - 3; j++) {
                if (dp[j] == INT_MAX) continue;
                
                // Try all characters for segment [j, i)
                for (char c = 'a'; c <= 'z'; c++) {
                    int cost = 0;
                    for (int k = j; k < i; k++) {
                        cost += abs(caption[k] - c);
                    }
                    
                    dp[i] = min(dp[i], dp[j] + cost);
                }
            }
        }
        
        if (dp[n] == INT_MAX) return "";
        
        // Reconstruct lexicographically smallest string
        string result;
        int pos = 0;
        
        while (pos < n) {
            bool found = false;
            
            // Try characters in order (lexicographically)
            for (char c = 'a'; c <= 'z'; c++) {
                // Try segment lengths
                for (int len = 3; pos + len <= n; len++) {
                    int cost = 0;
                    for (int k = pos; k < pos + len; k++) {
                        cost += abs(caption[k] - c);
                    }
                    
                    if (dp[pos] + cost == dp[pos + len]) {
                        result += string(len, c);
                        pos += len;
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            
            if (!found) return ""; // Should not happen
        }
        
        return result;
    }
};
# @lc code=end