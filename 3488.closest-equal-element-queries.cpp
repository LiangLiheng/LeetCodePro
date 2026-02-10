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
        vector<int> min_dist(n, -1);
        unordered_map<int, vector<int>> mp;
        for(int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        for(auto& p : mp) {
            vector<int>& positions = p.second;
            int m = positions.size();
            if (m < 2) continue;
            for(int k = 0; k < m; k++) {
                int prev_k = (k - 1 + m) % m;
                int next_k = (k + 1) % m;
                int idx = positions[k];
                int pidx = positions[prev_k];
                int nidx = positions[next_k];
                int d1 = abs(idx - pidx);
                d1 = min(d1, n - d1);
                int d2 = abs(idx - nidx);
                d2 = min(d2, n - d2);
                min_dist[idx] = min(d1, d2);
            }
        }
        vector<int> answer(queries.size());
        for(int i = 0; i < queries.size(); i++) {
            answer[i] = min_dist[queries[i]];
        }
        return answer;
    }
};
# @lc code=end