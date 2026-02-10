#
# @lc app=leetcode id=3310 lang=cpp
#
# [3310] Remove Methods From Project
#

# @lc code=start
class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n);
        for(const auto& inv : invocations) {
            adj[inv[0]].push_back(inv[1]);
        }
        vector<bool> suspicious(n, false);
        queue<int> q;
        q.push(k);
        suspicious[k] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v : adj[u]) {
                if(!suspicious[v]) {
                    suspicious[v] = true;
                    q.push(v);
                }
            }
        }
        bool can_remove = true;
        for(const auto& inv : invocations) {
            if(!suspicious[inv[0]] && suspicious[inv[1]]) {
                can_remove = false;
                break;
            }
        }
        vector<int> res;
        if(can_remove) {
            for(int i = 0; i < n; ++i) {
                if(!suspicious[i]) res.push_back(i);
            }
        } else {
            for(int i = 0; i < n; ++i) {
                res.push_back(i);
            }
        }
        return res;
    }
};
# @lc code=end