#
# @lc app=leetcode id=3373 lang=cpp
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1;
        int m = edges2.size() + 1;
        // Tree 1
        vector<vector<int>> adj1(n);
        for (const auto& e : edges1) {
            int u = e[0], v = e[1];
            adj1[u].push_back(v);
            adj1[v].push_back(u);
        }
        vector<int> color1(n, -1);
        queue<int> q;
        q.push(0);
        color1[0] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj1[u]) {
                if (color1[v] == -1) {
                    color1[v] = 1 - color1[u];
                    q.push(v);
                }
            }
        }
        int cnt0_1 = 0, cnt1_1 = 0;
        for (int i = 0; i < n; ++i) {
            if (color1[i] == 0) ++cnt0_1;
            else ++cnt1_1;
        }
        // Tree 2
        vector<vector<int>> adj2(m);
        for (const auto& e : edges2) {
            int u = e[0], v = e[1];
            adj2[u].push_back(v);
            adj2[v].push_back(u);
        }
        vector<int> color2(m, -1);
        queue<int> q2;
        q2.push(0);
        color2[0] = 0;
        while (!q2.empty()) {
            int u = q2.front(); q2.pop();
            for (int v : adj2[u]) {
                if (color2[v] == -1) {
                    color2[v] = 1 - color2[u];
                    q2.push(v);
                }
            }
        }
        int cnt0_2 = 0, cnt1_2 = 0;
        for (int i = 0; i < m; ++i) {
            if (color2[i] == 0) ++cnt0_2;
            else ++cnt1_2;
        }
        int K = max(cnt0_2, cnt1_2);
        vector<int> answer(n);
        for (int i = 0; i < n; ++i) {
            int even_size_1 = (color1[i] == 0 ? cnt0_1 : cnt1_1);
            answer[i] = even_size_1 + K;
        }
        return answer;
    }
};
# @lc code=end