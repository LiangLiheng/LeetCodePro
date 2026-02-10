#
# @lc app=leetcode id=3615 lang=cpp
#
# [3615] Longest Palindromic Path in Graph
#
# @lc code=start
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        for (auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        int maxLength = 1; // At least one node forms a palindrome
        
        // Try starting from each node
        for (int start = 0; start < n; start++) {
            string path;
            int visited = 0;
            dfs(start, graph, label, path, visited, maxLength);
        }
        
        return maxLength;
    }
    
private:
    void dfs(int node, vector<vector<int>>& graph, string& label, 
             string& path, int visited, int& maxLength) {
        // Mark current node as visited
        visited |= (1 << node);
        path += label[node];
        
        // Check if current path is a palindrome
        if (isPalindrome(path)) {
            maxLength = max(maxLength, (int)path.size());
        }
        
        // Continue DFS to adjacent nodes
        for (int neighbor : graph[node]) {
            if (!(visited & (1 << neighbor))) {
                dfs(neighbor, graph, label, path, visited, maxLength);
            }
        }
        
        // Backtrack
        path.pop_back();
    }
    
    bool isPalindrome(const string& s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};
# @lc code=end