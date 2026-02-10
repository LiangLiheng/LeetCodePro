#
# @lc app=leetcode id=3757 lang=cpp
#
# [3757] Number of Effective Subsequences
#
#include <vector>
#include <set>
using namespace std;

# @lc code=start
class Solution {
public:
    int countEffective(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        
        // Calculate total OR
        int totalOR = 0;
        for (int num : nums) {
            totalOR |= num;
        }
        
        if (totalOR == 0) return 0;
        
        // Find which bits are set in totalOR
        vector<int> bits;
        for (int b = 0; b < 20; b++) {  // nums[i] <= 10^6 < 2^20
            if (totalOR & (1 << b)) {
                bits.push_back(b);
            }
        }
        
        int numBits = bits.size();
        long long answer = 0;
        
        // Inclusion-exclusion over all non-empty subsets of bits
        for (int mask = 1; mask < (1 << numBits); mask++) {
            // Find union of elements having any of the selected bits
            set<int> unionIndices;
            for (int i = 0; i < numBits; i++) {
                if (mask & (1 << i)) {
                    int bit = bits[i];
                    for (int j = 0; j < n; j++) {
                        if (nums[j] & (1 << bit)) {
                            unionIndices.insert(j);
                        }
                    }
                }
            }
            
            // Count subsequences that include all these elements
            int sizeUnion = unionIndices.size();
            long long count = 1;
            for (int i = 0; i < n - sizeUnion; i++) {
                count = (count * 2) % MOD;
            }
            
            // Apply inclusion-exclusion
            int popcount = __builtin_popcount(mask);
            if (popcount % 2 == 1) {
                answer = (answer + count) % MOD;
            } else {
                answer = (answer - count + MOD) % MOD;
            }
        }
        
        return answer;
    }
};
# @lc code=end