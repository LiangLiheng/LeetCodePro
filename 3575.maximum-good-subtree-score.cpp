#
# @lc app=leetcode id=3575 lang=cpp
#
# [3575] Maximum Good Subtree Score
#
# @lc code=start
class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        const int MOD = 1e9 + 7;
        int n = vals.size();
        
        // Build adjacency list
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) {
            children[par[i]].push_back(i);
        }
        
        // Get digit mask for a number (-1 if digit repeats within number)
        auto getDigitMask = [](long long num) -> int {
            int mask = 0;
            while (num > 0) {
                int digit = num % 10;
                if (mask & (1 << digit)) {
                    return -1;  // Digit repeats
                }
                mask |= (1 << digit);
                num /= 10;
            }
            return mask;
        };
        
        long long totalSum = 0;
        
        // DFS returns map: digit_mask -> max_score for subtree rooted at u
        function<map<int, long long>(int)> dfs = [&](int u) -> map<int, long long> {
            map<int, long long> dp;
            dp[0] = 0;  // Start with empty selection
            
            // Process each child
            for (int child : children[u]) {
                map<int, long long> childStates = dfs(child);
                map<int, long long> newDp;
                
                // For each current state
                for (auto [mask1, score1] : dp) {
                    // Option 1: Don't select anything from this child
                    newDp[mask1] = max(newDp[mask1], score1);
                    
                    // Option 2: Select something from this child
                    for (auto [mask2, score2] : childStates) {
                        if ((mask1 & mask2) == 0) {  // No digit conflict
                            int newMask = mask1 | mask2;
                            long long newScore = score1 + score2;
                            newDp[newMask] = max(newDp[newMask], newScore);
                        }
                    }
                }
                
                dp = move(newDp);
            }
            
            // Try adding current node to each state
            int nodeMask = getDigitMask(vals[u]);
            if (nodeMask != -1) {
                vector<pair<int, long long>> toAdd;
                for (auto [mask, score] : dp) {
                    if ((mask & nodeMask) == 0) {
                        toAdd.push_back({mask | nodeMask, score + vals[u]});
                    }
                }
                for (auto [newMask, newScore] : toAdd) {
                    dp[newMask] = max(dp[newMask], newScore);
                }
            }
            
            // Calculate max score for this node's subtree
            long long maxScore = 0;
            for (auto [mask, score] : dp) {
                maxScore = max(maxScore, score);
            }
            totalSum = (totalSum + maxScore) % MOD;
            
            return dp;
        };
        
        dfs(0);
        return (int)totalSum;
    }
};
# @lc code=end