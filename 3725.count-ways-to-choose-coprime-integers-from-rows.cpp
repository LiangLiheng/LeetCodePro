#
# @lc app=leetcode id=3725 lang=cpp
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#
# @lc code=start
class Solution {
public:
    int countCoprime(vector<vector<int>>& mat) {
        const int MOD = 1e9 + 7;
        int m = mat.size();
        
        // dp[g] = number of ways to achieve GCD = g
        unordered_map<int, long long> dp;
        
        // Initialize with first row
        for (int val : mat[0]) {
            dp[val]++;
        }
        
        // Process remaining rows
        for (int i = 1; i < m; i++) {
            unordered_map<int, long long> ndp;
            
            for (auto& [g, cnt] : dp) {
                for (int val : mat[i]) {
                    int new_g = __gcd(g, val);
                    ndp[new_g] = (ndp[new_g] + cnt) % MOD;
                }
            }
            
            dp = move(ndp);
        }
        
        return dp[1];
    }
};
# @lc code=end