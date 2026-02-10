//
// @lc app=leetcode id=3575 lang=cpp
//
// [3575] Maximum Good Subtree Score
//
// @lc code=start
class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        int n = vals.size();
        const int MOD = 1e9 + 7;
        
        // Build tree structure
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) {
            children[par[i]].push_back(i);
        }
        
        // Extract digit mask and check for duplicates within a number
        auto getDigits = [](int num) -> pair<int, bool> {
            int mask = 0;
            bool hasDup = false;
            while (num > 0) {
                int digit = num % 10;
                if (mask & (1 << digit)) {
                    hasDup = true;
                }
                mask |= (1 << digit);
                num /= 10;
            }
            return {mask, hasDup};
        };
        
        vector<long long> maxScore(n);
        
        // DFS to compute dp for each subtree
        // Returns map of digit_mask -> max_sum
        function<map<int, long long>(int)> dfs = [&](int u) -> map<int, long long> {
            map<int, long long> dp;
            dp[0] = 0; // Empty subset
            
            // Add current node if it has no duplicate digits
            auto [myMask, hasDup] = getDigits(vals[u]);
            if (!hasDup) {
                dp[myMask] = vals[u];
            }
            
            // Process each child
            for (int child : children[u]) {
                auto childDp = dfs(child);
                map<int, long long> newDp;
                
                for (auto& [mask1, sum1] : dp) {
                    // Keep current state (not taking from child)
                    newDp[mask1] = max(newDp[mask1], sum1);
                    
                    // Try combining with child states
                    for (auto& [mask2, sum2] : childDp) {
                        if ((mask1 & mask2) == 0) { // No overlapping digits
                            int newMask = mask1 | mask2;
                            long long newSum = sum1 + sum2;
                            newDp[newMask] = max(newDp[newMask], newSum);
                        }
                    }
                }
                
                dp = newDp;
            }
            
            // Compute max score for this subtree
            long long maxVal = 0;
            for (auto& [mask, sum] : dp) {
                maxVal = max(maxVal, sum);
            }
            maxScore[u] = maxVal;
            
            return dp;
        };
        
        dfs(0);
        
        // Sum all max scores
        long long result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + maxScore[i]) % MOD;
        }
        
        return result;
    }
};
// @lc code=end