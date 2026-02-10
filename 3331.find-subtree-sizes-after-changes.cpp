#
# @lc app=leetcode id=3331 lang=cpp
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = s.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }
        vector<int> np = parent;
        vector<int> last(26, -1);
        auto dfs_update = [&](auto&& self, int u) -> void {
            if (u != 0) {
                int c = s[u] - 'a';
                if (last[c] != -1) {
                    np[u] = last[c];
                }
            }
            int c = s[u] - 'a';
            int prv = last[c];
            last[c] = u;
            for (int v : adj[u]) {
                self(self, v);
            }
            last[c] = prv;
        };
        dfs_update(dfs_update, 0);
        vector<vector<int>> nadj(n);
        for (int i = 1; i < n; ++i) {
            nadj[np[i]].push_back(i);
        }
        vector<int> subtree(n, 1);
        auto dfs_size = [&](auto&& self, int u) -> int {
            int sz = 1;
            for (int v : nadj[u]) {
                sz += self(self, v);
            }
            subtree[u] = sz;
            return sz;
        };
        dfs_size(dfs_size, 0);
        return subtree;
    }
};
# @lc code=end