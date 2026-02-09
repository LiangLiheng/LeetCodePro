#
# @lc app=leetcode id=3387 lang=cpp
#
# [3387] Maximize Amount After Two Days of Conversions
#
# @lc code=start
class Solution {
public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        // Build bidirectional graphs for both days
        unordered_map<string, vector<pair<string, double>>> graph1, graph2;
        
        // Day 1: add edges in both directions
        for (int i = 0; i < pairs1.size(); i++) {
            string from = pairs1[i][0], to = pairs1[i][1];
            double rate = rates1[i];
            graph1[from].push_back({to, rate});
            graph1[to].push_back({from, 1.0 / rate});
        }
        
        // Day 2: add edges in both directions
        for (int i = 0; i < pairs2.size(); i++) {
            string from = pairs2[i][0], to = pairs2[i][1];
            double rate = rates2[i];
            graph2[from].push_back({to, rate});
            graph2[to].push_back({from, 1.0 / rate});
        }
        
        // Find maximum amounts reachable on Day 1 from initialCurrency
        unordered_map<string, double> day1Max = findMaxConversions(graph1, initialCurrency);
        
        // Collect all currencies from both graphs
        unordered_set<string> allCurrencies;
        allCurrencies.insert(initialCurrency);
        for (auto& p : graph1) allCurrencies.insert(p.first);
        for (auto& p : graph2) allCurrencies.insert(p.first);
        
        // Try each intermediate currency and find maximum
        double maxResult = 1.0;
        
        for (const string& intermediateCurrency : allCurrencies) {
            // Amount of intermediate currency after Day 1
            double amountAfterDay1 = day1Max.count(intermediateCurrency) ? day1Max[intermediateCurrency] : 0.0;
            
            // Find maximum amount of initialCurrency starting from intermediate currency on Day 2
            unordered_map<string, double> day2Max = findMaxConversions(graph2, intermediateCurrency);
            double conversionBackRate = day2Max.count(initialCurrency) ? day2Max[initialCurrency] : 0.0;
            
            // Update maximum result
            maxResult = max(maxResult, amountAfterDay1 * conversionBackRate);
        }
        
        return maxResult;
    }
    
private:
    // Find maximum conversion amounts from start currency using given graph
    unordered_map<string, double> findMaxConversions(unordered_map<string, vector<pair<string, double>>>& graph, string start) {
        unordered_map<string, double> maxAmount;
        maxAmount[start] = 1.0;
        
        priority_queue<pair<double, string>> pq;
        pq.push({1.0, start});
        
        while (!pq.empty()) {
            auto [currentAmount, currentCurrency] = pq.top();
            pq.pop();
            
            // Skip if we've already found a better path
            if (currentAmount < maxAmount[currentCurrency]) continue;
            
            // Skip if no outgoing edges
            if (graph.find(currentCurrency) == graph.end()) continue;
            
            // Explore all conversions from current currency
            for (auto& [nextCurrency, conversionRate] : graph[currentCurrency]) {
                double newAmount = maxAmount[currentCurrency] * conversionRate;
                
                // Update if we found a better conversion path
                if (maxAmount.find(nextCurrency) == maxAmount.end() || newAmount > maxAmount[nextCurrency]) {
                    maxAmount[nextCurrency] = newAmount;
                    pq.push({newAmount, nextCurrency});
                }
            }
        }
        
        return maxAmount;
    }
};
# @lc code=end