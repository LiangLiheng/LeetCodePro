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
        
        // DP states:
        // inc: max sum of strictly increasing sequence ending at current position
        // dec: max sum of inc->dec pattern ending at current position (in dec phase)
        // tri: max sum of complete trionic pattern ending at current position
        long long inc = nums[0];
        long long dec = NEG_INF;
        long long tri = NEG_INF;
        long long result = NEG_INF;
        
        for (int i = 1; i < n; i++) {
            long long new_inc, new_dec, new_tri;
            
            // Update increasing state
            if (nums[i] > nums[i-1]) {
                new_inc = inc + nums[i];
            } else {
                new_inc = nums[i];
            }
            
            // Update decreasing state (after peak)
            if (nums[i] < nums[i-1]) {
                new_dec = inc + nums[i];  // Start new dec from current inc
                if (dec != NEG_INF) {
                    new_dec = max(new_dec, dec + nums[i]);  // Or continue existing dec
                }
            } else {
                new_dec = NEG_INF;
            }
            
            // Update trionic state (after valley, increasing again)
            if (nums[i] > nums[i-1]) {
                new_tri = NEG_INF;
                if (dec != NEG_INF) {
                    new_tri = max(new_tri, dec + nums[i]);  // Start new inc from dec
                }
                if (tri != NEG_INF) {
                    new_tri = max(new_tri, tri + nums[i]);  // Or continue existing tri
                }
            } else {
                new_tri = NEG_INF;
            }
            
            // Update states
            inc = new_inc;
            dec = new_dec;
            tri = new_tri;
            
            // Track maximum trionic sum
            if (tri != NEG_INF) {
                result = max(result, tri);
            }
        }
        
        return result;
    }
};
# @lc code=end