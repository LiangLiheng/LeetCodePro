#
# @lc app=leetcode id=3425 lang=cpp
#
# [3425] Longest Special Path
#
# @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        
        // Build adjacency list
        vector<vector<pair<int, int>>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        
        long long maxLen = 0;
        int minNodes = 1;
        
        // DFS to find longest special path
        unordered_map<int, int> valToIdx;
        vector<long long> cumulativeLen;
        
        function<void(int, int, long long)> dfs = [&](int u, int parent, long long distFromRoot) {
            int val = nums[u];
            
            // Find start index of valid path (after last occurrence of this value)
            int startIdx = 0;
            if (valToIdx.count(val)) {
                startIdx = valToIdx[val] + 1;
            }
            
            // Add current node
            int curIdx = cumulativeLen.size();
            cumulativeLen.push_back(distFromRoot);
            int prevIdx = valToIdx.count(val) ? valToIdx[val] : -1;
            valToIdx[val] = curIdx;
            
            // Calculate path length and node count
            long long startLen = (startIdx > 0) ? cumulativeLen[startIdx - 1] : 0;
            long long pathLen = distFromRoot - startLen;
            int nodeCount = curIdx - startIdx + 1;
            
            // Update result
            if (pathLen > maxLen || (pathLen == maxLen && nodeCount < minNodes)) {
                maxLen = pathLen;
                minNodes = nodeCount;
            }
            
            // Process children
            for (auto [v, w] : adj[u]) {
                if (v != parent) {
                    dfs(v, u, distFromRoot + w);
                }
            }
            
            // Backtrack
            cumulativeLen.pop_back();
            if (prevIdx >= 0) {
                valToIdx[val] = prevIdx;
            } else {
                valToIdx.erase(val);
            }
        };
        
        dfs(0, -1, 0);
        
        return {(int)maxLen, minNodes};
    }
};
# @lc code=end