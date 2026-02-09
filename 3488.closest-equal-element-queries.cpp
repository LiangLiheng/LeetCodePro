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
        unordered_map<int, vector<int>> valueIndices;
        
        // Build map of value -> list of indices
        for (int i = 0; i < n; i++) {
            valueIndices[nums[i]].push_back(i);
        }
        
        vector<int> answer;
        
        for (int queryIdx : queries) {
            int value = nums[queryIdx];
            vector<int>& indices = valueIndices[value];
            
            // If only one occurrence, return -1
            if (indices.size() == 1) {
                answer.push_back(-1);
                continue;
            }
            
            // Find minimum circular distance
            int minDist = INT_MAX;
            for (int idx : indices) {
                if (idx != queryIdx) {
                    int directDist = abs(idx - queryIdx);
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