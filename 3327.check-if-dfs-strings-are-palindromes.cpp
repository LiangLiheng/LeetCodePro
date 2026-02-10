#
# @lc app=leetcode id=3327 lang=cpp
#
# [3327] Check if DFS Strings Are Palindromes
#

# @lc code=start
class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = s.size();
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            adj[parent[i]].push_back(i);
        }
        for (auto& ch : adj) {
            sort(ch.begin(), ch.end());
        }
        const long long MOD1 = 1000000007LL;
        const long long MOD2 = 1000000009LL;
        const long long B1 = 31LL;
        const long long B2 = 37LL;
        vector<long long> p1(n + 1, 1LL);
        vector<long long> p2(n + 1, 1LL);
        for (int i = 1; i <= n; ++i) {
            p1[i] = p1[i - 1] * B1 % MOD1;
            p2[i] = p2[i - 1] * B2 % MOD2;
        }
        vector<long long> hf1(n), hf2(n), hr1(n), hr2(n);
        vector<int> len(n);
        std::function<void(int)> dfs = [&](int u) {
            len[u] = 1;
            long long f1 = 0, f2 = 0;
            long long r1 = (s[u] - 'a' + 1) % MOD1;
            long long r2 = (s[u] - 'a' + 1) % MOD2;
            for (int v : adj[u]) {
                dfs(v);
                len[u] += len[v];
                f1 = (f1 * p1[len[v]] % MOD1 + hf1[v]) % MOD1;
                f2 = (f2 * p2[len[v]] % MOD2 + hf2[v]) % MOD2;
            }
            long long ch = s[u] - 'a' + 1;
            f1 = (f1 * p1[1] % MOD1 + ch) % MOD1;
            f2 = (f2 * p2[1] % MOD2 + ch) % MOD2;
            for (int j = adj[u].size() - 1; j >= 0; --j) {
                int v = adj[u][j];
                r1 = (r1 * p1[len[v]] % MOD1 + hr1[v]) % MOD1;
                r2 = (r2 * p2[len[v]] % MOD2 + hr2[v]) % MOD2;
            }
            hf1[u] = f1;
            hf2[u] = f2;
            hr1[u] = r1;
            hr2[u] = r2;
        };
        dfs(0);
        vector<bool> ans(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = (hf1[i] == hr1[i] && hf2[i] == hr2[i]);
        }
        return ans;
    }
};
# @lc code=end