#
# @lc app=leetcode id=3414 lang=cpp
#
# [3414] Maximum Score of Non-overlapping Intervals
#
# @lc code=start
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        
        // Create array with {end, start, weight, original_index}
        vector<array<long long, 4>> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = {intervals[i][1], intervals[i][0], intervals[i][2], (long long)i};
        }
        
        // Sort by end time
        sort(arr.begin(), arr.end());
        
        // DP: dp[i][k] = {max_weight, selected_indices}
        // i: considering first i intervals, k: number selected
        vector<vector<pair<long long, vector<int>>>> dp(n + 1, 
            vector<pair<long long, vector<int>>>(5, {LLONG_MIN / 2, {}}));
        dp[0][0] = {0, {}};
        
        for (int i = 0; i < n; i++) {
            long long end = arr[i][0];
            long long start = arr[i][1];
            long long weight = arr[i][2];
            int idx = arr[i][3];
            
            // Option 1: Skip current interval
            for (int k = 0; k <= 4; k++) {
                auto& curr = dp[i][k];
                auto& next = dp[i + 1][k];
                if (curr.first > next.first || 
                    (curr.first == next.first && curr.second < next.second)) {
                    next = curr;
                }
            }
            
            // Option 2: Take current interval
            // Find last non-overlapping interval
            int j = i - 1;
            while (j >= 0 && arr[j][0] >= start) {
                j--;
            }
            
            for (int k = 0; k < 4; k++) {
                auto& prev = dp[j + 1][k];
                if (prev.first == LLONG_MIN / 2) continue;
                
                long long new_weight = prev.first + weight;
                vector<int> new_indices = prev.second;
                new_indices.push_back(idx);
                sort(new_indices.begin(), new_indices.end());
                
                auto& next = dp[i + 1][k + 1];
                if (new_weight > next.first ||
                    (new_weight == next.first && new_indices < next.second)) {
                    next = {new_weight, new_indices};
                }
            }
        }
        
        // Find best result
        long long max_weight = LLONG_MIN / 2;
        vector<int> result;
        for (int k = 0; k <= 4; k++) {
            auto& state = dp[n][k];
            if (state.first > max_weight) {
                max_weight = state.first;
                result = state.second;
            } else if (state.first == max_weight && state.second < result) {
                result = state.second;
            }
        }
        
        return result;
    }
};
# @lc code=end