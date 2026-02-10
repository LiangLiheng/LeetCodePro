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
        for (auto& lis : adj) {
            sort(lis.begin(), lis.end());
        }
        using ll = long long;
        const ll MOD1 = 1000000007LL;
        const ll BASE1 = 131;
        const ll MOD2 = 1000000009LL;
        const ll BASE2 = 137;
        vector<ll> pow1(n + 1, 1LL);
        vector<ll> pow2(n + 1, 1LL);
        for (int i = 1; i <= n; ++i) {
            pow1[i] = pow1[i - 1] * BASE1 % MOD1;
            pow2[i] = pow2[i - 1] * BASE2 % MOD2;
        }
        vector<bool> answer(n);
        auto dfs = [&](auto&& self, int node) -> tuple<ll, ll, ll, ll, int> {
            ll hleft1 = 0, hright1 = 0, hleft2 = 0, hright2 = 0;
            int leng = 0;
            for (int child : adj[node]) {
                auto [lh1, rh1, lh2, rh2, clen] = self(self, child);
                ll nhleft1 = (hleft1 * pow1[clen] % MOD1 + lh1) % MOD1;
                ll nhright1 = (hright1 + pow1[leng] * rh1 % MOD1) % MOD1;
                ll nhleft2 = (hleft2 * pow2[clen] % MOD2 + lh2) % MOD2;
                ll nhright2 = (hright2 + pow2[leng] * rh2 % MOD2) % MOD2;
                hleft1 = nhleft1;
                hright1 = nhright1;
                hleft2 = nhleft2;
                hright2 = nhright2;
                leng += clen;
            }
            int val = s[node] - 'a' + 1;
            ll final_left1 = (hleft1 * pow1[1] % MOD1 + val) % MOD1;
            ll final_right1 = (hright1 + pow1[leng] * (ll)val % MOD1) % MOD1;
            ll final_left2 = (hleft2 * pow2[1] % MOD2 + val) % MOD2;
            ll final_right2 = (hright2 + pow2[leng] * (ll)val % MOD2) % MOD2;
            answer[node] = (final_left1 == final_right1) && (final_left2 == final_right2);
            return {final_left1, final_right1, final_left2, final_right2, leng + 1};
        };
        dfs(dfs, 0);
        return answer;
    }
};
# @lc code=end