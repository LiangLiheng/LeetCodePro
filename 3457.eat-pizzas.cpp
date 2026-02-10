#
# @lc app=leetcode id=3457 lang=cpp
#
# [3457] Eat Pizzas!
#
# @lc code=start
class Solution {
public:
    long long maxWeight(vector<int>& pizzas) {
        sort(pizzas.begin(), pizzas.end(), greater<int>());
        
        int n = pizzas.size();
        int days = n / 4;
        long long totalWeight = 0;
        int left = 0, right = n - 1;
        
        for (int day = 1; day <= days; day++) {
            if (day % 2 == 1) {  // Odd day
                // Take 1 from left (largest) and 3 from right (smallest)
                totalWeight += pizzas[left];
                left++;
                right -= 3;
            } else {  // Even day
                // Take 2 from left and 2 from right
                // Gain the second largest, which is pizzas[left + 1]
                totalWeight += pizzas[left + 1];
                left += 2;
                right -= 2;
            }
        }
        
        return totalWeight;
    }
};
# @lc code=end