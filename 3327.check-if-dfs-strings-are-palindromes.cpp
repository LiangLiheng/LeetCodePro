#
# @lc app=leetcode id=3327 lang=cpp
#
# [3327] Check if DFS Strings Are Palindromes
#
# @lc code=start
class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> children(n);
        
        // Build adjacency list
        for (int i = 1; i < n; i++) {
            children[parent[i]].push_back(i);
        }
        
        // Sort children for each node
        for (int i = 0; i < n; i++) {
            sort(children[i].begin(), children[i].end());
        }
        
        // Build DFS string and record ranges
        string dfsStr;
        vector<int> start(n), end(n);
        
        function<void(int)> dfs = [&](int x) {
            start[x] = dfsStr.size();
            for (int child : children[x]) {
                dfs(child);
            }
            dfsStr += s[x];
            end[x] = dfsStr.size() - 1;
        };
        
        dfs(0);
        
        int m = dfsStr.size();
        const long long MOD = 1e9 + 7;
        const long long BASE = 31;
        
        // Precompute powers of BASE
        vector<long long> powBase(m + 1);
        powBase[0] = 1;
        for (int i = 1; i <= m; i++) {
            powBase[i] = (powBase[i-1] * BASE) % MOD;
        }
        
        // Prefix hash (forward)
        vector<long long> prefixHash(m + 1, 0);
        for (int i = 0; i < m; i++) {
            prefixHash[i+1] = (prefixHash[i] * BASE + (dfsStr[i] - 'a' + 1)) % MOD;
        }
        
        // Suffix hash (backward)
        vector<long long> suffixHash(m + 1, 0);
        for (int i = m - 1; i >= 0; i--) {
            suffixHash[m-i] = (suffixHash[m-i-1] * BASE + (dfsStr[i] - 'a' + 1)) % MOD;
        }
        
        // Helper to get forward hash of substring [l, r]
        auto getForwardHash = [&](int l, int r) -> long long {
            return (prefixHash[r+1] - prefixHash[l] * powBase[r-l+1] % MOD + MOD) % MOD;
        };
        
        // Helper to get backward hash of substring [l, r]
        auto getBackwardHash = [&](int l, int r) -> long long {
            return (suffixHash[m-l] - suffixHash[m-r-1] * powBase[r-l+1] % MOD + MOD) % MOD;
        };
        
        // Check palindrome for each node
        vector<bool> answer(n);
        for (int i = 0; i < n; i++) {
            answer[i] = (getForwardHash(start[i], end[i]) == getBackwardHash(start[i], end[i]));
        }
        
        return answer;
    }
};
# @lc code=end