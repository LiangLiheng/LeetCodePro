#
# @lc app=leetcode id=3615 lang=cpp
#
# [3615] Longest Palindromic Path in Graph
#

# @lc code=start
class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int MS = 1 << n;
        vector<int> dpp(static_cast<size_t>(n) * n * MS, 0);
        auto get_idx = [&](int u, int v, int m) -> size_t {
            return (static_cast<size_t>(u) * n + v) * MS + m;
        };
        int ans = 0;
        // Base: single nodes (odd centers)
        for (int i = 0; i < n; ++i) {
            int m = 1 << i;
            dpp[get_idx(i, i, m)] = 1;
            ans = std::max(ans, 1);
        }
        // Base: length 2 pairs (even centers)
        for (int u = 0; u < n; ++u) {
            for (int v : adj[u]) {
                if (label[u] == label[v]) {
                    int m = (1 << u) | (1 << v);
                    dpp[get_idx(u, v, m)] = 2;
                    ans = std::max(ans, 2);
                }
            }
        }
        // DP extensions
        for (int mask = 0; mask < MS; ++mask) {
            for (int u = 0; u < n; ++u) {
                if ((mask & (1 << u)) == 0) continue;
                for (int v = 0; v < n; ++v) {
                    if ((mask & (1 << v)) == 0) continue;
                    size_t idx = get_idx(u, v, mask);
                    int val = dpp[idx];
                    if (val == 0) continue;
                    ans = std::max(ans, val);
                    // Extend symmetrically
                    for (int nl : adj[u]) {
                        if (mask & (1 << nl)) continue;
                        for (int nr : adj[v]) {
                            if ((mask & (1 << nr)) != 0 || nl == nr) continue;
                            if (label[nl] != label[nr]) continue;
                            int new_mask = mask | (1 << nl) | (1 << nr);
                            size_t nidx = get_idx(nl, nr, new_mask);
                            int new_val = val + 2;
                            if (new_val > dpp[nidx]) {
                                dpp[nidx] = new_val;
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};
# @lc code=end