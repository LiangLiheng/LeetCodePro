#
# @lc app=leetcode id=3488 lang=cpp
#
# [3488] Closest Equal Element Queries
#
# @lc code=start
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        
        // Build a map from value to list of indices
        unordered_map<int, vector<int>> valueToIndices;
        for (int i = 0; i < n; i++) {
            valueToIndices[nums[i]].push_back(i);
        }
        
        vector<int> answer;
        for (int query : queries) {
            int value = nums[query];
            vector<int>& indices = valueToIndices[value];
            
            // If only one index has this value, return -1
            if (indices.size() == 1) {
                answer.push_back(-1);
                continue;
            }
            
            // Find minimum circular distance to other indices
            int minDist = INT_MAX;
            for (int idx : indices) {
                if (idx != query) {
                    int directDist = abs(idx - query);
                    int wrapDist = n - directDist;
                    int circularDist = min(directDist, wrapDist);
                    minDist = min(minDist, circularDist);
                }
            }
            
            answer.push_back(minDist);
        }
        
        return answer;
    }
};
# @lc code=end