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
        
        // Build adjacency lists
        vector<vector<int>> graph1(n), graph2(m);
        for (auto& e : edges1) {
            graph1[e[0]].push_back(e[1]);
            graph1[e[1]].push_back(e[0]);
        }
        for (auto& e : edges2) {
            graph2[e[0]].push_back(e[1]);
            graph2[e[1]].push_back(e[0]);
        }
        
        // Color tree1 using BFS
        vector<int> color1(n, -1);
        queue<int> q;
        q.push(0);
        color1[0] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph1[u]) {
                if (color1[v] == -1) {
                    color1[v] = 1 - color1[u];
                    q.push(v);
                }
            }
        }
        
        // Count nodes of each color in tree1
        int cnt1_0 = 0, cnt1_1 = 0;
        for (int i = 0; i < n; i++) {
            if (color1[i] == 0) cnt1_0++;
            else cnt1_1++;
        }
        
        // Color tree2 using BFS
        vector<int> color2(m, -1);
        q.push(0);
        color2[0] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : graph2[u]) {
                if (color2[v] == -1) {
                    color2[v] = 1 - color2[u];
                    q.push(v);
                }
            }
        }
        
        // Count nodes of each color in tree2
        int cnt2_0 = 0, cnt2_1 = 0;
        for (int i = 0; i < m; i++) {
            if (color2[i] == 0) cnt2_0++;
            else cnt2_1++;
        }
        int maxCount2 = max(cnt2_0, cnt2_1);
        
        // Build answer
        vector<int> answer(n);
        for (int i = 0; i < n; i++) {
            if (color1[i] == 0) {
                answer[i] = cnt1_0 + maxCount2;
            } else {
                answer[i] = cnt1_1 + maxCount2;
            }
        }
        
        return answer;
    }
};
# @lc code=end