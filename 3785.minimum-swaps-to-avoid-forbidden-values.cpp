#
# @lc app=leetcode id=3785 lang=cpp
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#
# @lc code=start
class Solution {
public:
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size();
        
        // Build bipartite graph: position i -> index j where nums[j] != forbidden[i]
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (nums[j] != forbidden[i]) {
                    graph[i].push_back(j);
                }
            }
        }
        
        // Find maximum matching using Kuhn's algorithm
        vector<int> match(n, -1);  // match[j] = i means position i takes value from index j
        
        auto dfs = [&](int v, vector<bool>& used, auto& dfs_ref) -> bool {
            for (int u : graph[v]) {
                if (used[u]) continue;
                used[u] = true;
                if (match[u] == -1 || dfs_ref(match[u], used, dfs_ref)) {
                    match[u] = v;
                    return true;
                }
            }
            return false;
        };
        
        for (int i = 0; i < n; i++) {
            vector<bool> used(n, false);
            dfs(i, used, dfs);
        }
        
        // Build assignment: assignment[i] = j means position i gets value from original index j
        vector<int> assignment(n, -1);
        for (int j = 0; j < n; j++) {
            if (match[j] != -1) {
                assignment[match[j]] = j;
            }
        }
        
        // Check if all positions are matched
        for (int i = 0; i < n; i++) {
            if (assignment[i] == -1) return -1;
        }
        
        // Count cycles in permutation (minimum swaps)
        vector<bool> visited(n, false);
        int swaps = 0;
        
        for (int i = 0; i < n; i++) {
            if (visited[i] || assignment[i] == i) continue;
            
            int cycleLen = 0;
            int j = i;
            while (!visited[j]) {
                visited[j] = true;
                j = assignment[j];
                cycleLen++;
            }
            swaps += cycleLen - 1;
        }
        
        return swaps;
    }
};
# @lc code=end