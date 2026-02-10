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
        
        // DP states: {sum, length_in_current_phase}
        // inc1: first increasing phase
        // dec: decreasing phase (length counts from peak)
        // inc2: second increasing phase (length counts from valley)
        vector<pair<long long, int>> inc1(n), dec(n), inc2(n);
        
        // Initialize with impossible values
        for (int i = 0; i < n; i++) {
            inc1[i] = dec[i] = inc2[i] = {LLONG_MIN, 0};
        }
        
        // First element starts inc1
        inc1[0] = {nums[0], 1};
        
        long long result = LLONG_MIN;
        
        for (int i = 1; i < n; i++) {
            // Update inc1: first increasing phase
            if (nums[i] > nums[i-1] && inc1[i-1].first != LLONG_MIN) {
                inc1[i] = {inc1[i-1].first + nums[i], inc1[i-1].second + 1};
            } else {
                inc1[i] = {nums[i], 1};
            }
            
            // Update dec: decreasing phase
            if (nums[i] < nums[i-1]) {
                // Transition from inc1 (peak at i-1)
                if (inc1[i-1].second >= 2) {
                    long long trans_sum = inc1[i-1].first + nums[i];
                    if (dec[i].first == LLONG_MIN || trans_sum > dec[i].first) {
                        dec[i] = {trans_sum, 2};
                    }
                }
                // Extend from previous dec
                if (dec[i-1].first != LLONG_MIN) {
                    long long extend_sum = dec[i-1].first + nums[i];
                    if (dec[i].first == LLONG_MIN || extend_sum > dec[i].first) {
                        dec[i] = {extend_sum, dec[i-1].second + 1};
                    }
                }
            }
            
            // Update inc2: second increasing phase
            if (nums[i] > nums[i-1]) {
                // Transition from dec (valley at i-1)
                if (dec[i-1].second >= 2) {
                    long long trans_sum = dec[i-1].first + nums[i];
                    if (inc2[i].first == LLONG_MIN || trans_sum > inc2[i].first) {
                        inc2[i] = {trans_sum, 2};
                    }
                }
                // Extend from previous inc2
                if (inc2[i-1].first != LLONG_MIN) {
                    long long extend_sum = inc2[i-1].first + nums[i];
                    if (inc2[i].first == LLONG_MIN || extend_sum > inc2[i].first) {
                        inc2[i] = {extend_sum, inc2[i-1].second + 1};
                    }
                }
            }
            
            // Check for valid trionic subarray
            if (inc2[i].second >= 2) {
                result = max(result, inc2[i].first);
            }
        }
        
        return result;
    }
};
# @lc code=end