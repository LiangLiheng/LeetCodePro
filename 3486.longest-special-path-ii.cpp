#
# @lc app=leetcode id=3486 lang=cpp
#
# [3486] Longest Special Path II
#
# @lc code=start
class Solution {
public:
    vector<vector<pair<int, int>>> tree;
    vector<int> nums;
    int maxLen;
    int minNodes;
    
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        this->nums = nums;
        tree.resize(n);
        maxLen = 0;
        minNodes = INT_MAX;
        
        // Build adjacency list
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], len = edge[2];
            graph[u].push_back({v, len});
            graph[v].push_back({u, len});
        }
        
        // Root the tree at node 0
        buildTree(0, -1, graph);
        
        // Try starting from each node
        for (int start = 0; start < n; start++) {
            unordered_map<int, int> freq;
            findPaths(start, freq, 0, 0, 0);
        }
        
        return {maxLen, minNodes};
    }
    
    void buildTree(int node, int parent, vector<vector<pair<int, int>>>& graph) {
        for (auto& [child, len] : graph[node]) {
            if (child == parent) continue;
            tree[node].push_back({child, len});
            buildTree(child, node, graph);
        }
    }
    
    void findPaths(int node, unordered_map<int, int>& freq, 
                   int duplicates, int pathLen, int nodeCount) {
        
        int val = nums[node];
        int oldFreq = freq[val];
        freq[val]++;
        
        // Check if this node can be added to the path
        int newDuplicates = duplicates;
        
        if (oldFreq == 1) {
            if (duplicates == 1) {
                // Can't add this node
                freq[val]--;
                return;
            }
            newDuplicates = 1;
        } else if (oldFreq >= 2) {
            // Can't add this node
            freq[val]--;
            return;
        }
        
        nodeCount++;
        
        // Update result (only for paths with at least 2 nodes)
        if (nodeCount >= 2) {
            if (pathLen > maxLen) {
                maxLen = pathLen;
                minNodes = nodeCount;
            } else if (pathLen == maxLen && nodeCount < minNodes) {
                minNodes = nodeCount;
            }
        }
        
        // Continue to children (descendants)
        for (auto& [child, edgeLen] : tree[node]) {
            findPaths(child, freq, newDuplicates, pathLen + edgeLen, nodeCount);
        }
        
        // Backtrack
        freq[val]--;
        if (freq[val] == 0) {
            freq.erase(val);
        }
    }
};
# @lc code=end