#
# @lc app=leetcode id=3695 lang=cpp
#
# [3695] Maximize Alternating Sum Using Swaps
#
# @lc code=start
class Solution {
public:
    vector<int> parent;
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py) {
            parent[px] = py;
        }
    }
    
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        // Build union-find structure
        for (auto& swap : swaps) {
            unite(swap[0], swap[1]);
        }
        
        // Group indices by component
        unordered_map<int, vector<int>> components;
        for (int i = 0; i < n; i++) {
            components[find(i)].push_back(i);
        }
        
        // For each component, assign values optimally
        vector<int> result(n);
        for (auto& [root, indices] : components) {
            // Get values for this component
            vector<int> values;
            for (int idx : indices) {
                values.push_back(nums[idx]);
            }
            
            // Sort values in descending order
            sort(values.begin(), values.end(), greater<int>());
            
            // Separate indices into even and odd
            vector<int> even_indices, odd_indices;
            for (int idx : indices) {
                if (idx % 2 == 0) {
                    even_indices.push_back(idx);
                } else {
                    odd_indices.push_back(idx);
                }
            }
            
            // Assign largest values to even indices, smallest to odd
            int val_idx = 0;
            for (int idx : even_indices) {
                result[idx] = values[val_idx++];
            }
            for (int idx : odd_indices) {
                result[idx] = values[val_idx++];
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