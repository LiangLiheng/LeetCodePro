#
# @lc app=leetcode id=3559 lang=cpp
#
# [3559] Number of Ways to Assign Edge Weights II
#
# @lc code=start
class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        int n = edges.size() + 1;
        const int MOD = 1e9 + 7;
        
        // Build adjacency list
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        // Function to find path length using BFS
        auto findPathLength = [&](int start, int end) -> int {
            if (start == end) return 0;
            
            queue<pair<int, int>> q;
            vector<bool> visited(n + 1, false);
            q.push({start, 0});
            visited[start] = true;
            
            while (!q.empty()) {
                auto [node, depth] = q.front();
                q.pop();
                
                if (node == end) return depth;
                
                for (int neighbor : graph[node]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push({neighbor, depth + 1});
                    }
                }
            }
            return 0;
        };
        
        // Function to calculate 2^exp mod MOD using fast exponentiation
        auto power = [&](long long base, long long exp) -> long long {
            long long result = 1;
            base %= MOD;
            while (exp > 0) {
                if (exp % 2 == 1) {
                    result = (result * base) % MOD;
                }
                base = (base * base) % MOD;
                exp /= 2;
            }
            return result;
        };
        
        vector<int> answer;
        for (const auto& query : queries) {
            int u = query[0];
            int v = query[1];
            int k = findPathLength(u, v);
            
            if (k == 0) {
                answer.push_back(0);
            } else {
                answer.push_back(power(2, k - 1));
            }
        }
        
        return answer;
    }
};
# @lc code=end