#
# @lc app=leetcode id=3493 lang=cpp
#
# [3493] Properties Graph
#
# @lc code=start
class Solution {
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        
        // Union-Find data structure
        vector<int> parent(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        // Find function with path compression
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        // Union function
        auto unite = [&](int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px != py) {
                parent[px] = py;
            }
        };
        
        // Intersect function
        auto intersect = [](const vector<int>& a, const vector<int>& b) {
            unordered_set<int> setA(a.begin(), a.end());
            unordered_set<int> setB(b.begin(), b.end());
            int count = 0;
            for (int val : setA) {
                if (setB.count(val)) {
                    count++;
                }
            }
            return count;
        };
        
        // Build graph and unite components
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (intersect(properties[i], properties[j]) >= k) {
                    unite(i, j);
                }
            }
        }
        
        // Count connected components
        unordered_set<int> components;
        for (int i = 0; i < n; i++) {
            components.insert(find(i));
        }
        
        return components.size();
    }
};
# @lc code=end