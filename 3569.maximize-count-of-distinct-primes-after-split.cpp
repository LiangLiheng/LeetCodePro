#
# @lc app=leetcode id=3569 lang=cpp
#
# [3569] Maximize Count of Distinct Primes After Split
#
# @lc code=start
class Solution {
public:
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        // Precompute primes using Sieve of Eratosthenes
        int maxVal = 100001;
        vector<bool> isPrime(maxVal, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i < maxVal; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j < maxVal; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        
        vector<int> result;
        int n = nums.size();
        
        for (auto& query : queries) {
            int idx = query[0];
            int val = query[1];
            nums[idx] = val;
            
            int maxCount = 0;
            
            // Try all possible split positions k (1 <= k < n)
            for (int k = 1; k < n; k++) {
                unordered_set<int> leftPrimes, rightPrimes;
                
                // Count distinct primes in left part [0..k-1]
                for (int i = 0; i < k; i++) {
                    if (isPrime[nums[i]]) {
                        leftPrimes.insert(nums[i]);
                    }
                }
                
                // Count distinct primes in right part [k..n-1]
                for (int i = k; i < n; i++) {
                    if (isPrime[nums[i]]) {
                        rightPrimes.insert(nums[i]);
                    }
                }
                
                int count = leftPrimes.size() + rightPrimes.size();
                maxCount = max(maxCount, count);
            }
            
            result.push_back(maxCount);
        }
        
        return result;
    }
};
# @lc code=end