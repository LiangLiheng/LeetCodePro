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
        const int MAX_VAL = 150;
        
        // Precompute Möbius function using inclusion-exclusion
        vector<int> mu(MAX_VAL + 1);
        mu[1] = 1;
        for (int i = 1; i <= MAX_VAL; i++) {
            for (int j = 2 * i; j <= MAX_VAL; j += i) {
                mu[j] -= mu[i];
            }
        }
        
        // For each divisor d, count ways to choose elements all divisible by d
        long long result = 0;
        for (int d = 1; d <= MAX_VAL; d++) {
            long long ways = 1;
            for (const auto& row : mat) {
                int count = 0;
                for (int val : row) {
                    if (val % d == 0) {
                        count++;
                    }
                }
                ways = (ways * count) % MOD;
            }
            // Apply Möbius inversion
            result = (result + (long long)mu[d] * ways % MOD + MOD) % MOD;
        }
        
        return result;
    }
};
# @lc code=end