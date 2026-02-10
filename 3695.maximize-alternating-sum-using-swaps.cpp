#
# @lc app=leetcode id=3695 lang=cpp
#
# [3695] Maximize Alternating Sum Using Swaps
#
# @lc code=start
class Solution {
public:
    class UnionFind {
    public:
        vector<int> parent, rank;
        
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        void unite(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px == py) return;
            
            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }
    };
    
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        UnionFind uf(n);
        
        // Build union-find from swaps
        for (auto& swap : swaps) {
            uf.unite(swap[0], swap[1]);
        }
        
        // Group indices by their root parent
        unordered_map<int, vector<int>> components;
        for (int i = 0; i < n; i++) {
            components[uf.find(i)].push_back(i);
        }
        
        // Create result array
        vector<int> result(n);
        
        // Process each component
        for (auto& [root, indices] : components) {
            // Collect values for this component
            vector<int> values;
            for (int idx : indices) {
                values.push_back(nums[idx]);
            }
            
            // Separate indices into even and odd
            vector<int> evenIndices, oddIndices;
            for (int idx : indices) {
                if (idx % 2 == 0) {
                    evenIndices.push_back(idx);
                } else {
                    oddIndices.push_back(idx);
                }
            }
            
            // Sort values in descending order
            sort(values.begin(), values.end(), greater<int>());
            
            // Assign largest values to even indices
            int valIdx = 0;
            for (int idx : evenIndices) {
                result[idx] = values[valIdx++];
            }
            
            // Assign remaining values to odd indices
            for (int idx : oddIndices) {
                result[idx] = values[valIdx++];
            }
        }
        
        // Calculate alternating sum
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                sum += result[i];
            } else {
                sum -= result[i];
            }
        }
        
        return sum;
    }
};
# @lc code=end