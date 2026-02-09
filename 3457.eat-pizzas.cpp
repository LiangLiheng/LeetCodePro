#
# @lc app=leetcode id=3457 lang=cpp
#
# [3457] Eat Pizzas!
#
# @lc code=start
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        int n = pizzas.size();
        
        // Sort pizzas in descending order
        sort(pizzas.begin(), pizzas.end(), greater<int>());
        
        int total_days = n / 4;
        int k1 = (total_days + 1) / 2;  // Number of odd days
        int k2 = total_days / 2;         // Number of even days
        
        long long result = 0;
        
        // Gain from odd days: sum of largest k1 pizzas (used as max in odd-day groups)
        for (int i = 0; i < k1; i++) {
            result += pizzas[i];
        }
        
        // Gain from even days: sum of pizzas used as second-max in even-day groups
        // These are from index k1+k2 to k1+2*k2-1
        for (int i = k1 + k2; i < k1 + 2 * k2; i++) {
            result += pizzas[i];
        }
        
        return result;
    }
};
# @lc code=end