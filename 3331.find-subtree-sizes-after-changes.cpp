//
// @lc app=leetcode id=3331 lang=cpp
//
// [3331] Find Subtree Sizes After Changes
//
// @lc code=start
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<int> newParent = parent;
        
        // Find new parents for each node
        for (int i = 1; i < n; i++) {
            int curr = parent[i];
            while (curr != -1) {
                if (s[curr] == s[i]) {
                    newParent[i] = curr;
                    break;
                }
                curr = parent[curr];
            }
        }
        
        // Build adjacency list for new tree
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) {
            children[newParent[i]].push_back(i);
        }
        
        // Calculate subtree sizes using DFS
        vector<int> result(n);
        dfs(0, children, result);
        
        return result;
    }
    
private:
    int dfs(int node, vector<vector<int>>& children, vector<int>& result) {
        int size = 1;
        for (int child : children[node]) {
            size += dfs(child, children, result);
        }
        result[node] = size;
        return size;
    }
};
// @lc code=end