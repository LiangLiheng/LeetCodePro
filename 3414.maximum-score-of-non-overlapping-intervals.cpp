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
        
        // Sort intervals by end time with original index
        vector<array<int, 4>> arr;
        for (int i = 0; i < n; i++) {
            arr.push_back({intervals[i][1], intervals[i][0], intervals[i][2], i});
        }
        sort(arr.begin(), arr.end());
        
        // dp[j][lastEnd] = {weight, indices} for j intervals selected, last one ending at lastEnd
        vector<map<int, pair<long long, vector<int>>>> dp(5), next_dp(5);
        dp[0][-1] = {0, {}};
        
        for (int i = 0; i < n; i++) {
            auto [end, start, weight, idx] = arr[i];
            next_dp = dp;  // Start with previous states
            
            // Try adding this interval to each existing state
            for (int j = 0; j < 4; j++) {
                for (auto& [lastEnd, state] : dp[j]) {
                    if (lastEnd < start) {  // No overlap
                        long long newWeight = state.first + weight;
                        vector<int> newIndices = state.second;
                        newIndices.push_back(idx);
                        sort(newIndices.begin(), newIndices.end());
                        
                        // Update next_dp[j+1][end]
                        if (next_dp[j+1].find(end) == next_dp[j+1].end() ||
                            next_dp[j+1][end].first < newWeight ||
                            (next_dp[j+1][end].first == newWeight && newIndices < next_dp[j+1][end].second)) {
                            next_dp[j+1][end] = {newWeight, newIndices};
                        }
                    }
                }
            }
            
            dp = next_dp;
        }
        
        // Find best solution
        pair<long long, vector<int>> best = {0, {}};
        for (int j = 0; j <= 4; j++) {
            for (auto& [lastEnd, state] : dp[j]) {
                if (state.first > best.first ||
                    (state.first == best.first && !state.second.empty() && (best.second.empty() || state.second < best.second))) {
                    best = state;
                }
            }
        }
        
        return best.second;
    }
};
# @lc code=end