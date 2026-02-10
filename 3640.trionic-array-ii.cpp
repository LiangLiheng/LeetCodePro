#
# @lc app=leetcode id=3640 lang=cpp
#
# [3640] Trionic Array II
#
# @lc code=start
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        const long long NEG_INF = LLONG_MIN / 2;
        
        vector<long long> inc1(n, NEG_INF);
        vector<long long> dec(n, NEG_INF);
        vector<long long> inc2(n, NEG_INF);
        
        for (int i = 1; i < n; i++) {
            // Phase 1: strictly increasing
            if (nums[i] > nums[i-1]) {
                if (inc1[i-1] != NEG_INF) {
                    inc1[i] = max(inc1[i], inc1[i-1] + nums[i]);
                }
                inc1[i] = max(inc1[i], (long long)nums[i-1] + nums[i]);
            }
            
            // Phase 2: strictly decreasing (must follow phase 1)
            if (nums[i] < nums[i-1]) {
                if (inc1[i-1] != NEG_INF) {
                    dec[i] = max(dec[i], inc1[i-1] + nums[i]);
                }
                if (dec[i-1] != NEG_INF) {
                    dec[i] = max(dec[i], dec[i-1] + nums[i]);
                }
            }
            
            // Phase 3: strictly increasing (must follow phase 2)
            if (nums[i] > nums[i-1]) {
                if (dec[i-1] != NEG_INF) {
                    inc2[i] = max(inc2[i], dec[i-1] + nums[i]);
                }
                if (inc2[i-1] != NEG_INF) {
                    inc2[i] = max(inc2[i], inc2[i-1] + nums[i]);
                }
            }
        }
        
        long long result = NEG_INF;
        for (int i = 0; i < n; i++) {
            result = max(result, inc2[i]);
        }
        
        return result;
    }
};
# @lc code=end