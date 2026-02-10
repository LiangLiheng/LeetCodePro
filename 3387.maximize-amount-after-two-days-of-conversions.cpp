#
# @lc app=leetcode id=3387 lang=cpp
#
# [3387] Maximize Amount After Two Days of Conversions
#
# @lc code=start
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        // Build graph for day 1
        unordered_map<string, vector<pair<string, double>>> graph1;
        for (int i = 0; i < pairs1.size(); i++) {
            graph1[pairs1[i][0]].push_back({pairs1[i][1], rates1[i]});
            graph1[pairs1[i][1]].push_back({pairs1[i][0], 1.0 / rates1[i]});
        }
        
        // Find max amounts for all currencies after day 1
        unordered_map<string, double> afterDay1 = findMaxAmounts(initialCurrency, graph1);
        
        // Build graph for day 2
        unordered_map<string, vector<pair<string, double>>> graph2;
        for (int i = 0; i < pairs2.size(); i++) {
            graph2[pairs2[i][0]].push_back({pairs2[i][1], rates2[i]});
            graph2[pairs2[i][1]].push_back({pairs2[i][0], 1.0 / rates2[i]});
        }
        
        // For each currency after day 1, find max path back to initialCurrency
        double maxResult = 1.0; // At minimum we can stay at initialCurrency
        
        for (auto& [currency, amount] : afterDay1) {
            // Find max conversion from currency back to initialCurrency on day 2
            unordered_map<string, double> afterDay2 = findMaxAmounts(currency, graph2);
            
            if (afterDay2.count(initialCurrency)) {
                maxResult = max(maxResult, amount * afterDay2[initialCurrency]);
            }
        }
        
        return maxResult;
    }
    
private:
    unordered_map<string, double> findMaxAmounts(string start, unordered_map<string, vector<pair<string, double>>>& graph) {
        unordered_map<string, double> maxAmounts;
        maxAmounts[start] = 1.0;
        
        // Use BFS with priority queue (max heap) to explore maximum amounts
        priority_queue<pair<double, string>> pq;
        pq.push({1.0, start});
        
        while (!pq.empty()) {
            auto [amount, curr] = pq.top();
            pq.pop();
            
            // If we've already found a better path, skip
            if (amount < maxAmounts[curr]) continue;
            
            // Explore neighbors
            if (graph.count(curr)) {
                for (auto& [next, rate] : graph[curr]) {
                    double newAmount = amount * rate;
                    if (newAmount > maxAmounts[next]) {
                        maxAmounts[next] = newAmount;
                        pq.push({newAmount, next});
                    }
                }
            }
        }
        
        return maxAmounts;
    }
};
# @lc code=end