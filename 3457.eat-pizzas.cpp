#
# @lc app=leetcode id=3457 lang=cpp
#
# [3457] Eat Pizzas!
#

# @lc code=start
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        std::sort(pizzas.rbegin(), pizzas.rend());
        int n = pizzas.size();
        int k = n / 4;
        int even_days = k / 2;
        int odd_days = k - even_days;
        long long total = 0;
        for (int i = 0; i < odd_days; ++i) {
            total += pizzas[i];
        }
        for (int i = 0; i < even_days; ++i) {
            total += pizzas[odd_days + 2 * i + 1];
        }
        return total;
    }
};
# @lc code=end