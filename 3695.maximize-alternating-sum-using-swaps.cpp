#
# @lc app=leetcode id=3695 lang=cpp
#
# [3695] Maximize Alternating Sum Using Swaps
#
# @lc code=start
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        
        // Union-Find to identify connected components
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        
        function<int(int)> find = [&](int x) {
            return parent[x] == x ? x : parent[x] = find(parent[x]);
        };
        
        auto unite = [&](int x, int y) {
            x = find(x);
            y = find(y);
            if (x != y) {
                parent[x] = y;
            }
        };
        
        // Build connected components from swaps
        for (auto& swap : swaps) {
            unite(swap[0], swap[1]);
        }
        
        // Group indices by their root component
        unordered_map<int, vector<int>> components;
        for (int i = 0; i < n; i++) {
            components[find(i)].push_back(i);
        }
        
        long long sum = 0;
        
        // For each component, optimize the alternating sum contribution
        for (auto& [root, indices] : components) {
            // Collect all values in this component
            vector<int> values;
            for (int idx : indices) {
                values.push_back(nums[idx]);
            }
            
            // Sort values in ascending order
            sort(values.begin(), values.end());
            
            // Count even and odd position indices
            int evenCount = 0, oddCount = 0;
            for (int idx : indices) {
                if (idx % 2 == 0) evenCount++;
                else oddCount++;
            }
            
            // Assign largest evenCount values to even positions (contribute +)
            for (int i = values.size() - evenCount; i < values.size(); i++) {
                sum += values[i];
            }
            
            // Assign smallest oddCount values to odd positions (contribute -)
            for (int i = 0; i < oddCount; i++) {
                sum -= values[i];
            }
        }
        
        return sum;
    }
};
# @lc code=end