#
# @lc app=leetcode id=3538 lang=cpp
#
# [3538] Merge Operations for Minimum Travel Time
#
# @lc code=start
class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        vector<pair<int, int>> signs;
        for (int i = 0; i < n; i++) {
            signs.push_back({i, time[i]});
        }
        return solve(signs, position, 0, k);
    }
    
private:
    map<pair<vector<pair<int,int>>, int>, int> memo;
    
    int solve(vector<pair<int,int>>& signs, vector<int>& position, int merges_done, int k) {
        if (merges_done == k) {
            return calculateCost(signs, position);
        }
        
        auto state = make_pair(signs, merges_done);
        if (memo.count(state)) {
            return memo[state];
        }
        
        int result = INT_MAX;
        
        for (int i = 0; i < (int)signs.size() - 1; i++) {
            if (signs[i].first == 0) continue; // Can't remove sign at position 0
            
            vector<pair<int,int>> new_signs;
            for (int j = 0; j < (int)signs.size(); j++) {
                if (j == i) continue; // Remove this sign
                if (j == i + 1) {
                    // Merge: add time from removed sign to this sign
                    new_signs.push_back({signs[j].first, signs[i].second + signs[j].second});
                } else {
                    new_signs.push_back(signs[j]);
                }
            }
            
            result = min(result, solve(new_signs, position, merges_done + 1, k));
        }
        
        memo[state] = result;
        return result;
    }
    
    int calculateCost(const vector<pair<int,int>>& signs, const vector<int>& position) {
        int cost = 0;
        for (int i = 0; i < (int)signs.size() - 1; i++) {
            int pos_idx1 = signs[i].first;
            int pos_idx2 = signs[i+1].first;
            int time_per_km = signs[i].second;
            int distance = position[pos_idx2] - position[pos_idx1];
            cost += distance * time_per_km;
        }
        return cost;
    }
};
# @lc code=end