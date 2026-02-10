#
# @lc app=leetcode id=3310 lang=cpp
#
# [3310] Remove Methods From Project
#

# @lc code=start
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);
        for(auto& inv : invocations) {
            graph[inv[0]].push_back(inv[1]);
        }
        vector<char> suspicious(n, 0);
        queue<int> q;
        q.push(k);
        suspicious[k] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                if (suspicious[v] == 0) {
                    suspicious[v] = 1;
                    q.push(v);
                }
            }
        }
        bool can_remove = true;
        for (int i = 0; i < n; ++i) {
            if (suspicious[i] == 0) {
                for (int j : graph[i]) {
                    if (suspicious[j] == 1) {
                        can_remove = false;
                        break;
                    }
                }
                if (!can_remove) {
                    break;
                }
            }
        }
        vector<int> res;
        if (can_remove) {
            for (int i = 0; i < n; ++i) {
                if (suspicious[i] == 0) {
                    res.push_back(i);
                }
            }
        } else {
            for (int i = 0; i < n; ++i) {
                res.push_back(i);
            }
        }
        return res;
    }
};
# @lc code=end