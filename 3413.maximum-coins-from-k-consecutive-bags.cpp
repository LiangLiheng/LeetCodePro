#
# @lc app=leetcode id=3413 lang=cpp
#
# [3413] Maximum Coins From K Consecutive Bags
#
# @lc code=start
class Solution {
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        sort(coins.begin(), coins.end());
        
        long long maxCoins = 0;
        int n = coins.size();
        
        for (int i = 0; i < n; i++) {
            // Try window starting at coins[i][0]
            long long start = coins[i][0];
            long long end = start + k - 1;
            long long sum = 0;
            
            for (int j = i; j < n && coins[j][0] <= end; j++) {
                long long l = coins[j][0];
                long long r = coins[j][1];
                long long c = coins[j][2];
                
                long long overlapLeft = max(l, start);
                long long overlapRight = min(r, end);
                
                if (overlapLeft <= overlapRight) {
                    sum += (overlapRight - overlapLeft + 1) * c;
                }
            }
            
            maxCoins = max(maxCoins, sum);
            
            // Try window ending at coins[i][1]
            end = coins[i][1];
            start = end - k + 1;
            sum = 0;
            
            for (int j = 0; j < n && coins[j][0] <= end; j++) {
                long long l = coins[j][0];
                long long r = coins[j][1];
                long long c = coins[j][2];
                
                long long overlapLeft = max(l, start);
                long long overlapRight = min(r, end);
                
                if (overlapLeft <= overlapRight) {
                    sum += (overlapRight - overlapLeft + 1) * c;
                }
            }
            
            maxCoins = max(maxCoins, sum);
        }
        
        return maxCoins;
    }
};
# @lc code=end