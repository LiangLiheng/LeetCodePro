#
# @lc app=leetcode id=3569 lang=cpp
#
# [3569] Maximize Count of Distinct Primes After Split
#
# @lc code=start
class Solution {
public:
    vector<bool> sieve(int maxVal) {
        vector<bool> isPrime(maxVal + 1, true);
        isPrime[0] = isPrime[1] = false;
        
        for (int i = 2; i * i <= maxVal; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= maxVal; j += i) {
                    isPrime[j] = false;
                }
            }
        }
        return isPrime;
    }
    
    vector<int> maximumCount(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> result;
        
        vector<bool> isPrime = sieve(100000);
        
        for (auto& query : queries) {
            int idx = query[0];
            int val = query[1];
            nums[idx] = val;
            
            // Compute prefix distinct primes count for each position
            vector<int> prefixCount(n);
            unordered_set<int> primesSeen;
            for (int i = 0; i < n; i++) {
                if (nums[i] <= 100000 && isPrime[nums[i]]) {
                    primesSeen.insert(nums[i]);
                }
                prefixCount[i] = primesSeen.size();
            }
            
            // Compute suffix distinct primes count for each position
            vector<int> suffixCount(n);
            primesSeen.clear();
            for (int i = n - 1; i >= 0; i--) {
                if (nums[i] <= 100000 && isPrime[nums[i]]) {
                    primesSeen.insert(nums[i]);
                }
                suffixCount[i] = primesSeen.size();
            }
            
            int maxCount = 0;
            // Try all split points k from 1 to n-1
            for (int k = 1; k < n; k++) {
                // Prefix is [0..k-1], suffix is [k..n-1]
                int totalCount = prefixCount[k-1] + suffixCount[k];
                maxCount = max(maxCount, totalCount);
            }
            
            result.push_back(maxCount);
        }
        
        return result;
    }
};
# @lc code=end