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
        int m = mat.size();
        
        // Compute Möbius function using sieve
        vector<int> mu(MAX_VAL + 1);
        vector<int> spf(MAX_VAL + 1); // smallest prime factor
        
        for (int i = 1; i <= MAX_VAL; i++) {
            spf[i] = i;
        }
        
        for (int i = 2; i <= MAX_VAL; i++) {
            if (spf[i] == i) { // i is prime
                for (int j = i; j <= MAX_VAL; j += i) {
                    if (spf[j] == j) {
                        spf[j] = i;
                    }
                }
            }
        }
        
        mu[1] = 1;
        for (int i = 2; i <= MAX_VAL; i++) {
            int p = spf[i];
            int rest = i / p;
            
            if (rest % p == 0) {
                mu[i] = 0;
            } else {
                mu[i] = -mu[rest];
            }
        }
        
        // Count ways for each divisor
        long long result = 0;
        
        for (int d = 1; d <= MAX_VAL; d++) {
            if (mu[d] == 0) continue;
            
            long long ways = 1;
            for (int i = 0; i < m; i++) {
                int count = 0;
                for (int num : mat[i]) {
                    if (num % d == 0) {
                        count++;
                    }
                }
                ways = (ways * count) % MOD;
            }
            
            result = (result + (long long)mu[d] * ways) % MOD;
        }
        
        return (result % MOD + MOD) % MOD;
    }
};
# @lc code=end