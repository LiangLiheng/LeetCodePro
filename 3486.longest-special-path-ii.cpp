#
# @lc app=leetcode id=3486 lang=cpp
#
# [3486] Longest Special Path II
#
# @lc code=start
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], len = edge[2];
            graph[u].push_back({v, len});
            graph[v].push_back({u, len});
        }
        
        // Root the tree at node 0 - build parent array
        vector<int> parent(n, -1);
        vector<vector<pair<int, int>>> children(n);
        buildTree(0, -1, graph, parent, children);
        
        int maxLen = 0;
        int minNodes = INT_MAX;
        
        // Explore downward paths from each node
        for (int start = 0; start < n; start++) {
            unordered_map<int, int> valCount;
            exploreDownward(start, children, nums, valCount, 0, 0, maxLen, minNodes);
        }
        
        return {maxLen, minNodes};
    }
    
private:
    void buildTree(int node, int par, vector<vector<pair<int, int>>>& graph,
                   vector<int>& parent, vector<vector<pair<int, int>>>& children) {
        parent[node] = par;
        for (auto& [child, len] : graph[node]) {
            if (child != par) {
                children[node].push_back({child, len});
                buildTree(child, node, graph, parent, children);
            }
        }
    }
    
    void exploreDownward(int node, vector<vector<pair<int, int>>>& children,
                        vector<int>& nums, unordered_map<int, int>& valCount,
                        int curLen, int nodeCount, int& maxLen, int& minNodes) {
        
        int val = nums[node];
        int prevCount = valCount[val];
        valCount[val]++;
        nodeCount++;
        
        // Check if path is valid: at most one value appears twice, no value appears 3+ times
        bool valid = true;
        int duplicates = 0;
        for (auto& [v, cnt] : valCount) {
            if (cnt > 2) {
                valid = false;
                break;
            }
            if (cnt == 2) duplicates++;
        }
        if (duplicates > 1) valid = false;
        
        if (valid) {
            if (curLen > maxLen) {
                maxLen = curLen;
                minNodes = nodeCount;
            } else if (curLen == maxLen) {
                minNodes = min(minNodes, nodeCount);
            }
        }
        
        // Only explore children if path is still valid
        if (valid) {
            for (auto& [child, edgeLen] : children[node]) {
                exploreDownward(child, children, nums, valCount,
                              curLen + edgeLen, nodeCount, maxLen, minNodes);
            }
        }
        
        // Backtrack
        valCount[val]--;
        if (valCount[val] == 0) {
            valCount.erase(val);
        }
    }
};
# @lc code=end