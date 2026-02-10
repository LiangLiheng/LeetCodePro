#
# @lc app=leetcode id=3331 lang=cpp
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }
        vector<int> new_parent = parent;
        vector<int> last_ancestor(26, -1);
        auto dfs_modify = [&](auto&& self, int u, int p) -> void {
            int idx = s[u] - 'a';
            if (last_ancestor[idx] != -1) {
                new_parent[u] = last_ancestor[idx];
            }
            int prev = last_ancestor[idx];
            last_ancestor[idx] = u;
            for (int v : adj[u]) {
                if (v != p) {
                    self(self, v, u);
                }
            }
            last_ancestor[idx] = prev;
        };
        dfs_modify(dfs_modify, 0, -1);
        vector<vector<int>> new_adj(n);
        for (int i = 1; i < n; ++i) {
            new_adj[new_parent[i]].push_back(i);
        }
        vector<int> subtree_sizes(n);
        auto dfs_size = [&](auto&& self, int u) -> int {
            int size = 1;
            for (int v : new_adj[u]) {
                size += self(self, v);
            }
            subtree_sizes[u] = size;
            return size;
        };
        dfs_size(dfs_size, 0);
        return subtree_sizes;
    }
};
# @lc code=end