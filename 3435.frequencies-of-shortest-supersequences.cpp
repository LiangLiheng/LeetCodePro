#
# @lc app=leetcode id=3435 lang=cpp
#
# [3435] Frequencies of Shortest Supersequences
#

# @lc code=start
class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        set<char> uniq;
        for (const auto& w : words) {
            uniq.insert(w[0]);
            uniq.insert(w[1]);
        }
        vector<char> letters(uniq.begin(), uniq.end());
        int k = letters.size();
        unordered_map<char, int> let_id;
        for (int i = 0; i < k; ++i) {
            let_id[letters[i]] = i;
        }
        vector<vector<int>> graph(k);
        for (const auto& w : words) {
            int u = let_id[w[0]];
            int v = let_id[w[1]];
            graph[u].push_back(v);
        }
        auto is_dag = [&](int mask) -> bool {
            vector<int> indeg(k, 0);
            for (int i = 0; i < k; ++i) {
                if ((mask & (1 << i)) == 0) continue;
                for (int nei : graph[i]) {
                    if ((mask & (1 << nei))) {
                        ++indeg[nei];
                    }
                }
            }
            queue<int> q;
            int cnt = 0;
            int sz = __builtin_popcount(mask);
            for (int i = 0; i < k; ++i) {
                if ((mask & (1 << i)) && indeg[i] == 0) {
                    q.push(i);
                }
            }
            while (!q.empty()) {
                int u = q.front(); q.pop();
                ++cnt;
                for (int nei : graph[u]) {
                    if ((mask & (1 << nei)) && --indeg[nei] == 0) {
                        q.push(nei);
                    }
                }
            }
            return cnt == sz;
        };
        int max_sz = 0;
        for (int mask = 0; mask < (1 << k); ++mask) {
            if (is_dag(mask)) {
                max_sz = max(max_sz, __builtin_popcount(mask));
            }
        }
        vector<vector<int>> ans;
        for (int mask = 0; mask < (1 << k); ++mask) {
            if (is_dag(mask)) {
                if (__builtin_popcount(mask) == max_sz) {
                    vector<int> freq(26, 0);
                    for (int i = 0; i < k; ++i) {
                        int cnt = (mask & (1 << i)) ? 1 : 2;
                        freq[letters[i] - 'a'] = cnt;
                    }
                    ans.push_back(freq);
                }
            }
        }
        return ans;
    }
};
# @lc code=end