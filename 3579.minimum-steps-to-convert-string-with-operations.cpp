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
                int cost = calculateMinOps(word1, word2, j, i - 1);
                if (dp[j] != INT_MAX) {
                    dp[i] = min(dp[i], dp[j] + cost);
                }
            }
        }
        
        return dp[n];
    }
    
private:
    int calculateMinOps(const string& word1, const string& word2, int l, int r) {
        string s1 = word1.substr(l, r - l + 1);
        string s2 = word2.substr(l, r - l + 1);
        
        // Try without reversing
        int cost1 = calculateOpsHelper(s1, s2, false);
        
        // Try with reversing
        int cost2 = calculateOpsHelper(s1, s2, true);
        
        return min(cost1, cost2);
    }
    
    int calculateOpsHelper(string s1, const string& s2, bool useReverse) {
        int cost = 0;
        
        if (useReverse) {
            reverse(s1.begin(), s1.end());
            cost = 1;
        }
        
        // Find all mismatched positions
        vector<int> mismatches;
        for (size_t i = 0; i < s1.length(); i++) {
            if (s1[i] != s2[i]) {
                mismatches.push_back(i);
            }
        }
        
        // Try to pair up mismatches for swaps
        int swaps = 0;
        vector<bool> used(s1.length(), false);
        
        for (size_t i = 0; i < mismatches.size(); i++) {
            if (used[mismatches[i]]) continue;
            
            for (size_t j = i + 1; j < mismatches.size(); j++) {
                if (used[mismatches[j]]) continue;
                
                int pos_i = mismatches[i];
                int pos_j = mismatches[j];
                
                // Check if swapping these two positions would fix both
                if (s1[pos_i] == s2[pos_j] && s1[pos_j] == s2[pos_i]) {
                    swaps++;
                    used[pos_i] = true;
                    used[pos_j] = true;
                    break;
                }
            }
        }
        
        // Count remaining mismatches that need replacements
        int replacements = 0;
        for (int pos : mismatches) {
            if (!used[pos]) {
                replacements++;
            }
        }
        
        return cost + swaps + replacements;
    }
};
# @lc code=end